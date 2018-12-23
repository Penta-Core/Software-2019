/*
 * Ballverfolgung.cpp
 *
 * Created: 30.10.2018 11:12:21
 * Author: Ben Kast
 */ 

#include "Goldboard4.h"
#include "Variablen.h"

void ballfahren_torwart()
{
	if (ballnah)
	{
		int x = ball_x;
		int y = ball_y;
		int c = x/3;//atan((y)/(abs(x)*x));
		int pace = 255;
		fahren(c,pace);
	}
	else if (ballda)
	{
		fahren(0,255);
		schuss();
	}
	else
		fahren(0,0,0);
	/*else
	{
		if (ultraschall_hinten > 25)
		{
			fahren(180,200);
		}
		else
		{
			fahren(0,0);
		}
	}*/
}

/*					y
					240
					140
x					40
-160				0				160
				Roboter
				
				a = atan(y/x);*/