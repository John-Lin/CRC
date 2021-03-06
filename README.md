# CRC Simulate

This Program is my study on the course named Communications Network.

## Description 

This is the cyclic redundancy check (CRC) Simulate, if you don't know how it works take a look on Wikipedai Cyclic redundancy check. :)

CRC Sender need to encode the dataword into codeword.
CRC Receiver need to determine the received codeword if the received codeword been corrupted by noise, then discard it. Otherwise received the dataword.

The CRClib provided some features:

* Sender side:
    * Get random dataword function.
    * Generate augmented dataword function.
    * Generate remainder function.
    * Generate codeword function.

* Receiver side:
    * Generate syndrome function.
    * To decide whether discart received dataword or not.
    * Get dataword back from codeword function.

* Unreliable Channel:
    * Generate random noise by input error rate parameter.

* logging:
    * logging CRC detect success or failure.

It also provided input customized dataword by using getinput function.

## CRC detection simulate Example in main program

    #include "CRClib.h"

    using namespace std;
    typedef unsigned long long byte;

    int main(int argc, const char * argv[])
    {
        int add_bit;
        bool status;
        
        byte divisor = 0x123;
        
        byte dataword;
        byte arg_dataword;
        byte remainder;
        byte codeword;

        byte syndrome;
        byte received;
        byte received_dataword;

        //random number with time seed
        srand((unsigned int)time(NULL));
        
        //For Sender side
        dataword = getdataword(divisor);
        add_bit = count_bit(dec2bin(divisor)) - 1;
        arg_dataword = enlargedataword(dataword, add_bit);
        remainder = generator(arg_dataword, divisor);
        codeword = getcodeword(dataword, remainder, add_bit);

        //Throught to the Unreliable Channel with 0.5 error rate
        codeword = channel(codeword, 0.5);

        //For Receiver side
        syndrome = checker(codeword, divisor);
        received_dataword = narrowcodeword(codeword, add_bit);
        received = decision(received_dataword, syndrome);

        //Recognize CRC detection success or failure and log it
        status = comparedataword(dataword, received, syndrome);
        logging(status);

        return 0;
    }

## How To build the application

Because this project is the Xcode project, you need...

* Mac OS X 10.6 Snow Leopard or late version.
* Intel Mac.
* Xcode.

Just click build button.

## NOTE

The number of bit with augmented dataword only support 20 bits.

## Contact

email: ireri339@gmail.com

## Copyright ©

The MIT License (MIT)

Copyright (c) 2013 LIN CHE WEI

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.


