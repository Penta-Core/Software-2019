/*
 * Displaysteuerung.cpp
 *
 * Created: 22.06.2018 17:25:11
 *  Author: Ben Kast
 */

#include "Goldboard4.h"
#include "Variablen.h"
#include "Display.h"

void menue_start()
{
	buttons_auslesen();
	LCDprint_text(0,2,"TheKingsOfSoccer");
	LCDprint_text(1,0,"Start");
	LCDprint_text(2,0,"Sensoren");
	LCDprint_text(3,0,"Motorboard");
	LCDprint_text(cursor,19,"X");
	
	LCDprint_num(0,19,cursor);
	
	if(buttons[1])
	{
		cursor --;
	}
	else if (buttons[3])
	{
		cursor++;
	}
	else if (buttons[0])
	{
		if(cursor == 1){
			raus = true;
		}
		else if (cursor == 2){
			aktuelles_menue = SENSOREN_A;
			cursor = 1;
			delay(200);
		}
		else
		{
			aktuelles_menue = MOTORBOARD;
			cursor = 1;
			delay(200);
		}
	}
	
	if(cursor == 4)
	{
		cursor = 3;
	}
	else if (cursor < 1)
	{
		cursor = 1;
	}
}

void menue_sensoren_a()
{
	LCDprint_text(0,0,"SensorenA");
	LCDprint_text(0,13,"-->B");
	LCDprint_text(1,0,"Boden");
	LCDprint_text(2,0,"Pixy");
	LCDprint_text(3,0,"Ultraschall");
	LCDprint_text(cursor,19,"X");
	
	if(buttons[1])
	{
		cursor --;
	}
	else if (buttons[3])
	{
		cursor ++;
	}
	else if (buttons[2])
	{
		aktuelles_menue = SENSOREN_B;
		delay(200);
		cursor = 1;
	}
	else if (buttons[4])
	{
		aktuelles_menue = SENSOREN_B;
		delay(200);
		cursor = 1;
	}
	else if (buttons[0])
	{
		if(cursor == 1){
			aktuelles_menue = BODEN_A;
			delay(200);
		}
		else if (cursor == 2){
			aktuelles_menue = PIXY;
			delay(200);
		}
		else
		{
			aktuelles_menue = ULTRASCHALL;
			delay(200);
		}
	}
	else if (buttons[7])
	{
		aktuelles_menue = START;
		cursor = 2;
		delay(500);
	}
	
	if(cursor > 3)
	cursor = 3;
	else if (cursor < 1)
	cursor = 1;
}

void menue_sensoren_b()
{
	LCDprint_text(0,5,"SensorenB");
	LCDprint_text(0,16,"-->A");
	LCDprint_text(1,0,"Compass");
	LCDprint_text(2,0,"Buttons");
	LCDprint_text(3,0,"LS,Ball");
	LCDprint_text(cursor,19,"X");
	
	if(buttons[1])
	{
		cursor--;
	}
	else if (buttons[2])
	{
		aktuelles_menue = SENSOREN_A;
		delay(200);
		cursor = 1;
	}
	else if (buttons[3])
	{
		cursor++;
	}
	else if (buttons[4])
	{
		aktuelles_menue = SENSOREN_A;
		delay(200);
		cursor = 1;
	}
	else if (buttons[0])
	{
		if(cursor == 1){
			aktuelles_menue = COMPASS;
			delay(200);
		}
		else if (cursor == 2){
			aktuelles_menue = BUTTONS;
			delay(200);
		}
		else
		{
			aktuelles_menue = LICHTSCHRANKE;
			delay(200);
		}
	}
	else if (buttons[7])
	{
		aktuelles_menue = START;
		cursor = 2;
		delay(500);
	}
	
	if(cursor > 3)
		cursor = 3;
	else if (cursor < 1)
		cursor = 1;
}


void menues_sensoren() 
{
	if(millis()-last_cls > 1000)
	{
		LCDcls();
		last_cls = millis();
	}
	
	if(buttons[7])
	{
		aktuelles_menue = SENSOREN_A;
		cursor = 1;
		delay(500);
	}
	
	if(aktuelles_menue == BODEN_A && !buttons[6])
	{
		if(buttons[0] || buttons[1] || buttons[2] || buttons[3] || buttons[4])
		{
			aktuelles_menue = BODEN_B;
			delay(200);
		}
		//UUU vermeide sich widerholenden Code
		LCDprint_text(0,7,"BODEN");
		LCDprint_num(1,4,0);
		LCDprint_num(1,11,1);
		LCDprint_num(2,4,2);
		LCDprint_num(2,11,3);
		LCDprint_num(3,4,4);
		LCDprint_num(3,11,5);
		LCDprint_text(1,5,":");
		LCDprint_text(1,12,":");
		LCDprint_text(2,5,":");
		LCDprint_text(2,12,":");
		LCDprint_text(3,5,":");
		LCDprint_text(3,12,":");
		LCDprint_num(1,6,bodenlichtsensor_d[0]);
		LCDprint_num(1,13,bodenlichtsensor_d[1]);
		LCDprint_num(2,6,bodenlichtsensor_d[2]);
		LCDprint_num(2,13,bodenlichtsensor_d[3]);
		LCDprint_num(3,6,bodenlichtsensor_d[4]);
		LCDprint_num(3,13,bodenlichtsensor_d[5]);
	}
	else if(aktuelles_menue == BODEN_B && !buttons[6])
	{
		if(buttons[0] || buttons[1] || buttons[2] || buttons[3] || buttons[4])
		{
			aktuelles_menue = BODEN_C;
			delay(200);
		}
		//UUU vermeide sich widerholenden Code
		LCDprint_text(0,7,"BODEN");
		LCDprint_num(1,4,6);
		LCDprint_num(1,11,7);
		LCDprint_num(2,4,8);
		LCDprint_num(2,11,9);
		LCDprint_num(3,4,10);
		LCDprint_num(3,11,11);
		LCDprint_text(1,5,":");
		LCDprint_text(1,12,":");
		LCDprint_text(2,5,":");
		LCDprint_text(2,12,":");
		LCDprint_text(3,6,":");
		LCDprint_text(3,13,":");
		LCDprint_num(1,6,bodenlichtsensor_d[6]);
		LCDprint_num(1,13,bodenlichtsensor_d[7]);
		LCDprint_num(2,6,bodenlichtsensor_d[8]);
		LCDprint_num(2,13,bodenlichtsensor_d[9]);
		LCDprint_num(3,7,bodenlichtsensor_d[10]);
		LCDprint_num(3,14,bodenlichtsensor_d[11]);
	}
	else if(aktuelles_menue == BODEN_C && !buttons[6])
	{
		if(buttons[0] || buttons[1] || buttons[2] || buttons[3] || buttons[4])
		{
			aktuelles_menue = BODEN_A;
			delay(200);
		}
		
		LCDprint_text(0,7,"BODEN");
		LCDprint_num(2,3,12);
		LCDprint_num(2,10,13);
		LCDprint_num(3,3,14);
		LCDprint_num(3,10,15);
		LCDprint_text(2,5,":");
		LCDprint_text(2,12,":");
		LCDprint_text(3,5,":");
		LCDprint_text(3,12,":");
		LCDprint_num(2,6,bodenlichtsensor_d[12]);
		LCDprint_num(2,13,bodenlichtsensor_d[13]);
		LCDprint_num(3,6,bodenlichtsensor_d[14]);
		LCDprint_num(3,13,bodenlichtsensor_d[15]);
	}
	else if(aktuelles_menue == BODEN_A && buttons[6])
	{
		if(buttons[0] || buttons[1] || buttons[2] || buttons[3] || buttons[4])
		{
			aktuelles_menue = BODEN_B;
			delay(200);
		}
		
		LCDprint_text(0,7,"BODEN");
		LCDprint_num(1,4,0);
		LCDprint_num(1,11,1);
		LCDprint_num(2,4,2);
		LCDprint_num(2,11,3);
		LCDprint_num(3,4,4);
		LCDprint_num(3,11,5);
		LCDprint_text(1,5,":");
		LCDprint_text(1,12,":");
		LCDprint_text(2,5,":");
		LCDprint_text(2,12,":");
		LCDprint_text(3,5,":");
		LCDprint_text(3,12,":");
		LCDprint_num(1,6,us.getanalogValue(0));
		LCDprint_num(1,13,us.getanalogValue(1));
		LCDprint_num(2,6,us.getanalogValue(2));
		LCDprint_num(2,13,us.getanalogValue(3));
		LCDprint_num(3,6,us.getanalogValue(4));
		LCDprint_num(3,13,us.getanalogValue(5));
	}
	else if(aktuelles_menue == BODEN_B && buttons[6])
	{
		if(buttons[0] || buttons[1] || buttons[2] || buttons[3] || buttons[4])
		{
			aktuelles_menue = BODEN_C;
			delay(200);
		}
		
		LCDprint_text(0,7,"BODEN");
		LCDprint_num(1,4,6);
		LCDprint_num(1,11,7);
		LCDprint_num(2,4,8);
		LCDprint_num(2,11,9);
		LCDprint_num(3,3,10);
		LCDprint_num(3,10,11);
		LCDprint_text(1,5,":");
		LCDprint_text(1,12,":");
		LCDprint_text(2,5,":");
		LCDprint_text(2,12,":");
		LCDprint_text(3,5,":");
		LCDprint_text(3,12,":");
		LCDprint_num(1,6,us.getanalogValue(6));
		LCDprint_num(1,13,us.getanalogValue(7));
		LCDprint_num(2,6,us.getanalogValue(8));
		LCDprint_num(2,13,us.getanalogValue(9));
		LCDprint_num(3,6,us.getanalogValue(10));
		LCDprint_num(3,13,us.getanalogValue(11));
	}
	else if(aktuelles_menue == BODEN_C && buttons[6])
	{
		if(buttons[0] || buttons[1] || buttons[2] || buttons[3] || buttons[4])
		{
			aktuelles_menue = BODEN_A;
			delay(200);
		}
		
		LCDprint_text(0,7,"BODEN");
		LCDprint_num(2,3,12);
		LCDprint_num(2,10,13);
		LCDprint_num(3,3,14);
		LCDprint_num(3,10,15);
		LCDprint_text(2,5,":");
		LCDprint_text(2,12,":");
		LCDprint_text(3,5,":");
		LCDprint_text(3,12,":");
		LCDprint_num(2,6,us.getanalogValue(12));
		LCDprint_num(2,13,us.getanalogValue(13));
		LCDprint_num(3,6,us.getanalogValue(14));
		LCDprint_num(3,13,us.getanalogValue(15));
	}
	else if (aktuelles_menue == COMPASS)
	{
		LCDprint_text(0,5,"COMPASS");
		LCDprint_num(1,0,compass);
		LCDprint_text(2,0,"Calibrate");
		LCDprint_text(2,19,"X");
		
		if(buttons[0])
		{
			cmp.startCalibration();
			delay(1000);
			
			while(!buttons[7])
			{
				buttons_auslesen();
				gb.setLed(1,1);
			}
			
			cmp.exitCalibration();
			
			delay(500);
			
			gb.setLed(1,0);
			
			cmp.setAs128Degree();
		}
	}
	else if (aktuelles_menue == ULTRASCHALL)
	{
		LCDprint_text(0,4,"ULTRASCHALL");
		LCDprint_text(2,0,"H:");
		LCDprint_num(2,2,ultraschall_hinten);
	}
	else if (aktuelles_menue == PIXY)
	{
		LCDprint_text(0,6,"PIXY");
		LCDprint_text(1,0,"Blocks:");
		LCDprint_num(1,8,pixy_blocks);
		LCDprint_text(2,0,"Ball:");
		LCDprint_text(2,4,"X:");
		LCDprint_num(2,6,ball_x);
		LCDprint_text(2,10,"Y:");
		LCDprint_num(2,12,ball_y);
		LCDprint_num(2,16,ballnah);
		LCDprint_text(3,0,"Tor:");
		LCDprint_text(3,4,"X:");
		LCDprint_num(3,6,tor_x);
		LCDprint_text(3,10,"Y:");
		LCDprint_num(3,12,tor_y);
		LCDprint_num(3,16,tor); 
	}
	else if (aktuelles_menue == BUTTONS)
	{
		LCDprint_text(0,6,"BUTTONS");
		
		LCDprint_num(1,0,0);
		LCDprint_text(1,1,":");
		LCDprint_num(1,2,buttons[0]);
		LCDprint_num(2,0,1);
		LCDprint_text(2,1,":");
		LCDprint_num(2,2,buttons[1]);
		LCDprint_num(3,0,2);
		LCDprint_text(3,1,":");
		LCDprint_num(3,2,buttons[2]);
		LCDprint_num(1,8,3);
		LCDprint_text(1,9,":");
		LCDprint_num(1,10,buttons[3]);
		LCDprint_num(2,8,4);
		LCDprint_text(2,9,":");
		LCDprint_num(2,10,buttons[4]);
		LCDprint_num(3,8,5);
		LCDprint_text(3,9,":");
		LCDprint_num(3,10,buttons[5]);
		LCDprint_num(1,17,6);
		LCDprint_text(1,18,":");
		LCDprint_num(1,19,buttons[6]);
		LCDprint_num(2,17,7);
		LCDprint_text(2,18,":");
		LCDprint_num(2,19,buttons[7]);
		LCDprint_num(3,17,8);
		LCDprint_text(3,18,":");
		LCDprint_num(3,19,buttons[8]);
	}
	else if(aktuelles_menue == LICHTSCHRANKE)
	{
		LCDprint_text(0,3,"Lichtschranke");
		LCDprint_num(1,3,lichtschranke);
		LCDprint_text(2,5,"Ballnah:");
		LCDprint_num(3,5,ballnah);
	}
}

void menue_motorboard()
{
	LCDprint_text(0,3,"Motorboard");
	LCDprint_text(1,0,"Motoren");
	LCDprint_text(2,0,"Power");
	LCDprint_text(3,0,"TKOS");
	LCDprint_text(3,5,"FUR");
	LCDprint_text(3,9,"DEUTSCHLAND");
	LCDprint_text(cursor,19,"X");
	
	if (buttons[0])
	{
		if(cursor == 1)
		{
			aktuelles_menue = MOTOREN;
			cursor = 1;
			delay(200);
		}
		else if(cursor == 2)
		{
			aktuelles_menue = POWER;
			cursor = 1;
			delay(200);
		}
	}
	else if (buttons[1])
	{
		cursor--;
		delay(200);
	}
	else if (buttons[3])
	{
		cursor++;
		delay(200);
	}
	else if (buttons[7])
	{
		aktuelles_menue = START;
		cursor = 1;
		delay(500);
	}
	
	if(cursor > 2)
	cursor = 2;
	else if (cursor < 1)
	cursor = 1;
}

int richt_lcd = 0;
bool drall_lcd = false;
int speed_lcd = 255;

void menue_motoren()
{
	LCDprint_text(0,5,"Motoren");
	LCDprint_text(1,0,"Richt");
	LCDprint_text(1,7,"-");
	LCDprint_num(1,9,richt_lcd);
	LCDprint_text(1,12,"+");
	LCDprint_text(3,0,"Drall:");
	if(drall_lcd)
	LCDprint_text(3,7,"Ja");
	else
	LCDprint_text(3,7,"Nein");
	LCDprint_text(2,0,"Speed");
	LCDprint_num(2,7,speed_lcd);
	LCDprint_text(cursor,19,"X");
	
	if(buttons[0])
	{
		unsigned long start = millis();
		while(millis()-start < 10000)
		{
			sensorwerte_aktualisieren();
			
			if(drall_lcd)
				fahren(richt_lcd,speed_lcd);
			else
				fahren(richt_lcd,speed_lcd,0);
		}
		fahren(0,0,0);
	}
	else if(buttons[1])
	{
		cursor--;
		delay(200);
	}
	else if (buttons[2])
	{
		if(cursor == 1)
		{
			richt_lcd -= 10;
		}
		else if (cursor == 3)
		{
			if(drall_lcd)
				drall_lcd = false;
			else
				drall_lcd = true;
		}
		else if (cursor == 2)
		{
			speed_lcd-=10;
		}
		delay(200);
	}
	else if (buttons[3])
	{
		cursor++;
		delay(200);
	}
	else if (buttons[4])
	{
		if(cursor == 1)
		{
			richt_lcd += 10;
		}
		else if (cursor == 3)
		{
			if(drall_lcd)
				drall_lcd = false;
			else
				drall_lcd = true;
		}
		else if (cursor == 2)
		{
			speed_lcd+=10;
		}
		delay(200);
	}
	else if (buttons[7])
	{
		aktuelles_menue = MOTORBOARD;
		cursor = 1;
		delay(200);
	}
	
	if(cursor > 3)
	cursor = 3;
	else if (cursor < 1)
	cursor = 1;
}

bool dribbler_state = 0;

void menue_power()
{
	LCDprint_text(0,6,"Power");
	LCDprint_text(1,0,"Schusstest");
	LCDprint_text(cursor,19,"X");
	LCDprint_num(2,9,schussstaerke);
	LCDprint_text(2,7,"-");
	LCDprint_text(2,12,"+");
	LCDprint_text(3,0,"Dribbler");
	
	if(buttons[0])
	{
		if(cursor == 1){
			schuss();
		}
		else{
			if(dribbler_state)
			dribbler_state = false;
			else
			dribbler_state = true;
			
			delay(200);
			
			dribbler(dribbler_state);
		}
	}
	else if (buttons[2])
	{
		schussstaerke--;
		delay(200);
	}
	else if (buttons[1])
	{
		if(cursor == 1)
		cursor = 3;
		else
		cursor = 1;
		delay(200);
	}
	else if (buttons[4])
	{
		schussstaerke++;
		delay(200);
	}
	else if (buttons[3])
	{
		if(cursor == 1)
		cursor = 3;
		else
		cursor = 1;
		delay(200);
	}
	else if (buttons[7])
	{
		aktuelles_menue = MOTORBOARD;
		cursor = 1;
		delay(200);
	}
}

int letzter_cursor = 0;
int letztes_menue = 0;

void displaysteuerung()
{
	letzter_cursor = cursor;
	letztes_menue = aktuelles_menue;
	
	sensorwerte_aktualisieren();
	
	if(aktuelles_menue < 8)
	{
		menues_sensoren();
	}
	else if (aktuelles_menue == START)
	{
		menue_start();
	}
	else if (aktuelles_menue == SENSOREN_A)
	{
		menue_sensoren_a();
	}
	else if (aktuelles_menue == SENSOREN_B)
	{
		menue_sensoren_b();
	}
	else if (aktuelles_menue == POWER)
	{
		menue_power();
	}
	else if (aktuelles_menue == MOTORBOARD)
	{
		menue_motorboard();
	}
	else if (aktuelles_menue == MOTOREN)
	{
		menue_motoren();
	}
	
	if((letztes_menue != aktuelles_menue) || (letzter_cursor != cursor) || buttons[8])
	{
		LCDcls();
	}
}
