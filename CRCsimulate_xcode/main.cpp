//
//  main.cpp
//  CRCsimulate_xcode
//
//  Created by CHE WEI LIN on 13/6/13.
//  Copyright (c) 2013年 John. All rights reserved.
//
#include "CRClib.h"

using namespace std;
typedef long long byte;

int main(int argc, const char * argv[])
{
    srand((unsigned int)time(NULL));
    //byte dataword = 0x9; //binary 1001
	//byte divisor = 0xB;   //binary 1011
	
	//byte dataword = 0x9; //binary 1001
	//byte divisor = 0xB;   //binary 1101
	//byte dataword = 0xA; //binary 1010
    //byte divisor = 0xD;   //binary 1011
    
    //byte divisor = 0x13; //binary 1 0011
    byte divisor = 0x123; //binary 1 0010 0011
	//byte dataword;
    byte arg_dataword;
    byte remainder;
	byte codeword;
    
    
	byte syndrome;
	byte received;
	byte received_dataword;
    int add_bit = 0;
    
	bool status;
    
	byte dataword = getdataword(divisor);
	//隨機取得dataword
    
    //byte dataword = 0x35B;
	//dwdataword 11 0101 1011
    
//    cout<<"NOTE divisor is "<<dec2bin(divisor)<<endl;
//	byte dataword = getinput();
	//get input dataword
    
    add_bit = count_bit(dec2bin(divisor)) - 1;
	//­計算需要加幾個位元
	arg_dataword = enlargedataword(dataword, add_bit);
	//往左位移
	remainder = generator(arg_dataword, divisor);
	//產生remainder
	codeword = getcodeword(dataword, remainder, add_bit);
	//組合codeword
    
    cout<<"dataword:"<<dec2bin(dataword)<<endl;
    cout<<"divisor:"<<dec2bin(divisor)<<endl;
    cout<<"remainder:"<<dec2bin(remainder)<<endl;
    cout<<"After encode get codeword:"<<dec2bin(codeword)<<endl;
	
	
	codeword = channel(codeword, 0.5);
	//通過不穩定通道
    cout<<endl<<"Received codeword:"<<dec2bin(codeword)<<endl;
	
    
	syndrome = checker(codeword, divisor);
	//取得syndrome
	received_dataword = narrowcodeword(codeword, add_bit);
	//往右位移
    
    cout<<"syndrome:"<<dec2bin(syndrome)<<endl;
    
	received = decision(received_dataword, syndrome);
	//決策是否將資料丟棄
    
    status = comparedataword(dataword, received, syndrome);
    //To ckeck the received dataword is right or wrong
	logging(status);
    
	return 0;
}

