/*
 * GUI.c
 *
 *  Created on: Apr 29, 2024
 *      Author: harun
 */
#include "GUI.h"
//https://github.com/olikraus/u8g2/wiki/u8g2reference

//---------Global Vars---------
pinState button_inputs[7]={
		{null,0,0,false,false},
		{up,0,0,false,false},
		{down,0,0,false,false},
		{left,0,0,false,false},
		{right,0,0,false,false},
		{select,0,0,false,false},
		{back,0,0,false,false}
};

windows currWindow = menu;
uint8_t Tim3Count=0;
//-----------------------------
/**
  * @brief Handle Input Function
  * @param bool retTap (to determin if the function returns the tapped value or pressed value)
  * @retval pinState struct
  */
pinState handleInput(t_p Tap_Press){
	button_inputs[up].last = button_inputs[up].current;
	button_inputs[up].current = HAL_GPIO_ReadPin(Up_BTN_GPIO_Port,Up_BTN_Pin);
	button_inputs[up].isTapped = button_inputs[up].current && !button_inputs[up].last;
	button_inputs[up].isPressed = button_inputs[up].current && button_inputs[up].last;

	button_inputs[down].last = button_inputs[down].current;
	button_inputs[down].current = HAL_GPIO_ReadPin(Down_BTN_GPIO_Port,Down_BTN_Pin);
	button_inputs[down].isTapped = button_inputs[down].current && !button_inputs[down].last;
	button_inputs[down].isPressed = button_inputs[down].current && button_inputs[down].last;

	button_inputs[left].last = button_inputs[left].current;
	button_inputs[left].current = HAL_GPIO_ReadPin(Left_BTN_GPIO_Port,Left_BTN_Pin);
	button_inputs[left].isTapped = button_inputs[left].current && !button_inputs[left].last;
	button_inputs[left].isPressed = button_inputs[left].current && button_inputs[left].last;

	button_inputs[right].last = button_inputs[right].current;
	button_inputs[right].current = HAL_GPIO_ReadPin(Right_BTN_GPIO_Port,Right_BTN_Pin);
	button_inputs[right].isTapped = button_inputs[right].current && !button_inputs[right].last;
	button_inputs[right].isPressed = button_inputs[right].current && button_inputs[right].last;

	button_inputs[select].last = button_inputs[select].current;
	button_inputs[select].current = HAL_GPIO_ReadPin(Select_BTN_GPIO_Port,Select_BTN_Pin);
	button_inputs[select].isTapped = button_inputs[select].current && !button_inputs[select].last;
	button_inputs[select].isPressed = button_inputs[select].current && button_inputs[select].last;

	button_inputs[back].last = button_inputs[back].current;
	button_inputs[back].current = HAL_GPIO_ReadPin(Back_BTN_GPIO_Port,Back_BTN_Pin);
	button_inputs[back].isTapped = button_inputs[back].current && !button_inputs[back].last;
	button_inputs[back].isPressed = button_inputs[back].current && button_inputs[back].last;
	if(Tap_Press==Tap){
		if(button_inputs[up].isTapped){
			return button_inputs[up];//UP
		}
		else if(button_inputs[down].isTapped){
			return button_inputs[down];//DOWN
		}
		else if(button_inputs[left].isTapped){
			return button_inputs[left];//LEFT
		}
		else if(button_inputs[right].isTapped){
			return button_inputs[right];//RIGHT
		}
		else if(button_inputs[select].isTapped){
			return button_inputs[select];//SELECT
		}
		else if(button_inputs[back].isTapped){
			return button_inputs[back];//BACK
		}
		else{
			return button_inputs[null];
		}
	}
	else{
		if(button_inputs[up].isPressed){
			return button_inputs[up];//UP
		}
		else if(button_inputs[down].isPressed){
			return button_inputs[down];//DOWN
		}
		else if(button_inputs[left].isPressed){
			return button_inputs[left];//LEFT
		}
		else if(button_inputs[right].isPressed){
			return button_inputs[right];//RIGHT
		}
		else if(button_inputs[select].isPressed){
			return button_inputs[select];//SELECT
		}
		else if(button_inputs[back].isPressed){
			return button_inputs[back];//BACK
		}
		else{
			return button_inputs[null];
		}
	}
	//TODO Later: USE TIMER, if still isPressed after timer expires, then move
}



/**
  * @brief Handle Window Function
  * @param0 u8g2_t* u8g2 (u8g2 struct instance)
  *
  * @retval None
  */
void handle_Windows(u8g2_t* u8g2){
	switch(currWindow){
	case menu:
		window_Menu(u8g2);
		break;
	case game:
		window_Game(u8g2);
		break;
	case idle:
		window_Idle(u8g2);
		break;
	case nfc:
		window_NFC(u8g2);
		break;
	case rfid:
		window_RFID(u8g2);
		break;
	case settings:
		window_Settings(u8g2);
		break;
	case subghz:
		window_Subghz(u8g2);
		break;
	}
}



/**
  * @brief Menu Window Function
  * @param0 u8g2_t u8g2 (u8g2 struct instance)
  *
  * @retval None
  */
int8_t item_sel=0;
int8_t item_prev=5;
int8_t item_next=1;
void window_Menu(u8g2_t* u8g2){

	button input = handleInput(Tap).direction;
	switch(input){
	case up:
		//isTapped, else isPushed
		item_sel--;
		break;
	case down:
		item_sel++;
		break;
	case select:
		//Enter new window
		currWindow=item_sel;
		break;
	case back:
		break;
	case left:
		break;
	case right:
		break;
	case null:
		break;
	}

	item_prev=item_sel-1;
	item_next=item_sel+1;

	if(item_sel<0){
		item_sel=icon_len-1;
	}
	else if(item_sel>=icon_len){
		item_sel=0;
	}

	if(item_prev<0){
		item_prev=5;
	}
	if(item_next>=icon_len){
		item_next=0;
	}

	u8g2_ClearBuffer(u8g2);
	u8g2_SetDrawColor(u8g2,1);
	u8g2_SetBitmapMode(u8g2,1);
	u8g2_SetFont(u8g2,u8g_font_7x14);
	u8g2_DrawXBMP(u8g2, icn_x, top_icn_y, icon_wh, icon_wh,  menu_item[item_prev].icon);
	u8g2_DrawStr(u8g2, title_x, top_title_y, menu_item[item_prev].icon_name);

	u8g2_DrawXBMP(u8g2, icn_x, mid_icn_y, icon_wh, icon_wh,  menu_item[item_sel].icon);
	u8g2_DrawStr(u8g2, title_x, mid_title_y, menu_item[item_sel].icon_name);

	u8g2_DrawXBMP(u8g2, icn_x, bot_icn_y, icon_wh, icon_wh,  menu_item[item_next].icon);
	u8g2_DrawStr(u8g2, title_x, bot_title_y, menu_item[item_next].icon_name);

	u8g2_DrawXBMP(u8g2, -2, 22, Select_width,  Select_height, Select_bits);
	u8g2_DrawXBMP(u8g2, 126-ScrollBar_width, 0, ScrollBar_width,  ScrollBar_height, ScrollBar_bits);
	u8g2_DrawBox(u8g2,127-4, (64/icon_len)*item_sel, 3, (64/icon_len) + ((64%icon_len) * ((item_sel/(icon_len-1)))));

	u8g2_SendBuffer(u8g2);

}

playerInfo Player={2,2};//TODO if wanting to reset progress(init when selected from menu)
void window_Game(u8g2_t* u8g2){
	button input = handleInput(Press).direction;
	switch(input){
	case up:
		if(Player.y_pos>0){
			Player.y_pos--;
		}
		break;
	case down:
		if(Player.y_pos<63){
				Player.y_pos++;
			}
		break;
	case select:
		break;
	case back:
		currWindow=menu;
		break;
	case left:
		if(Player.x_pos>0){
				Player.x_pos--;
			}
		break;
	case right:
		if(Player.x_pos<127){
				Player.x_pos++;
			}
		break;
	case null:
		break;
	}
	u8g2_ClearBuffer(u8g2);
	u8g2_SetDrawColor(u8g2,1);
	u8g2_SetFont(u8g2,u8g_font_7x14);
	u8g2_DrawStr(u8g2, 15, 30, "404 Not Found");

	u8g2_DrawPixel(u8g2,Player.x_pos,Player.y_pos);



	u8g2_SendBuffer(u8g2);

}

void window_Idle(u8g2_t* u8g2){
	button input = handleInput(Tap).direction;
	switch(input){
	case up:
		currWindow=menu;
		break;
	case down:
		currWindow=menu;
		break;
	case select:
		currWindow=menu;
		break;
	case back:
		currWindow=menu;
		break;
	case left:
		currWindow=menu;
		break;
	case right:
		currWindow=menu;
		break;
	case null:
		/*-------------------------*/
		break;
	}
	u8g2_ClearBuffer(u8g2);
	u8g2_SetDrawColor(u8g2,1);
	switch(z_iter){
	case 0:
		u8g2_DrawXBMP(u8g2, 20, 20, panda0_width, panda0_height,  panda0_bits);
		u8g2_SetFont(u8g2,u8g_font_5x8);
		u8g2_DrawStr(u8g2, 30, 35, "z");
		break;
	case 1:
		u8g2_DrawXBMP(u8g2, 20, 21, panda1_width, panda1_height,  panda1_bits);
		u8g2_SetFont(u8g2,u8g_font_7x14);
		u8g2_DrawStr(u8g2, 23, 27, "z");
		break;
	case 2:
		u8g2_DrawXBMP(u8g2, 20, 21, panda1_width, panda1_height,  panda1_bits);
		u8g2_SetFont(u8g2,u8g_font_7x14);
		u8g2_DrawStr(u8g2, 13, 15, "Z");
		break;
	case 3:
		u8g2_DrawXBMP(u8g2, 20, 20, panda0_width, panda0_height,  panda0_bits);
		u8g2_SetFont(u8g2,u8g_font_7x14);
		u8g2_DrawStr(u8g2, 13, 15, "Z");
	}
	u8g2_SendBuffer(u8g2);
	//Animation Delay is Handled in Tim3 PeriodElapsedCallback IRQ in main.c [User Code 4]
}

void window_NFC(u8g2_t* u8g2){
	button input = handleInput(Tap).direction;
	switch(input){
	case up:
		break;
	case down:
		break;
	case select:
		break;
	case back:
		currWindow=menu;
		break;
	case left:
		break;
	case right:
		break;
	case null:
		break;
	}
	u8g2_ClearBuffer(u8g2);
	u8g2_SetDrawColor(u8g2,1);
	u8g2_SetFont(u8g2,u8g_font_7x14);
	u8g2_DrawStr(u8g2, 15, 30, "404 Not Found");
	u8g2_SendBuffer(u8g2);

}

void window_RFID(u8g2_t* u8g2){
	button input = handleInput(Tap).direction;
	switch(input){
	case up:
		break;
	case down:
		break;
	case select:
		break;
	case back:
		currWindow=menu;
		break;
	case left:
		break;
	case right:
		break;
	case null:
		break;
	}
	u8g2_ClearBuffer(u8g2);
	u8g2_SetDrawColor(u8g2,1);
	u8g2_SetFont(u8g2,u8g_font_7x14);
	u8g2_DrawStr(u8g2, 15, 30, "404 Not Found");
	u8g2_SendBuffer(u8g2);

}

void window_Settings(u8g2_t* u8g2){
	button input = handleInput(Tap).direction;
	switch(input){
	case up:
		break;
	case down:
		break;
	case select:
		break;
	case back:
		currWindow=menu;
		break;
	case left:
		break;
	case right:
		break;
	case null:
		break;
	}
	u8g2_ClearBuffer(u8g2);
	u8g2_SetDrawColor(u8g2,1);
	u8g2_SetFont(u8g2,u8g_font_7x14);
	u8g2_DrawStr(u8g2, 15, 30, "404 Not Found");
	u8g2_SendBuffer(u8g2);

}

void window_Subghz(u8g2_t* u8g2){
	button input = handleInput(Tap).direction;
	switch(input){
	case up:
		break;
	case down:
		break;
	case select:
		break;
	case back:
		currWindow=menu;
		break;
	case left:
		break;
	case right:
		break;
	case null:
		break;
	}
	u8g2_ClearBuffer(u8g2);
	u8g2_SetDrawColor(u8g2,1);
	u8g2_SetFont(u8g2,u8g_font_7x14);
	u8g2_DrawStr(u8g2, 15, 30, "404 Not Found");
	u8g2_SendBuffer(u8g2);

}


