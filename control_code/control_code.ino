#include <EEPROM.h>
#include <PID_v1.h>

//--------------------------------------------------------------------------------
//              DEĞİŞKENLER BÖLÜMÜ - TÜM DEĞİŞKENLER BURADA TANIMLANACAK
//--------------------------------------------------------------------------------

// pid katsayıları
const double kp=0.0;        // oransal katsayısı
const double ki=0.0;        // integral katsayısı
const double kd=0.0;        // türev kaysayısı

// sensör değişkenleri
boolean on,arka;    // ön ve arkada bulunan dijital sensörler (ön---pina2)(arka---pina4)
int sag,sol;        // sağ ve soldaki analog uzaklık sensörleri (sag---pin1)(sol---pin0)

// motor pinleri
const int motSagOn = 5;
const int motSolOn = 11;
const int motSolArka = 10;
const int motSagArka = 6;
const int enableSag = 13;
const int enableSol = 7;

// motor değişkenleri
int motSag = 0;
int motSol = 0;
int offsetSag = 0;
int offsetSol = 0;


// pid değişkenleri
double error=0,referance=0,output=0;

// konum değişkeninin tutulduğu fonsiyon
volatile double konum;
int sayac=0;      // kaç defa ileri gidildiğini sayan sayaç

// pid objesi
// error     -> sensörlerden elde edilen hata 
// output    -> pid algoritmasının verdiği çıktı
// referance -> ulaşılması hedeflenen nokta, hatanın sıfır olduğu yer
PID pid1(&error,&output,&referance , kp, ki, kd, DIRECT);

//--------------------------------------------------------------------------------
//              SETUP BÖLÜMÜ - TÜM AYARLAR BU BÖLÜMDE YAPILACAK
//--------------------------------------------------------------------------------

void setup()
{
  Serial.begin(9600);    // seri monitör ile iletişim başlatılıyor
  
  // pin modları
  DDRB = B000000;   // tüm B portu çıkış
  DDRD = B00110000; // D2,D3 input diğerleri output
  
  // pid ayarları
  pid1.SetMode(AUTOMATIC);
  pid1.SetOutputLimits(-255, 255);
  
  // encoder pinlerindeki interrupt ayarları
  attachInterrupt(0,konumBul,CHANGE);
  attachInterrupt(1,konumBul,CHANGE);
  
  // motor enable ayarları
  digitalWrite(enableSag,0);
  digitalWrite(enableSol,0);
}

//--------------------------------------------------------------------------------
//              LOOP BÖLÜMÜ - TÜM İŞLEMLER BU BÖLÜMDE YAPILACAK
//--------------------------------------------------------------------------------


void loop()
{
  pid1.Compute();          // pid kontrolcüsünü çalıştırıyor
}

//--------------------------------------------------------------------------------
//              FONKSİYONLAR BÖLÜMÜ - TÜM FONKSİYONLAR BU BÖLÜMDE TANIMLANACAK
//--------------------------------------------------------------------------------


// hata hesabı
int hata_hesapla(){          // hata negatifse sağa daha yakın
  return sag - sol;          // hata pozitifse sola daha yakın
}

// Analog sharp sensörü okuma fonksiyonu
int sharpOku(int pin){                 // Analog sharp sensörler okunur   
  return 2400 / (analogRead(pin) - 20);      // fonksiyon cm cinsinden değer dönderir
}

// Digital sharp sensörü okuma fonksiyonu
boolean sharpDigitalOku(int pin){      // digital sharp sensörler okunur
  return digitalRead(pin);
}

// Kontrast sensörü okuma fonksiyonu


// Konumu hesaplamak için kullanılan interrupt fonksiyonu 
void konumBul(){
  if(digitalRead(motSagOn) == 1 && digitalRead(motSolOn) == 1) // motorlar ileri yönde dönüyor ise konum arttırılıyor
  {
    konum += 2.74;
  }
  else if(digitalRead(motSagOn) == 0 && digitalRead(motSolOn) == 0) // motorlar geriye dönüyor ise konum azaltılıyor
  {
    konum -= 2.74;   
  }
}

// ileri gitme fonksiyonu
void ileriGit(){
  
  digitalWrite(motSagOn,HIGH);     // ileri gitmek için gerekli pin atamaları
  digitalWrite(motSolOn,HIGH);
  digitalWrite(motSagArka,LOW);
  digitalWrite(motSolArka,LOW);
  
  motSag = constrain((offsetSag + output), 0, 255);    // motor hızları atanıyor
  motSol = constrain((offsetSol - output), 0, 255);
  
  sayac += 1;
}

// geri gitme fonksiyonu
void geriGit(){
  
  digitalWrite(motSagArka,HIGH);      // geri gitmek için gerekli pin atamaları
  digitalWrite(motSolArka,HIGH);
  digitalWrite(motSagOn,LOW);
  digitalWrite(motSolOn,LOW);
  
  motSag = constrain((offsetSag + output), 0, 255);    // motor hızları atanıyor
  motSol = constrain((offsetSol - output), 0, 255);
}

void dur(){
  digitalWrite(motSagArka,LOW);      // durmak için gerekli pin atamaları
  digitalWrite(motSolArka,LOW);
  digitalWrite(motSagOn,LOW);
  digitalWrite(motSolOn,LOW);
  
  EEPROM.write(sayac,konum);        // konum verileri eeprom'a yazılıyor 
  konum = 0;                         // bir dahaki hareket için konum sıfırlanıyor
}

