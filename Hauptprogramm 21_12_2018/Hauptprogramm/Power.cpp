/*
 * Power.cpp
 *
 * Created: 22.06.2018 17:32:39
 *  Author: Ben Kast
 */

#include "Goldboard4.h"
#include "Variablen.h"
#include "Display.h"

void motor_anzeigen()
{
	LCDprint_num(0,0,255);
	LCDprint_num(1,0,200);
	LCDprint_num(2,0,150);
	LCDprint_num(3,0,100);
	
	LCDprint_num(0,4,(-255*sin((M_PI*0/180)-0.75*M_PI)));
	LCDprint_num(1,4,(-200*sin((M_PI*0/180)-0.75*M_PI)));
	LCDprint_num(2,4,(-150*sin((M_PI*0/180)-0.75*M_PI)));
	LCDprint_num(3,4,(-100*sin((M_PI*0/180)-0.75*M_PI)));
}

int* fahren (int grad, int speed, int drall) //4 rad
{
	float bogen = M_PI * grad / 180;
	int motor0 = (-speed*sin(bogen - 0.75*M_PI))/0.7; // /0.7 weil siehe void fahren anzeigen
	int motor1 = (-speed*sin(bogen - 0.25*M_PI))/0.7;
	
	static int m[4]; 
	
	m[VL] = -motor0+drall;
	m[VR] = motor1+drall;
	m[HL] = -motor1+drall;
	m[HR] = motor0+drall;
	
	int highest_m = 0;
	
	for (int i = 0; i < 4; i++)
	{
		if (abs(m[i]) > highest_m)
		{
			highest_m = abs(m[i]);
		}
	}

	float change = (float)speed/highest_m;
	
	for (int i = 0; i < 4; i++)
	{
		m[i]*=change;
	}
	
	/*for (int i = 0; i < 4; i++)
	{
		if(m[i] > 255)
			m[i] = 255;
		else if (m[i] < -255)
			m[i] = -255;
	}*/
	
	gb.motor[VL].rotate(m[VL]);
	gb.motor[VR].rotate(m[VR]);
	gb.motor[HL].rotate(m[HL]);
	gb.motor[HR].rotate(m[HR]);
	
	return m;
}

int fahren(int grad, int speed)
{
	drall_faktor = 0.7;
	
	bool d = 1.20;
	
	if(tor)
	{
		d = 1.50;
	}
	
	if(tor)
		drall_faktor = 0.3;
	
	float speed_faktor = 1+(speed/1000);
	
	int drall = (compass-128)*drall_faktor+d*(compass-compass_alt);
	
	if(tor)
		drall+=(tor_x*0.7);
	
	drall = drall*-1;
	
	drall *= speed_faktor;
	
	drall = drall / 3;
	
	fahren(grad, speed, drall);
	
	return 0;//behoben
//UUU return fehlt!!!
}

void drehen(int speed)
{
	for (int i = 0; i < 4; i++)
	{
		gb.motor[i].rotate(speed);
	}
}

void schuss()
{
	gb.setPower(1,1);
	delay(schussstaerke);
	gb.setPower(1,0);
}

void dribbler(bool state)
{
	gb.setPower(0,state);
}
