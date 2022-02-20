/*
Kod ile ilgili bilgiler.
�ifreyi ilk program �al��t���nda kullan�c� eli ile belirliyor.
Sonras�nda giri� i�in tekrardan �ifre giri�i yapmal�d�r.
Sessiz alarm kodu "1233" d�r. Kullan�c� kendi �ifresini "1233" belirleyemez.  
bu durumuda tekrardan �ifre giri�i istenecektir.
Kullan�c�n�n do�ru �ifreyi girmesi i�in 3 hakk� vard�r. 3 deneyi�te de do�ru
giri� yapamaz ise giri� ba�ar�s�z uyar�s� verip do�ru �ifreyi g�sterip
yeni �ifre iste�i ile program devam eder.
�ifreyi belirledikten sonra do�ru giri� yapar ise 
-> ye�il led yanar lcdye ho�geldiniz yazar. sonra tekrar program ba�a d�ner.
alarm kodunu girdi�inde ise
-> Sar� led 10 defa yan�p s�ner acil durum anlam�nda. sonra program ba�a d�ner.
3 defa yanl�� �ifre girildi�inde ise
-> k�rm�z� led yanar sonra yukarda anlatt���m �ekilde yol izlenir.

proteusta kulland���m ayg�tlar
PIC = PIC16F877A
LCD = LM016L
Keypad= KEYPAD_PHONE
Led'ler(Sar�-K�rm�z�-Ye�il)

*/
#include <Sifrekilit.h>
#define LCD_ENABLE_PIN PIN_E0     // lcd enable -> e0 pinine att�k
#define LCD_RW_PIN PIN_E1        //  lcd rw -> e1 pinine 
#define LCD_RS_PIN PIN_E2        //  lcd rs -> e2 pinine
#define LCD_DATA4 PIN_D4         //  lcd data4 -> d4 pinine 
#define LCD_DATA5 PIN_D5         //  lcd data5 -> d5 pinine 
#define LCD_DATA6 PIN_D6         //  lcd data6 -> d6 pinine 
#define LCD_DATA7 PIN_D7         //  lcd data7 -> d7 pinine 

#fuses xt,nowdt,nolvp

#include <lcd.c>   // lcd k�t�phanesini eklememiz gerekiyor

void acildurum()
{
   output_high(pin_d0);
   delay_ms(200);
   output_low(pin_d0);
   delay_ms(200);
}


int keypaddd()    // keypaddan tus beklerken bu fonksiyona yollayaca��z.
{
    //    ----------------------------------------------------
   /*       Keypad tu� kontrol�
   
   Keypad kontrol� yaparken 4x3 l�k bir keypadim mevcut.
         Sat�rlar� a,b,c,d
         s�t�nlar� 1,2,3 olarak d���n�rsek 
         [a1 a2 a3] => [1 2 3]
         [b1 b2 b3] => [4 5 6]
         [c1 c2 c3] => [7 8 9]
         [d1 d2 d3] => [* 0 #]
         keypad'de kar��l�k gelen de�erler bunlar oluyor.
         Main i�erisinde tris ile PIC giri� pinlerimi sat�rlar olarak belirlemi�tim.
   */
   
   
   int i;
   char flag='h';    // herhangi bir tu�a bas�l�p bas�lmad���n� kontrol edecek
   for(i=0;i<2;i++)  // tu�a bas�laca�a kadar d�nmesi i�in kurdu�um d�ng�.
   {
      output_high(pin_b0);  // kontrolde 1.sat�r� aktif ediyor
      if(input(pin_b4)==1)  // 1.s�t�na bas�lm��sa geriye 1 de�eri d�n�yor
         {output_low(pin_b0);output_low(pin_b4);printf(lcd_putc,"1");return 1;}
      else if(input(pin_b5)==1)// 2.s�t�na bas�lm��sa geriye 2 de�eri d�n�yor
           {output_low(pin_b0);output_low(pin_b5);printf(lcd_putc,"2");return 2;}
           else if(input(pin_b6)==1)// 3.s�t�na bas�lm��sa geriye 1 de�eri d�n�yor
               {output_low(pin_b0);output_low(pin_b6);printf(lcd_putc,"3");return 3;}
  
      output_low(pin_b0);//1.sat�ra bas�lmad��� tespit edildi�inden pasif yap�yoruz.
      output_high(pin_b1); //2. sat�r�n kontrolu de ayn� �ekilde yap�yoruz.
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
      output_low(pin_b2); // ba�a d�nd���m�zde bas�l� tu� kalmamas� i�in
      output_low(pin_b3); // t�m pinleri kapat�yoruz.

  //    ----------------------------------------------------
   if(flag=='h') // e�erki return de�eri ile fonksiyondan ��kmad�ysak
      i=-1;       // h de�eri d�n�cektir. i mizi azaltaca��ndan
   }              // for d�ng�s� tekrar tekrar �al��acakt�r.
  return -1;      // herhangi bir tu�a bas�laca�a kadar.

}





void main()
{
   lcd_init(); // Lcd kendini ayarlamas� i�in main i�erisinde bu kodu yaz�yoruz.
   /*
   led kodlar�
   \f lcd ekran�n� temizler ve imleci ba�a al�r
   \a imleci en ba�a al�r(silmeden)
   \n alt sat�ra ge�er
   \b bir karakter imleci geri kayd�r�r. 
   */
   int pass[4],i,j; // kullan�c�dan �ifre al�nacak
   int try[4]; // giri� yapmay� denerken �ifre dizisi
   int alarm[]={1,2,3,3},sayac=0; // sessiz alarm i�in
   char flag=0; // ilk giri�te �ifre al�nmas� veya �ifre de�i�tirmek i�in
   
   set_tris_b(0b00001111);
   // PIC pinlerimizdeki b portunun 0,1,2,3 � giri� 4,5,6 y� ��k�� olarak kullanaca��z
   set_tris_d(0); // burada lcd pinlerini ��k�� pini yap�yoruz.
   
   // alttaki c portu ledler i�in
   set_tris_c(0x00);
   output_c(0x00);
   
while(TRUE)
{     
   for(i=0;i<4;i++)   // yeni �ifre belirlemeden �nce s�f�rl�yoruz.
       pass[i]=0; 
       
   while(flag==0)
   {
      printf(lcd_putc,"\f4 rakamli\nSifre olustur");
      for(i=0;i<4;i++)
         pass[i]=keypaddd();
         
      for(i=0;i<4;i++)        // �ifreyi alarm koduyla ayn� olu�turduysa
          if(pass[i]!=alarm[i]) // tekrardan �ifre giri�i yapt�r�caz
            flag=1;

   }
   
   printf(lcd_putc,"\f");
   printf(lcd_putc,"Lutfen sifre\ngirisi yapin.");
   /*
   a�a��daki forda 3 defa yanl�� girme hakk� veriliyor. e�er 3 denemede do�ru
   �ifreyi girerse kap� a��l�cak, ancak 3 defa yanl�� girerse alarm �al�cak.
   
   acil durum sessiz alarm kodu istedi�iniz i�in kontrol�n� ekstra yapaca��m.
   alarm kodu(1233)
   
   */
   int life;
   for(life=3;life>0;life--)
   {
      int kontrol=0;
      sayac=0;
      for(j=0;j<4;j++)        // �ifre giri�i yapt�r�yoruz
         try[j]=keypaddd();
      for(j=0;j<4;j++)        // alarm ile �ifre giri�ini kar��la�t�r�yoruz
          if(try[j]!=alarm[j] && sayac==0)
             sayac=1;  // herhangi bir farkl�l�k olursa sayac 1 olacak 
             // yani bu durumda alarm kodunu girmemi� oluyor.
            
             // sayac�n 0 olmas� durumu alarm kodunun girilmi� olmas� demek.
             // bu durumda kap� a��l�p sessiz alarm durumuna ge�iliyor.
      if(sayac==0) 
      {
         printf(lcd_putc,"\fHosgeldiniz.");
         life++;
         flag=0;
         for(j=0;j<10;j++)
            acildurum();
         break;
      }
      for(j=0;j<4;j++)        // normal �ifre kontrol� yap�l�yor.
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
   
 
   
}// while(true) biti�i

}// main biti�i
