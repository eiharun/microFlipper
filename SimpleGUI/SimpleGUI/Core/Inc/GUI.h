/*
 * GUI.h
 *
 *  Created on: Apr 29, 2024
 *      Author: harun
 */
#include <stdint.h>
#include <stdbool.h>
#include "main.h"
#include "u8g2stm32/u8g2.h"
#include "Bitmaps.h"

#ifndef SRC_GUI_H_
#define SRC_GUI_H_

enum _btn{
	null=0,up,down,left,right,select,back
};typedef enum _btn button;

enum _windows{
	menu=-1,idle=0,subghz=1,rfid=2,nfc=3,game=4,settings=5
};typedef enum _windows windows;

struct _pinState{
	button direction;
	GPIO_PinState current;
	GPIO_PinState last;
	bool isTapped;
	bool isPressed;
};typedef struct _pinState pinState;

pinState handleInput();

extern uint8_t Tim3Count;

void handle_Windows(u8g2_t* u8g2);
//WINDOWS ...//
void window_Menu(u8g2_t* u8g2);
void window_Game(u8g2_t* u8g2);
void window_Idle(u8g2_t* u8g2);
void window_NFC(u8g2_t* u8g2);
void window_RFID(u8g2_t* u8g2);
void window_Settings(u8g2_t* u8g2);
void window_Subghz(u8g2_t* u8g2);

#endif /* SRC_GUI_H_ */
