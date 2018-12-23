#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include "i2c.h"

void write_portexpander(int pin, bool state);
bool read_portexpander(int pin, uint8_t value_to_high);
int read_portexpander();
bool read_portexpander(int pin);

void read_states_portexpander();

void LCDprint_num(int y, int x, int num);
void LCDprint_num(int num);
void LCDprint_text(int y, int x, const char* text);
void LCDprint_text(const char* text);
void LCDputc(char zeich);
void LCDlocate(int pos_x, int pos_y);
void LCDcls();
void LCDhome();
void LCDinit();
void sendCommand_init(uint8_t cmd);
void LCDsetCursor(uint8_t curmode);
void loc8();
void sendData(uint8_t data);
void sendCommand(uint8_t cmd);


#endif

