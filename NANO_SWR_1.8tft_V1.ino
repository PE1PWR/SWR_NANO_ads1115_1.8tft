//############################################################################################
//This software is free to use. Its a SWR for HF, UHF and VHF. ( PE1PWR Wim Schilperoort)
//Its based on a NANO with TFT ST7735 Blue version display 3.2 inch ads1115 and a Arduino 5 volt relay. 
//For more precision I have used a asd1115 AD converter. 
//You can used a relay for transceiver protection. D7 is allready in the script for 5 volt Arduino relay. 
//Protection niveau will be for a SWR of 1:3 and higher. It will activated relay till SWR is below 1:3. 
//##############################################################################################
// TFT color definiton
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define YELLOW 0xFFE0
#define WHITE 0xFFFF


#include "SPI.h"
#include "Adafruit_GFX.h"
#include <Adafruit_ST7735.h>
#define cs   10
#define dc   9
#define rst  8
Adafruit_ST7735 tft = Adafruit_ST7735(cs, dc, rst); // hardware spi D13=CLK D11=DIN Led=5v/3v
#include <Wire.h>
#include <Adafruit_ADS1015.h>
Adafruit_ADS1115 ads(0x48);
      float Vfwd = 0.0;      
      float Vrev = 0.0;   

// Varibles      
      float Pfwd;
      float Prev;
      float SWR;
      const int relay = 7;  
   
       
   void setup(){ 
       tft.initR(INITR_BLACKTAB);     // initialize a ST7735S chip, black tab
       ads.begin(); 
       pinMode(relay, OUTPUT);
       tft.fillScreen(ST7735_BLUE);
       tft.setRotation(0);
       tft.setTextColor(ST7735_WHITE, ST7735_BLUE);  
       tft.setCursor (0, 1);  // go to Column, Row   
       tft.print(" === Transmitting === ");
       tft.setTextColor(ST7735_WHITE, ST7735_BLUE); 
       tft.setTextSize(1);          
       tft.setCursor (0,15);  
       tft.print(" FWD ");
       tft.setCursor (0,60);           
       tft.print(" REV ");        
       tft.setCursor (0,110);           
       tft.print(" SWR ");     
       tft.setCursor (0,30);  
       tft.print(" 1 2 3 4 5 6 7 8 9 10");
       tft.setCursor (0,75);  
       tft.print(" 1 2 3 4 5 6 7 8 9 10");
       tft.setCursor (0,125);  
       tft.print("  1:1 1:2 1:3 ");
       tft.setCursor (0,125);  
       tft.setTextColor(ST7735_RED, ST7735_BLUE);  
       tft.setCursor (95,125);
       tft.print("1:5 ");
   }
void loop()  
{    // start of main loop                

    {
         int16_t adc0;
         int16_t adc1;
         adc0 = ads.readADC_SingleEnded(0);
         adc1 = ads.readADC_SingleEnded(1);
         Vfwd = (adc0 * 0.1875)/1000;
         Vrev = (adc1 * 0.1875)/1000;
        } 
     
         Pfwd = (Vfwd * Vfwd)*10.5;
         Prev = (Vrev * Vrev)*10.5;         
         float fp = sqrt ( Prev / Pfwd ); // Formula SWR Prev / Pfwd int is fp
         SWR = ( 1 + fp ) / ( 1 - fp ); // Formula second part SWR 1+fp / 1-fp                          
         SWR = constrain(SWR, 1, 99.9); // some more than 100 // go further 
          
        
  
       
       
       // print PWR
       tft.setTextColor(ST7735_WHITE, ST7735_BLUE); 
       tft.setTextSize(1);           
       tft.setCursor (30,15) ;           // go to Column, Row                                 
       tft.print(Pfwd, 1);      // displays forward power as xx.x value    //  ",1" means one decimal place 
       tft.print("    ");     // to clear trailing digits

        //  FWD bargraph
           tft.setTextSize(1);
           tft.setTextColor(ST7735_GREEN, ST7735_BLUE); 
           tft.setRotation(45);  
           int pwr = (Pfwd / 108) * 123;
           tft.drawRect(39, 2, 12, 125,ST7735_WHITE);
           tft.fillRect(40,126-pwr,10,pwr,ST7735_GREEN);
           tft.fillRect(40,126-123,10,123-pwr,ST7735_BLACK);
           tft.setRotation(0); 
           
           //  end bargraph          
                          
      // print REV
         tft.setTextSize(1);   
         tft.setTextColor(ST7735_WHITE, ST7735_BLUE);       
         tft.setCursor (30,60);           // go to Column, Row            
         tft.print(Prev, 1);      // displays forward power as xx.x value    //  ",1" means one decimal place 
         tft.print("    ");     // to clear trailing digits
           
           //  REV bargraph
           tft.setTextSize(1);
           tft.setTextColor(ST7735_GREEN, ST7735_BLUE); 
           tft.setRotation(45);  
           int rev = (Prev / 110) * 123;
           tft.drawRect(84, 2, 12, 125,ST7735_WHITE);
           tft.fillRect(85,126-rev,10,rev,ST7735_GREEN);
           tft.fillRect(85,126-123,10,123-rev,ST7735_BLACK);
           tft.setRotation(0); 
            //  end bargraph

          // print SWR
         tft.setTextColor(ST7735_WHITE, ST7735_BLUE);        
         tft.setCursor (30,110);           // go to Column, Row            
         tft.print(SWR, 1);      // displays forward power as xx.x value    //  ",1" means one decimal place
          if (SWR >= 3)
           digitalWrite(relay, HIGH);
           if (SWR <= 3)
           digitalWrite(relay, LOW); 
         tft.print("     ");     // to clear trailing digits
           
           // SWR bargraph
           tft.setTextSize(1);
           tft.setTextColor(ST7735_GREEN, ST7735_BLUE); 
           tft.setRotation(45);  
           int swr = (SWR / 6) * 123;
           tft.drawRect(134, 2, 12, 125,ST7735_WHITE);
           tft.fillRect(135,126-swr,10,swr,ST7735_GREEN);
           tft.fillRect(135,126-123,10,123-swr,ST7735_BLACK);
           tft.setRotation(0); // rotate screen start position
           //  end bargraph


   
      

   } // End loop      


     
 
