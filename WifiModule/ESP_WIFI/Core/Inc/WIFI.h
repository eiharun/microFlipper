/*
 * WIFI.h
 *
 *  Created on: May 20, 2024
 *      Author: harun
 */

#ifndef INC_WIFI_H_
#define INC_WIFI_H_

#include "stm32f7xx_hal.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h> //Temporary...
#include <stdlib.h>

#define RXSIZE 256
#define DATASIZE 4096
extern uint8_t UART4_RX[RXSIZE];//Buffer written by DMA
extern uint8_t Data_Buffer[DATASIZE];//Actual storage
extern uint16_t data_head,data_tail;
extern bool rxCplt;
extern bool txCplt;
extern bool rxErr;
extern char* recv;
extern uint8_t waitTMout;
enum _atstatus {AT_OK, AT_ERR, AT_PEND, AT_TMOUT, AT_MISCONFIG}; typedef enum _atstatus ATStatus;
enum _cwmode {Null,STATION,AP,AP_STATION}; typedef enum _cwmode WifiMode;
enum _cipmux {SINGLE,MULTIPLE}; typedef enum _cipmux MuxMode;
enum _cipserver {DELETE,CREATE}; typedef enum _cipserver ServerMode;
enum _sendmode {NORMAL,PASSTHROUGH}; typedef enum _sendmode SendMode;


void handleWifi(UART_HandleTypeDef huart4);


//BASIC AT COMMANDS
ATStatus AT_test(UART_HandleTypeDef* huart4);
ATStatus AT_restart(UART_HandleTypeDef* huart4);
ATStatus AT_version(UART_HandleTypeDef* huart4, char* output);

//WIFI AT COMMANDS
ATStatus AT_queryWIFImode(UART_HandleTypeDef* huart4, WifiMode* mode);//returns the mode through its parameter
ATStatus AT_setWIFImode(UART_HandleTypeDef* huart4, WifiMode mode);

//TCP-IP AT COMMANDS
ATStatus AT_queryMUX(UART_HandleTypeDef* huart4, MuxMode* mode);
ATStatus AT_setMUX(UART_HandleTypeDef* huart4, MuxMode mode);

ATStatus AT_queryServer(UART_HandleTypeDef* huart4, ServerMode* mode, uint16_t* port);
ATStatus AT_setServer(UART_HandleTypeDef* huart4, ServerMode mode, uint16_t port);//CIPMUX must be set to 1

ATStatus AT_getIP(UART_HandleTypeDef* huart4, char* output);

ATStatus AT_Send(UART_HandleTypeDef* huart4, char* data, size_t size, uint8_t linkID, SendMode mode, MuxMode cipmux);

ATStatus AT_Close(UART_HandleTypeDef* huart4, uint8_t linkID, MuxMode cipmux);

#endif /* INC_WIFI_H_ */




/*TEMPLATE
if(txCplt==false){
	HAL_UART_Transmit_IT(huart4, (uint8_t*)"AT\r\n", 4);
}
while(!rxCplt){
	//wait until rx is CPLT
	HAL_GPIO_WritePin(LED_RED_GPIO_Port,LED_RED_Pin,SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(LED_RED_GPIO_Port,LED_RED_Pin,RESET);
	//Have a timeout(there is something wrong if this while loop runs more than 10 times)
	if(waitTMout>10){
		return AT_TMOUT;
	}
	waitTMout++;
}
waitTMout=0;
if(rxCplt && txCplt){
	rxCplt=false;
	txCplt=false;
	memset(recv,'\0',strlen(recv));
	//COPY ONLY RELEVANT section of Data buffer into recv
	if(data_head>data_tail){//handle wrap around condition
		uint16_t size_leftover = DATASIZE-data_head;
		memcpy((uint8_t*)recv, (uint8_t*)Data_Buffer+data_head, size_leftover);
		memcpy((uint8_t*)recv+size_leftover, (uint8_t*)Data_Buffer, data_tail);
	}
	else{
		memcpy((uint8_t*)recv, (uint8_t*)Data_Buffer+data_head, data_tail-data_head);
	}

	if(strstr(recv, "\r\nOK\r\n")!=NULL){
		//DO SOMETHING

		memset(recv,'\0',strlen(recv));
		return AT_OK;
	}
	else if(strstr(recv,"\r\nERROR\r\n")!=NULL){
		return AT_ERR;
	}
}
else{
	return AT_PEND;
}
if(rxErr){
	return AT_ERR;
}
return AT_ERR;
 * */
