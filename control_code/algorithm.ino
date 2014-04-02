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
    delay(50);
    don(1);
    
  }else if(sag>20 && sol<20){    // sol duvar sağ boşluksa sağa dön
    
    dur();
    delay(50);
    don(0);
    
  }else{  // hiç bir şart sağlanmadıysa geri git
   geriGit(); 
  }       

}
