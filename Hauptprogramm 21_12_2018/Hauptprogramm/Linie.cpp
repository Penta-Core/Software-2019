/*)
 * Linie.cpp
 *
 * Created: 04.08.2018 11:12:16
 *  Author: Ben Kast
 */

#include "Goldboard4.h"
#include "Variablen.h"

int richtung = -1;


void linie_wegfahren()
{
	double x = 0;
	double y = 0;
	
	if (bodenlichtsensor_d[12])
	{
		x+=100*sin(0*PI/180);
		y+=100*cos(0*PI/180);
	}
	
	if (bodenlichtsensor_d[4])
	{
		x+=100*sin(180*PI/180);
		y+=100*cos(180*PI/180);
	}
	
	if (bodenlichtsensor_d[0])
	{
		x+=100*sin(90*PI/180);
		y+=100*cos(90*PI/180);
	}
	
	if (bodenlichtsensor_d[8])
	{
		x+=100*sin(270*PI/180);
		y+=100*cos(270*PI/180);
	}
	
	int richtung = (int)(atan2(y,x)*180/PI);
	richtung-=90;
	
	//SERIAL_PRINTLN(richtung);
	//delay(200);
	//fahren(richtung-180,255,0);
	//delay(1000);
}






