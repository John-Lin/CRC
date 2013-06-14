//
//  CRClib.h
//  CRCsimulate_xcode
//
//  Created by CHE WEI LIN on 13/6/13.
//  Copyright (c) 2013年 John. All rights reserved.
//

#ifndef __CRCsimulate_xcode__CRClib__
#define __CRCsimulate_xcode__CRClib__

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <math.h>

typedef long long byte;

//Decimal to Binary
byte dec2bin(byte);
//Binary to Decimal
byte bin2dec(byte);

//count the number of bit (only can detect 19 bits)
int count_bit(byte);

//Sender
byte getdataword(byte); //Random get dataword
byte enlargedataword(byte,  int);
byte generator(byte, byte); //To generate remainder
byte getcodeword(byte, byte, int);

//Receiver
byte narrowcodeword(byte,  int);
byte checker(byte, byte); //To generate syndrome
byte decision(byte, byte);

//channel
byte channel(byte, double);

//Statistics and logging
bool comparedataword(byte, byte, byte);
void logging(bool);

//Input handler function
byte getinput();

#endif /* defined(__CRCsimulate_xcode__CRClib__) */
