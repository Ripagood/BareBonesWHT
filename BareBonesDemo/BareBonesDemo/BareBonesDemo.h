/*
 * BareBonesDemo.h
 *
 * Created: 9/21/2015 1:04:05 AM
 *  Author: Admin
 */ 



#ifndef BAREBONESDEMO_H_
#define BAREBONESDEMO_H_

#include "BareBonesWHT.h"

int8_t serialMoteReceive(void);
void serialMoteSend(int8_t data );
void initSerialMote(void);

#endif /* BAREBONESDEMO_H_ */
