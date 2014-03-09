#include <EEPROM.h>
#include <PID_v1.h>

// Debug modda çalıştırmak için etiketi uncomment et
// #define DEBUG

//--------------------------------------------------------------------------------
//              DEĞİŞKENLER BÖLÜMÜ - TÜM GLOBAL DEĞİŞKENLER BURADA TANIMLANACAK
//--------------------------------------------------------------------------------

// pid katsayıları
const double kp=0.0;        // oransal katsayısı
const double ki=0.0;        // integral katsayısı
const double kd=0.0;        // türev kaysayısı

// sensör değişkenleri
boolean on,arka;    // ön ve arkada bulunan dijital sensörler (ön---pina2)(arka---pina4)
int sag,sol;        // sağ ve soldaki analog uzaklık sensörleri (sag---pina1)(sol---pina0)

// sensor pinleri
const int sensorSag = A1;
const int sensorSol = A0;
const int sensorOn = A2;
const int sensorArka = A3;

// motor pinleri
const int motSagOn = 5;
const int motSolOn = 11;
const int motSolArka = 10;
const int motSagArka = 6;
const int enableSag = 13;
const int enableSol = 7;

// motor değişkenleri
int motSag = 0;        // motora uygulanacak toplam pwm girişi
int motSol = 0;
int offsetSag = 0;    // Motorlara dönmeye başlamaları için sürekli verilen giriş
int offsetSol = 0;
const int donum1 = 100;    // Dönerken hızlı dönen tekere verilecek giriş
const int donum2 = 50;     // Dönerken yavaş dönen tekere verilecek giriş

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
  tumSensorleriOku();
  hataHesapla();           // hata hesaplanıyor
  pid1.Compute();          // pid kontrolcüsünü çalıştırıyor
  yolunuBul();             // labirent çözme algoritması ekleniyor 
}








