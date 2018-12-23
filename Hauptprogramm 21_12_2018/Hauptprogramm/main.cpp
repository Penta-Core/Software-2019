 /** Project Name: goldboard4_V1_1 
	Team: TheKingsOfSoccer
	-- GoldBoard V4.0 Soccer Program --
**/
 
//Pixy Abfrage testen!!!

#include "Goldboard4.h"
#include "Variablen.h"
#include "Display.h"

Goldboard4 gb;
usring us;
SRF08 hinten;
PCF8574A taster;
CMPS11 cmp;
PixyI2C pixy_tk;

void reset_values()
{
	LCDinit();
	LCDcls();
	us.init();
	us.setThresholdValueGolbal(180); //IR ca. 180 Schwellwert
	us.setFilterValue(10); //Filter Wert, Wert ausprobieren
	taster.init(34);
	cmp.init();
	cmp.setAs128Degree();
	pixy_tk.init();
	hinten.init(0);
	gb.setDigital(3,false);
	delay(250);
	lichtschranke_referenz = 255-gb.getAnalog(7);
	gb.setDigital(3,true);
	/*for(int i = 0; i < 4; i++)
		gb.motor[i].setAcceleration(50);*/
}

int main(void)
{	
	reset_values();
 
	while(1)
	{
		SERIAL_PRINTLN("passed");
		gb.scanI2C();
		
		displaysteuerung();
		
		if(raus)
		{
			break;
		}
	}
	
	LCDcls();
	
	/*int last = 0;
	
	while(1){
		sensorwerte_aktualisieren_spiel();
		
		if (millis()-last > 500)
		{
			last = millis();
			
			for (int i = 0; i < 16; i++)
			{
				SERIAL_PRINT(bodenlichtsensor_d[i]);
			}
			
			SERIAL_PRINTLN("");
		}
		
		if (an)
			linie_wegfahren();
		else
			fahren(0,0,0);
	}*/
		
	while (true)
	{		
		SERIAL_PRINTLN("Passed");
		
		sensorwerte_aktualisieren_spiel();
		
		if(ball_y < 50 && ball_y > 0 && compass > 100 && compass < 160) {ballda = true; ballnah = false;} 

		if (an)
		{
			//linie_wegfahren();
		}
		else
		{
			//fahren(0,0,0);
			//compass=128;
			//pixy_auslesen();
			//ballfahren_torwart();
		}
		
		if (buttons[8] && buttons[9])
		{//while true mit displaysteuerung...!!
			fahren(0,0,0);
		}
	}
}
