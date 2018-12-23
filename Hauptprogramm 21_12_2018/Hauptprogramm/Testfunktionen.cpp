/*
 * Testfunktionen.cpp
 *
 * Created: 13.07.2018 17:40:30
 *  Author: Ben Kast
 */ 

#include "Goldboard4.h"
#include "Variablen.h"

void motor_funktion_test()
{
	int richtung_vorne = 0;
	int richtung_halblinks = 45;
	int compass_vorne = 128;
	int compasss_hinten = 0;
	int pace = 200;
	
	//#define mVL_vorne noch zu beschreiben
	//#define mVR_vorne noch zu beschreiben
	//#define mHL_vorne noch zu beschreiben
	//#define mHR_vorne noch zu beschreiben

	//#define mVL_halblinks_hinten noch zu beschreiben
	//#define mVR_halblinks_hinten noch zu beschreiben
	//#define mHL_halblinks_hinten noch zu beschreiben
	//#define mHR_halblinks_hinten noch zu beschreiben
	
	int* m_vorne = fahren(richtung_vorne, pace, compass_vorne);
	int* m_halblinks_hinten = fahren(richtung_halblinks, pace, compasss_hinten);
	
	fahren(0,0);
	delay(10);
	
	bool passed_vorne = false;
	bool passed_halblinks_hinten = false;
	
	//auf passed testen!!!
	
	SERIAL_PRINTLN("Testfall1:");
	SERIAL_PRINTLN(m_vorne[VL]);
	SERIAL_PRINTLN(m_vorne[VR]);
	SERIAL_PRINTLN(m_vorne[HL]);
	SERIAL_PRINTLN(m_vorne[HR]);
	if(passed_vorne)
		SERIAL_PRINTLN("YEAH_TEST_PASSED");
	else
		SERIAL_PRINTLN("NOOO_TEST_FAILED");
	
	SERIAL_PRINTLN("Testfall2:");
	SERIAL_PRINTLN(m_halblinks_hinten[VL]);
	SERIAL_PRINTLN(m_halblinks_hinten[VR]);
	SERIAL_PRINTLN(m_halblinks_hinten[HL]);
	SERIAL_PRINTLN(m_halblinks_hinten[HR]);
	if(passed_halblinks_hinten)
		SERIAL_PRINTLN("YEAH_TEST_PASSED");
	else
		SERIAL_PRINTLN("NOOO_TEST_FAILED");
		
	delay(1000);	
}

void pixy_funktion_test()
{
	
}

void boden_funktion_test()
{
	
}

void gesamt_test()
{
	
}