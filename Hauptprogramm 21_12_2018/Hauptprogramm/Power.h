/*
 * Power.h
 *
 * Created: 22.06.2018 17:32:17
 *  Author: Ben Kast
 */ 


#ifndef POWER_H_
#define POWER_H_

#define VL 0
#define VR 1
#define HL 2
#define HR 3

void motor_anzeigen();
int* fahren(int grad, int speed, int drall);
int fahren(int grad, int speed);
void drehen(int speed);
void schuss();
void dribbler(bool state);

#endif /* POWER_H_ */