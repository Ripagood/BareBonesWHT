/***
BareBones WHT V1.0
Created 18/09/2015 00:00 AM
Author: Elias Ventura Hernandez E.
****/

#ifndef BAREBONESWHT_H_
#define BAREBONESWHT_H_

#include "hdlc/hdlc.h"
#include <stdint.h>

#define serviceID 0x02  //Service ID for the Mote, select a different one for each mote and micro, starting at 1
#define BUFFER_LENGHT 128




typedef struct MoteData{

	void (*serialMoteSend)(int8_t data);
	int8_t (*serialMoteReceive)(void);


	volatile uint8_t RXindex;
	volatile uint8_t RXbuffer[BUFFER_LENGHT];

	volatile INT32S decodeResult;
	volatile uint8_t validFrame;


	volatile uint8_t hdlcOutput[BUFFER_LENGHT];
	volatile uint8_t hdlcDecoded[BUFFER_LENGHT];

	int8_t sizeToSend;
} MoteData_t, *MoteData_p;


MoteData_p newMoteData(void);
void InterruptReception( MoteData_p moteData);
void MoteInitialization( MoteData_p moteData);
void MoteSvcInitialization( MoteData_p moteData);
void serialMoteSendArray(uint8_t* datos, uint8_t tam, MoteData_p moteData);
uint8_t sendData(uint8_t* data, uint8_t tam, uint8_t svcId, MoteData_p moteData);
uint8_t compareBuffer(uint8_t* datos, uint8_t*datos2,uint8_t tam);






#endif
	


