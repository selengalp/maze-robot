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
  
  digitalWrite(motSagOn,HIGH);     // ileri gitmek için gerekli pin atamaları
  digitalWrite(motSolOn,HIGH);
  digitalWrite(motSagArka,LOW);
  digitalWrite(motSolArka,LOW);
  
  motSag = constrain((offsetSag + output), 0, 255);    // motor hızları atanıyor
  motSol = constrain((offsetSol - output), 0, 255);
  
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
  
  digitalWrite(motSagOn,HIGH);     // ileri gitmek için gerekli pin atamaları
  digitalWrite(motSolOn,HIGH);
  digitalWrite(motSagArka,LOW);
  digitalWrite(motSolArka,LOW);
  
  if(yon == 0){    // sağa dönüş yapılacaksa
    motSag = offsetSag + donum2;
    motSol = offsetSol + donum1;
    
  }else{    // sola dönüş yapacaksa
    motSag = offsetSag + donum1;
    motSol = offsetSol + donum2;
  }  
}
