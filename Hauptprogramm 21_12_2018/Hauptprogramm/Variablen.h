/*
 * Variablen.h
 *
 * Created: 22.06.2018 17:09:36
 *  Author: Ben Kast
 */ 

#include "Sensoren.h"
#include "Displaysteuerung.h"
#include "Power.h"
#include "Testfunktionen.h"
#include "Linie.h"
#include "Ballverfolgung.h"

//UUU verusche globale Variablen möglichst selten zu verwenden. 

extern Goldboard4 gb;
extern usring us;
extern SRF08 hinten;
extern PCF8574A taster;
extern CMPS11 cmp;
extern PixyI2C pixy_tk;

#ifndef VARIABLEN_H_
#define VARIABLEN_H_

#define VL 0
#define VR 1
#define HL 2
#define HR 3

extern float drall_faktor;

extern bool raus;
extern bool an;
extern bool last_an;

extern int aktuelles_menue;
extern int cursor;
extern unsigned long last_cls;

extern int ultraschall_count;
extern unsigned long last_ultraschall;
#define ULTRASCHALL_ABFRAGE_ZEIT 250

extern unsigned long last_compass;
#define COMPASS_ABFRAGE_ZEIT 50

#define BODEN_A			0
#define BODEN_B			1
#define BODEN_C			2
#define COMPASS			3
#define ULTRASCHALL		4
#define PIXY			5
#define BUTTONS			6
#define LICHTSCHRANKE	7

#define START			10
#define SENSOREN_A		11
#define SENSOREN_B		12
#define POWER			13
#define MOTORBOARD		14
#define MOTOREN			15

extern int lichtschranke_referenz;
extern int bodenlichtsensor[16];
extern bool bodenlichtsensor_d[16];

extern int compass;
extern int compass_alt;
extern int ultraschall_hinten;

extern int pixy_blocks;
extern unsigned long letzte_abfrage; 
extern int ball_x;
extern int ball_x_alt;
extern int ball_y;
extern int ball_y_alt;
extern int tor_x;
extern int tor_y;
extern bool tor;
extern int tore;
extern int baelle;

extern bool ballda;
extern bool ballnah;

extern bool buttons[9]; //UUU array hat nicht die gleiche größe wie in Variablen.cpp!!! verwende define für array größen
extern bool oldbuttons[9]; //von 7 zu 9 ... behoben
extern int lichtschranke;

extern int schussstaerke;

#endif /* VARIABLEN_H_ */
