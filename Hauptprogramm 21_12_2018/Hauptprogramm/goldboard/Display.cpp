/***********************************
void sendCommand_init(uint8_t cmd)
void sendData(uint8_t data)
void sendCommand(uint8_t cmd)
***********************************/

/*
Pinbelegung		vgl. www.wiki.rocci.net

Display	PCF8574
0		9
1		10
2		11
3		12
4		7/6
5		6/7
*/

#include "Display.h"

//I2C Adresse
//#define LCD_ADR 0x27
//#define LCD_ADR 0X4E //i2c; portexpander GB4
//#define LCD_ADR 0b01111110  //portexpander GB4
#define LCD_ADR 0b01001010 //portexpander LCD Platine Ben //evtl 0 am ende entfernen
//#define LCD_ADR 0x4A


//Displaygröße
#define LCD_X 24
#define LCD_Y 4

//Befehle für HD44780
#define CLS      0x01  // Displayinhalt löschen
#define HOME     0x02  // Cursor nach links oben
#define DISPDATA 0x80  // Display-Daten schreiben

#define EN       0x04  // Enable auf high

#define WR_CMD1  0x08  // Befehl schreiben 1
#define WR_CMD2  0x0C  // Befehl schreiben 2 
#define WR_CMD3  0x08  // Befehl schreiben 3 

#define WR_DATA1 0x09  // Daten schreiben 1 
#define WR_DATA2 0x0D  // Daten schreiben 2 
#define WR_DATA3 0x09  // Daten schreiben 3 

//Cursor Position
uint8_t cur_x;     // Spalte
uint8_t cur_y;     // Zeile



//Befehl an LCD-Anzeige senden
void sendCommand(uint8_t cmd)
{

  uint8_t cmd1 = cmd&0xF0;
  uint8_t cmd2 = cmd<<4;
  
  uint8_t cmd1WRCMD2 = cmd1+WR_CMD2;
  uint8_t cmd1WRCMD1 = cmd1+WR_CMD1;
  uint8_t cmd2WRCMD2 = cmd2+WR_CMD2;
  uint8_t cmd2WRCMD1 = cmd2+WR_CMD1;

  i2cWriteToSlave(LCD_ADR, &cmd1WRCMD2, 1);
  delay(1); //E=1
  i2cWriteToSlave(LCD_ADR, &cmd1WRCMD1, 1);
  delay(1); //obere 4 bits  

  i2cWriteToSlave(LCD_ADR, &cmd2WRCMD2, 1);
  delay(1); //E=1 
  i2cWriteToSlave(LCD_ADR, &cmd2WRCMD1, 1);
  delay(1); //untere 4 bits 

}

//Daten an LCD-Anzeige senden
void sendData(uint8_t data)
{

  uint8_t data1 = data&0xF0;
  uint8_t data2 = data<<4;
  
  uint8_t data1WRDATA2 = data1+WR_DATA2;
  uint8_t data1WRDATA1 = data1+WR_DATA1;
  uint8_t data2WRDATA2 = data2+WR_DATA2;
  uint8_t data2WRDATA1 = data2+WR_DATA1;
  
  i2cWriteToSlave(LCD_ADR, &data1WRDATA2, 1);
  delay(1); //E=1
  i2cWriteToSlave(LCD_ADR, &data1WRDATA1, 1);
 delay(1); //obere 4 bits
  
  i2cWriteToSlave(LCD_ADR, &data2WRDATA2, 1);
  delay(1); //E=1
  i2cWriteToSlave(LCD_ADR, &data2WRDATA1, 1);
 delay(1); //untere 4 bits
  
}

//Cursorposition ans Display senden
void loc8()
{
  uint8_t pos = 0x00; 
  
  if(cur_y==0)      //Zeile 1
    pos=0;                      //dez:0
  else if(cur_y==1) //Zeile 2
    pos = 0x40;                 //0x40 dez:64
  else if(cur_y==2) //Zeile 3
    pos = 0x14;                 //0x14 dez:20   0x10 dez:16
  else if(cur_y==3) //Zeile 4
    pos = 0x54;                 //0x54 dez:84   0x50 dez:80

  pos += cur_x;                         // Neue Position berechnen   

  sendCommand(DISPDATA + pos);  //ans Display senden 
}

//Form des Cursors festlegen 
void LCDsetCursor(uint8_t curmode)//0-kein Cursor 1-Rechteck blinkend 2-Unterstrich 3-Unterstrich und Rechteck blinkend
{
  curmode &= 0x03;   // Nur die untersten 2 Bits behalten
  sendCommand(0x0C + curmode);
}

void sendCommand_init(uint8_t cmd)
{
  uint8_t cmdEN = cmd + EN;

  i2cWriteToSlave(LCD_ADR, &cmdEN, 1);//E=1 
  delay(1);
  i2cWriteToSlave(LCD_ADR, &cmd, 1);//E=0
  delay(1);

}

//Display-Controller initialisieren 
void LCDinit()
{
    delay(50);
 sendCommand_init(0x30);  //display startet im 8bit modus
delay(1);
 sendCommand_init(0x30);
delay(1);
 sendCommand_init(0x30);
delay(1);
 
 sendCommand_init(0x20);  //4bit mode
delay(1);
 
 sendCommand(0x28);  //function set
 sendCommand(0x0F);  //display
 sendCommand(0x06);  //entry mode set
 
 sendCommand(HOME);
    sendCommand(CLS);
 cur_x = 0;
    cur_y = 0;
    loc8();
}


//Cursor nach oben links setzen
void LCDhome()
{
  cur_x = 0;
  cur_y = 0;
  loc8();
}

//Bildschirm löschen 
void LCDcls()
{
  sendCommand(CLS);
  delay(2);
  //LCDhome();
}

//Cursor positionieren
void LCDlocate(int pos_x, int pos_y)
{
  if(pos_x < LCD_X)
    cur_x = pos_x;

  if(pos_y < LCD_Y)
    cur_y = pos_y;

  loc8();
}

//einzelnes Zeichen ausgeben
void LCDputc(char zeich)
{
  sendData(zeich);     // Zeichen ans Display senden

  cur_x++;             // Cursor 1 Schritt nach rechts 
                       //nächste Position berechnen
  if(cur_x>=LCD_X)
  {
   cur_x=0;
   cur_y++;
   if(cur_y>=LCD_Y)
     cur_y=0;
  }
  
  loc8();
}

//Text ausgeben
void LCDprint_text(const char* text)
{ 
  while(*text != 0)  
    LCDputc(*text ++);
}
void LCDprint_text(int y, int x, const char* text)
{
  LCDlocate(x,y);
  LCDprint_text(text);
}

//Zahl ausgeben (-32768 bis 32767)
void LCDprint_num(int num)
{
  if(num < 0)  
  {   
    LCDputc('-');
 num*=-1;
  }  
  
  bool zeros = false;  //führend Nullen nicht drucken
  uint8_t ziff;
  uint8_t pzif;

  ziff = num/10000;   // 10000er Stellen berechnen 
  num = num%10000;
  pzif = ziff+0x30;   // ASCII-Code für 0..9 
  if(ziff!=0)
  {
    zeros=true;  
    LCDputc(pzif);
  }    
  
  ziff = num/1000;   // 1000er Stellen berechnen
  num = num%1000;
  pzif = ziff+0x30;  
  if((ziff!=0)||zeros==true)
  {
    zeros=true;
    LCDputc(pzif);
  }  

  ziff=num / 100;    // 100er Stellen berechnen
  num=num % 100;
  pzif=ziff+0x30;
  if((ziff!=0)||zeros==true)
  {
    zeros=true;
    LCDputc(pzif);
  }

  ziff=num/10;    // 10er Stellen berechnen
  num=num%10;
  pzif=ziff+0x30;  
  if((ziff!=0)||zeros==true)
  {
    zeros=true;
    LCDputc(pzif);
  }
  
  // 1er Stellen anhängen 
  LCDputc(num + 0x30);
} 
void LCDprint_num(int y, int x, int num)
{
  LCDlocate(x,y);
  LCDprint_num(num);
}


