# BareBonesWHT
C library for the SmartMesh WirelessHart Mote

This is a basic C library for using the **SmartMesh WirelessHart Mote by Linear Technology**.
The main library is contained in the **BareBones** folder with BareBonesWHT.c , BareBonesWHT.h and uses the fcs.c,fcs.h, 
hdlc.c and hdlc.h sources provided by LT.

The library is made for easy porting in mind. To do it, just use the needed structure definition and
give function callbacks for reading a byte, sending a byte and place the InterruptReception(&moteData);
function inside your ISR for USART reception. Just remember to configure the same network id for the 
motes and the manager, configure the most precise **115200 baudrate** in your uc and use the python programs
given by LT to check the received data on a PC.

A simple Demo for the **Atmega328p** is given [here](https://github.com/Ripagood/BareBonesWHT/blob/master/BareBonesDemo/BareBonesDemo/BareBonesDemo.c) inside the **BareBonesDemo** folder to use ,flash the microcontroller with 
the given .hex and configure the fuses for using an external 7.3728 Mhz crystal on the needed pins. Check the
datasheet for additional information. 

The microcontroller uses the following connections:

* 7.3728 Mhz crystal between PB6,PB7
* LED in PC1
* Switch button to GND on PC2

The connections between the microcontroller and the mote are the following:



ATmega328p   | Mote
------------ | -------------
GND | GND
VCC | VBAT
TXD(PD1) | RX
RXD(PD0) | TX
GND | TX CTSn
VCC | RX RTSn




As such the 328p is energized by the onboard battery on the motes and will run at
3.3V


This simple Demo will:

1. Establish connection to the mote
2. Turn on the LED when the mote is ready to send
3. To begin transmission press the button switch, the LED will then turn off.
4. The uc will begin using the mote to send data at a 500ms rate
5. When the uc is done sending a defined number of packets the LED will turn on again.
6. At this point the demo finishes.



This library was made for use in determining the send data rate for 5 motes in 
different situations. 

This Demo was built using Atmel Studio 6.2 and the latest toolchain.

For any doubts feel free to email me at ripagood@gmail.com






