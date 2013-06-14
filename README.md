# CRC Simulate

Copyright © 2009 Che Wei Lin. All Rights Reserved.

## To build the application

Because this the Xcode project, you need 

* Mac OS X 10.6 Snow Leopard or late version.
* Intel Mac.
* Xcode.

----

# Description 

This is the cyclic redundancy check (CRC) Simulate, if you don't know how it works take a look on Wikipedai Cyclic redundancy check.

CRC Sender need to encode the dataword into codeword.
CRC Receiver need to determine the received codeword if the received codeword been corrupted by noise, then discard it. Otherwise received the dataword.

The CRClib provided some features:

* Sender side:
    Random get dataword function.
    Generate augmented dataword function.
    Generate remainder function.
    Generate codeword function.

* Receiver side:
    Generate syndrome function.
    To decide whether discart received dataword or not.
    Get dataword back from codeword function.

* Unreliable Channel:
    Generate random noise by input error rate parameter.

It also provided input customized dataword by using getinput function.

----

# NOTE:
    The number of bit with augmented dataword only support 19 bits.



