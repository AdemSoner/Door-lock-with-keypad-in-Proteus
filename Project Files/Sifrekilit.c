/*
Kod ile ilgili bilgiler.
Þifreyi ilk program çalýþtýðýnda kullanýcý eli ile belirliyor.
Sonrasýnda giriþ için tekrardan þifre giriþi yapmalýdýr.
Sessiz alarm kodu "1233" dür. Kullanýcý kendi þifresini "1233" belirleyemez.  
bu durumuda tekrardan þifre giriþi istenecektir.
Kullanýcýnýn doðru þifreyi girmesi için 3 hakký vardýr. 3 deneyiþte de doðru
giriþ yapamaz ise giriþ baþarýsýz uyarýsý verip doðru þifreyi gösterip
yeni þifre isteði ile program devam eder.
þifreyi belirledikten sonra doðru giriþ yapar ise 
-> yeþil led yanar lcdye hoþgeldiniz yazar. sonra tekrar program baþa döner.
alarm kodunu girdiðinde ise
-> Sarý led 10 defa yanýp söner acil durum anlamýnda. sonra program baþa döner.
3 defa yanlýþ þifre girildiðinde ise
-> kýrmýzý led yanar sonra yukarda anlattýðým þekilde yol izlenir.

proteusta kullandýðým aygýtlar
PIC = PIC16F877A
LCD = LM016L
Keypad= KEYPAD_PHONE
Led'ler(Sarý-Kýrmýzý-Yeþil)

*/
#include <Sifrekilit.h>
#define LCD_ENABLE_PIN PIN_E0     // lcd enable -> e0 pinine attýk
#define LCD_RW_PIN PIN_E1        //  lcd rw -> e1 pinine 
#define LCD_RS_PIN PIN_E2        //  lcd rs -> e2 pinine
#define LCD_DATA4 PIN_D4         //  lcd data4 -> d4 pinine 
#define LCD_DATA5 PIN_D5         //  lcd data5 -> d5 pinine 
#define LCD_DATA6 PIN_D6         //  lcd data6 -> d6 pinine 
#define LCD_DATA7 PIN_D7         //  lcd data7 -> d7 pinine 

#fuses xt,nowdt,nolvp

#include <lcd.c>   // lcd kütüphanesini eklememiz gerekiyor

void acildurum()
{
   output_high(pin_d0);
   delay_ms(200);
   output_low(pin_d0);
   delay_ms(200);
}


int keypaddd()    // keypaddan tus beklerken bu fonksiyona yollayacaðýz.
{
    //    ----------------------------------------------------
   /*       Keypad tuþ kontrolü
   
   Keypad kontrolü yaparken 4x3 lük bir keypadim mevcut.
         Satýrlarý a,b,c,d
         sütünlarý 1,2,3 olarak düþünürsek 
         [a1 a2 a3] => [1 2 3]
         [b1 b2 b3] => [4 5 6]
         [c1 c2 c3] => [7 8 9]
         [d1 d2 d3] => [* 0 #]
         keypad'de karþýlýk gelen deðerler bunlar oluyor.
         Main içerisinde tris ile PIC giriþ pinlerimi satýrlar olarak belirlemiþtim.
   */
   
   
   int i;
   char flag='h';    // herhangi bir tuþa basýlýp basýlmadýðýný kontrol edecek
   for(i=0;i<2;i++)  // tuþa basýlacaða kadar dönmesi için kurduðum döngü.
   {
      output_high(pin_b0);  // kontrolde 1.satýrý aktif ediyor
      if(input(pin_b4)==1)  // 1.sütüna basýlmýþsa geriye 1 deðeri dönüyor
         {output_low(pin_b0);output_low(pin_b4);printf(lcd_putc,"1");return 1;}
      else if(input(pin_b5)==1)// 2.sütüna basýlmýþsa geriye 2 deðeri dönüyor
           {output_low(pin_b0);output_low(pin_b5);printf(lcd_putc,"2");return 2;}
           else if(input(pin_b6)==1)// 3.sütüna basýlmýþsa geriye 1 deðeri dönüyor
               {output_low(pin_b0);output_low(pin_b6);printf(lcd_putc,"3");return 3;}
  
      output_low(pin_b0);//1.satýra basýlmadýðý tespit edildiðinden pasif yapýyoruz.
      output_high(pin_b1); //2. satýrýn kontrolu de ayný þekilde yapýyoruz.
      if(input(pin_b4)==1)
          {output_low(pin_b1);output_low(pin_b4);printf(lcd_putc,"4");return 4;}
      else if(input(pin_b5)==1)
           {output_low(pin_b1);output_low(pin_b5);printf(lcd_putc,"5");return 5;}
           else if(input(pin_b6)==1)
               {output_low(pin_b1);output_low(pin_b6);printf(lcd_putc,"6");return 6;}
               
      output_low(pin_b1);
      output_high(pin_b2);
      if(input(pin_b4)==1)
          {output_low(pin_b2);output_low(pin_b4);printf(lcd_putc,"7");return 7;}
      else if(input(pin_b5)==1)
           {output_low(pin_b2);output_low(pin_b5);printf(lcd_putc,"8");return 8;}
           else if(input(pin_b6)==1)
               {output_low(pin_b2);output_low(pin_b6);printf(lcd_putc,"9");return 9;}
               
      output_low(pin_b2);
      output_high(pin_b3);
      if(input(pin_b4)==1)
        printf(lcd_putc,"");
      else if(input(pin_b5)==1)
         {output_low(pin_b3);output_low(pin_b5);printf(lcd_putc,"0");return 0;}
            else if(input(pin_b6)==1)
               printf(lcd_putc,"");
             
      output_low(pin_b0);
      output_low(pin_b1);
      output_low(pin_b2); // baþa döndüðümüzde basýlý tuþ kalmamasý için
      output_low(pin_b3); // tüm pinleri kapatýyoruz.

  //    ----------------------------------------------------
   if(flag=='h') // eðerki return deðeri ile fonksiyondan çýkmadýysak
      i=-1;       // h deðeri dönücektir. i mizi azaltacaðýndan
   }              // for döngüsü tekrar tekrar çalýþacaktýr.
  return -1;      // herhangi bir tuþa basýlacaða kadar.

}





void main()
{
   lcd_init(); // Lcd kendini ayarlamasý için main içerisinde bu kodu yazýyoruz.
   /*
   led kodlarý
   \f lcd ekranýný temizler ve imleci baþa alýr
   \a imleci en baþa alýr(silmeden)
   \n alt satýra geçer
   \b bir karakter imleci geri kaydýrýr. 
   */
   int pass[4],i,j; // kullanýcýdan þifre alýnacak
   int try[4]; // giriþ yapmayý denerken þifre dizisi
   int alarm[]={1,2,3,3},sayac=0; // sessiz alarm için
   char flag=0; // ilk giriþte þifre alýnmasý veya þifre deðiþtirmek için
   
   set_tris_b(0b00001111);
   // PIC pinlerimizdeki b portunun 0,1,2,3 ü giriþ 4,5,6 yý çýkýþ olarak kullanacaðýz
   set_tris_d(0); // burada lcd pinlerini çýkýþ pini yapýyoruz.
   
   // alttaki c portu ledler için
   set_tris_c(0x00);
   output_c(0x00);
   
while(TRUE)
{     
   for(i=0;i<4;i++)   // yeni þifre belirlemeden önce sýfýrlýyoruz.
       pass[i]=0; 
       
   while(flag==0)
   {
      printf(lcd_putc,"\f4 rakamli\nSifre olustur");
      for(i=0;i<4;i++)
         pass[i]=keypaddd();
         
      for(i=0;i<4;i++)        // þifreyi alarm koduyla ayný oluþturduysa
          if(pass[i]!=alarm[i]) // tekrardan þifre giriþi yaptýrýcaz
            flag=1;

   }
   
   printf(lcd_putc,"\f");
   printf(lcd_putc,"Lutfen sifre\ngirisi yapin.");
   /*
   aþaðýdaki forda 3 defa yanlýþ girme hakký veriliyor. eðer 3 denemede doðru
   þifreyi girerse kapý açýlýcak, ancak 3 defa yanlýþ girerse alarm çalýcak.
   
   acil durum sessiz alarm kodu istediðiniz için kontrolünü ekstra yapacaðým.
   alarm kodu(1233)
   
   */
   int life;
   for(life=3;life>0;life--)
   {
      int kontrol=0;
      sayac=0;
      for(j=0;j<4;j++)        // þifre giriþi yaptýrýyoruz
         try[j]=keypaddd();
      for(j=0;j<4;j++)        // alarm ile þifre giriþini karþýlaþtýrýyoruz
          if(try[j]!=alarm[j] && sayac==0)
             sayac=1;  // herhangi bir farklýlýk olursa sayac 1 olacak 
             // yani bu durumda alarm kodunu girmemiþ oluyor.
            
             // sayacýn 0 olmasý durumu alarm kodunun girilmiþ olmasý demek.
             // bu durumda kapý açýlýp sessiz alarm durumuna geçiliyor.
      if(sayac==0) 
      {
         printf(lcd_putc,"\fHosgeldiniz.");
         life++;
         flag=0;
         for(j=0;j<10;j++)
            acildurum();
         break;
      }
      for(j=0;j<4;j++)        // normal þifre kontrolü yapýlýyor.
         if(try[j]!=pass[j])
            kontrol=1;
      
      if(kontrol==0) 
      { 
         output_high(pin_d2);                                                            
         printf(lcd_putc,"\fHosgeldiniz.");
         delay_ms(2000);
         output_low(pin_d2);
         life++;
         flag=0;
         break;
      }
      printf(lcd_putc,"\fKalan hak=%d\n",life-1);
       
   }
   if(life==0)
   {
      output_high(pin_d1); 
      printf(lcd_putc,"\fgiris basarisiz\nYeni sfre vakti");
      flag=0;
      delay_ms(2000);
      output_low(pin_d1);
      printf(lcd_putc,"\feski sifre=");
      for(j=0;j<4;j++)
      {
         printf(lcd_putc,"%d",pass[j]);
      }
      delay_ms(1000);
   }
   
 
   
}// while(true) bitiþi

}// main bitiþi
