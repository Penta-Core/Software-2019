/*
 * Variablen.cpp
 *
 * Created: 22.06.2018 17:08:34
 *  Author: Ben Kast
 */

#include "Goldboard4.h"

extern Goldboard4 gb;
extern usring us;
extern SonarSRF08 hinten;
extern PCF8574A taster;
extern CMPS11 cmp;

#define VL 0
#define VR 1
#define HL 2
#define HR 3

float drall_faktor = 1.0;

bool raus = false;
bool an = false;
bool last_an = false;
int aktuelles_menue = 10;
int cursor = 0;
unsigned long last_cls;

int ultraschall_count = 0;
unsigned long last_ultraschall = 0;
#define ULTRASCHALL_ABFRAGE_ZEIT 250

unsigned long last_compass = 0;
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

int lichtschranke_referenz = 0;

int bodenlichtsensor[16];
bool bodenlichtsensor_d[16];

int compass;
int compass_alt;
int ultraschall_hinten;

int pixy_blocks;
unsigned long letzte_abfrage;
int ball_x;
int ball_x_alt;
int ball_y;
int ball_y_alt;
int tor_x;
int tor_y;
bool tor;
int tore;
int baelle;

bool ballda = false;
bool ballnah = false;

bool buttons[9];
bool oldbuttons[9];

int lichtschranke;

int schussstaerke = 20;