/*
 * BareBones library Demo
 *
 * Created: 1/28/2015 8:32:50 PM
 *  Author: Elias Ventura
 * This is the atmega328p version
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
#include <string.h>
#include <stdlib.h>
#include "BareBonesDemo.h"

#define F_CPU 7372800UL
#define BAUDRATEPC 115200                           // define baud for PC
#define BAUDRATE ((F_CPU)/(BAUDRATEPC*16UL)-1)            // set baud rate value for UBRR

#define BAUDRATEMOTE 115200                           // define baud for WH mote
#define UBRRMOTE ((F_CPU)/(BAUDRATEMOTE*16UL)-1)            // set baud rate value for UBRR

#define PAQUETES 100   // Number of packets to send for the test

MoteData_t moteData;  //structure for keeping mote data 

ISR(USART_RX_vect){
	
	InterruptReception(&moteData);
			
}


int main(void)
{
	
	//set the function pointers for send and receive
	moteData.serialMoteSend=serialMoteSend;
	moteData.serialMoteReceive=serialMoteReceive;


	DDRC = (1<<PORTC0)|(1<<PORTC1); // select pc0 and pc1 as outputs
	//pc0 drives the reset on the whmt, pc1 is the led indication
	
	PORTC = (1<<PORTC2);//Pull up on the button, reset the mote


	initSerialMote(); //Initialize the serial connection for the mote
	
	
	_delay_ms(300);
	sei();
	PORTC |= (1<<PORTC0);// turn on the mote
	
	MoteInitialization(&moteData);

	MoteSvcInitialization(&moteData);
	
	uint8_t datos[]={0xB1,0x6B,0x00,0xB5};
	uint8_t datos2[]={'D','I','N','E','R','O'};
		
	//bit_fld & (1<<n)
	
	PORTC |= (1<<PORTC1); //turn on LED, the Mote is ready to send
	
	
	while (PINC & (1<<PINC2)); // wait for button press
	PORTC &= ~(1<<PORTC1);// turn off the LED
	
	uint16_t packets = 0;
    while(packets<=PAQUETES)
    {
		_delay_ms(500);
		//begin transmission 
		//send data every 500ms, serviceID is defined in BareBonesWHT.h
		sendData(datos2,sizeof(datos2),serviceID,&moteData);
		packets++;
		
    }
	
	
	PORTC |= (1<<PORTC1);// turn on LED again, tx finished
	while(1);
}



void initSerialMote(void){
	UBRR0 = UBRRMOTE;
	//UCSR0A = (1<<U2X0);
	UCSR0B = (1<<TXEN0)|(1<<RXEN0)|(1<<RXCIE0);                // enable receiver and transmitter
	UCSR0C = (1<<UCSZ00)|(1<<UCSZ01);   // 8bit data format
	//Enable interrupts for RX
}

void serialMoteSend(int8_t data )
{
	/*
	Wait for empty transmit buffer
	*/
	while( !( UCSR0A & (1<<UDRE0)) );
	/*
	Put data into buffer, sends the data
	*/
	UDR0 = data;
}


int8_t serialMoteReceive(void)
{	//Only read UDR0
	return UDR0;
}






