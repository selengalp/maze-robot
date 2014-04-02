/*
Bu bölümde labirent çözücü algoritma ve pid ile ilgili işlemler yapılacak 
*/

// hata hesabı
void hataHesapla(){          // hata negatifse sağa daha yakın
  error = sag - sol;          // hata pozitifse sola daha yakın
}


 // Labirent çözen kısım 
void yolunuBul(){
  if(sag<20 && sol<20){      // sağ ve sol duvarsa ileri git
    
    ileriGit();
    
  }else if(sag<20 && sol>20){    // sağ duvar sol boşluksa sola dön
    
    dur();
    don(1);
    
  }else if(sag>20 && sol<20){    // sol duvar sağ boşluksa sağa dön
    
    dur();
    don(0);
    
  }else{ }       // hiç bir şart sağlanmadıysa bir şey yapma

  #ifdef DEBUG
  Serial.print("sol    :");
  Serial.print(sol);
  Serial.print("     ");
  Serial.print("sag    :");
  Serial.print(sag);
  Serial.print("     ");
  Serial.print("on    :");
  Serial.print(on);
  Serial.print("     ");
  Serial.print("arka    :");
  Serial.print(arka);
  Serial.print("     ");
  Serial.print("hata  :");
  Serial.print(sag-sol);
  Serial.print("     ");
  Serial.print("Konum    :");
  Serial.println(konum);
  delay(100);
  #endif  
}
