/*
Bu bölümde robotun yapacağı hareketler fonksiyon olarak tanımlanacaktır.
Robot-->
- ileri gitme
- geri gitme
- durma ve bilgileri eeproma kaydetme
- Sağ ve sola dönme 
hareketi yapacaktır
*/


// ileri gitme fonksiyonu
void ileriGit(){
  
  motSag = constrain((offsetSag + output), 0, 255);    // motor hızları atanıyor
  motSol = constrain((offsetSol - output), 0, 255);
  
  analogWrite(motSagOn,motSag);     // ileri gitmek için gerekli pin atamaları
  analogWrite(motSolOn,motSol);
  digitalWrite(motSagArka,LOW);
  digitalWrite(motSolArka,LOW);
    
}

// geri gitme fonksiyonu
void geriGit(){
  
  motSag = constrain((offsetSag + output), 0, 255);    // motor hızları atanıyor
  motSol = constrain((offsetSol - output), 0, 255);
  
  digitalWrite(motSagArka,motSag);      // geri gitmek için gerekli pin atamaları
  digitalWrite(motSolArka,motSol);
  digitalWrite(motSagOn,LOW);
  digitalWrite(motSolOn,LOW);
    
}

// durma fonksiyonu
void dur(){
  digitalWrite(motSagArka,LOW);      // durmak için gerekli pin atamaları
  digitalWrite(motSolArka,LOW);
  digitalWrite(motSagOn,LOW);
  digitalWrite(motSolOn,LOW);
  
  EEPROM.write(sayac,konum);        // konum verileri eeprom'a yazılıyor 
  konum = 0;      // bir dahaki hareket için konum sıfırlanıyor                    
  sayac += 1;  
}

// dönme fonksiyonu
void don(boolean yon){
  
  digitalWrite(motSagArka,LOW);  // motor geri pinleri LOW
  digitalWrite(motSolArka,LOW);
  
  if(yon == 0){    // sağa dönüş yapılacaksa
    motSag = offsetSag + donum2;
    motSol = offsetSol + donum1;
    analogWrite(motSagOn,motSag);    
    analogWrite(motSolOn,motSol);
    
  }else{    // sola dönüş yapacaksa
    motSag = offsetSag + donum1;
    motSol = offsetSol + donum2;
    analogWrite(motSagOn,motSag);    
    analogWrite(motSolOn,motSol);
  }  
}
