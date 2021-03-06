/*
Bu bölümde sensör işlemleri yapılacaktır
*/

// Analog sharp sensörü okuma fonksiyonu
int sharpOku(int pin){   // analog sharp sensörler okunur   
  return 2400 / (analogRead(pin) - 20);      // fonksiyon cm cinsinden değer dönderir
}

// Digital sharp sensörü okuma fonksiyonu
boolean sharpDigitalOku(int pin){      // digital sharp sensörler okunur
  return digitalRead(pin);
}

// Kontrast sensörü okuma fonksiyonu
boolean kontrastOku(int pin){
  
}

// Konumu hesaplamak için kullanılan interrupt fonksiyonu 
// Aynı zamanda enkoderdan gelen değeri işlemekte kullanılıyor
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

// tüm sensörleri okumak için kullanılan fonksiyon
void tumSensorleriOku(){
  sag = sharpOku(sensorSag);
  sol = sharpOku(sensorSol);
  on = sharpDigitalOku(sensorOn);
  arka = sharpDigitalOku(sensorArka);
}

// debug kodları bu fonksiyonda
void debugFunction(){
  Serial.print("sol  :");
  Serial.print(sol);
  Serial.print("     ");
  Serial.print("sag  :");
  Serial.print(sag);
  Serial.print("     ");
  Serial.print("on  :");
  Serial.print(on);
  Serial.print("     ");
  Serial.print("arka  :");
  Serial.print(arka);
  Serial.print("     ");
  Serial.print("hata  :");
  Serial.print(sag-sol);
  Serial.print("     ");
  Serial.print("output  :");
  Serial.print(output);
  Serial.print("     ");
  Serial.print("motorSag  :");
  Serial.print(motSag);
  Serial.print("     ");
  Serial.print("motorSol  :");
  Serial.print(motSol);
//  Serial.print("Konum    :");
//  Serial.print(konum);
  Serial.println();
}
