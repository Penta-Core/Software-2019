/*
 * Sensoren.cpp
 *
 * Created: 22.06.2018 17:19:26
 *  Author: Ben Kast
 */ 

#include "Goldboard4.h"
#include "Variablen.h"

unsigned long last_abfrage = 0;

void bodenlicht_auslesen()
{
//sensoren hinten evtl anderer threshold value
//FILTER FÜR DIE WERTE!!!!!!!!!!!!!!!!!
	int value = us.getValue();
	
	for (int i = 0; i < 16; i++)
	{
		bodenlichtsensor_d[i] = value&(1<<i);
		/*
		bodenlichtsensor[i] = us.getanalogValue(i)/10;
		
		if(bodenlichtsensor[i] > 10)
		{
			bodenlichtsensor_d[i] = true;
		}
		else
		{
			bodenlichtsensor_d[i] = false;
		}*/
	}
	
	last_an = an;
	
	if (value != 0)
	{
		an = true;
	}
	else
	{
		an = false;
	}
}

void compass_auslesen()
{
	if (millis()- last_compass > COMPASS_ABFRAGE_ZEIT)
	{
		compass_alt = compass;
		compass = cmp.getValue();
		last_compass = millis();
	}
}

void ultraschall_auslesen()
{
	if (millis() - last_ultraschall > ULTRASCHALL_ABFRAGE_ZEIT)
	{
		ultraschall_hinten = hinten.getValueCM();
		last_ultraschall = millis();
	}
}

void pixy_auslesen()
{
	 //blocks selten >1
	
	if(millis() - letzte_abfrage > 27)
	{
		ball_x_alt = ball_x;
		ball_y_alt = ball_y;
		
		letzte_abfrage = millis();
		pixy_blocks = pixy_tk.getBlocks();
		
		ballnah = false;
		ballda = false;
		tor = false;
		int tor_x_summe = 0;
		int tor_y_summe = 0;
		int ball_x_summe = 0;
		int ball_y_summe = 0;
		
		if(pixy_blocks)
		{
			for (int i = 0; i < pixy_blocks; i++)
			{
				if(pixy_tk.blocks[i].signature == 1)
				{
					ballnah = true;
					baelle = baelle + 1;
					ball_x_summe = ball_x_summe + pixy_tk.blocks[i].x;
					ball_y_summe+=pixy_tk.blocks[i].y;
					
					ball_x = pixy_tk.blocks[i].x-160;
					ball_y = 240 - pixy_tk.blocks[i].y;
				}
				if (pixy_tk.blocks[i].signature == 2)
				{
					tor = true;
					tore++;
					tor_x_summe+=pixy_tk.blocks[i].x;
					tor_y_summe+=pixy_tk.blocks[i].y;
				}
			}
		}
		
		//ball_x = (0.1*ball_x_alt)+((0.9*(ball_x_summe/baelle))-160);
		//ball_y = (0.1*ball_y_alt)+(0.9*(ball_y_summe/baelle));		
		tor_x = (tor_x_summe/tore)-160;
		tor_y = tor_y_summe/tore;
	}
}

void buttons_auslesen()
{
	for (int i = 0; i < 9; i++)
	{
		oldbuttons[i] = buttons[i];
	}
	
	int pcf_value = taster.read();
	
	buttons[0] = pcf_value&(1<<0);
	buttons[1] = pcf_value&(1<<1);
	buttons[2] = pcf_value&(1<<2);
	buttons[3] = pcf_value&(1<<3);
	buttons[4] = pcf_value&(1<<4);
	buttons[5] = pcf_value&(1<<5);
	buttons[6] = pcf_value&(1<<6);
	buttons[7] = gb.getDigital(0);
	buttons[8] = gb.getDigital(1);
	
	for (int i = 0; i < 9; i++)
	{
		if(buttons[i])
			buttons[i] = false;
		else
			buttons[i] = true;
	}
}

void buttons_auslesen_spiel()
{
	buttons[8] = gb.getButton(0);
	buttons[9] = gb.getButton(1);
	
	if (buttons[8])
	{
		buttons[8] = false;
	}
	else
	{
		buttons[8] = true;
	}
	
	if (buttons[9])
	{
		buttons[9] = false;
	}
	else
	{
		buttons[9] = true;
	}
}

void sensorwerte_aktualisieren()
{
	bodenlicht_auslesen();	
	for (int i = 0; i < 16; i ++)
	{
		bodenlichtsensor[i] = us.getanalogValue(i);
	}	
		
	compass_auslesen();
	
	buttons_auslesen();
	
	ultraschall_auslesen();
	
	pixy_auslesen();
	
	lichtschranke = gb.getAnalog(7)+lichtschranke_referenz;
}

void sensorwerte_aktualisieren_spiel()
{
	bodenlicht_auslesen();	
	if (!an && millis() - last_abfrage > 50)
	{
		last_abfrage = millis();
		
		compass_auslesen();
		
		buttons_auslesen_spiel();
		
		ultraschall_auslesen();
		
		pixy_auslesen();
		
		lichtschranke = gb.getAnalog(7)+lichtschranke_referenz;
		
		gb.setLed(1,0);
		gb.setLed(0,0);
	}
	else
	{
		gb.setLed(1,1);
		gb.setLed(0,1);
	}
}
