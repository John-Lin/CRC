//
//  CRClib.cpp
//  CRCsimulate_xcode
//
//  Created by CHE WEI LIN on 13/6/13.
//  Copyright (c) 2013年 John. All rights reserved.
//

#include "CRClib.h"

using namespace std;

byte dec2bin(byte n)
{
    byte total = 0;
    byte m = 1;
    //cout<<"n"<<n<<endl;
    while(n!=0){
        total = total + (n%2) * m;
        n = n / 2;
        m = m * 10;
    }
    return total;
}

byte bin2dec(byte n)
{
    byte total = 0;
    byte m = 1;
    
	while(n!=0){
		total = total + (n%10) * m;
		n = n/10;
		m = m*2;
	}
	return total;
}

int count_bit(byte binary)
{
    int bit = 0;
	byte th1 = 11111111111; //11 bits
	byte th0 = 10000000000; //11 bits
    
	if(binary <= 11 && binary >=10){
        bit = 2;
    }
    else if(binary <= 111 && binary >=100){
        bit = 3;
    }
    else if(binary <= 1111 && binary >=1000){
        bit = 4;
    }
    else if(binary <= 11111 && binary >=10000){
        bit = 5;
    }
    else if(binary <= 111111 && binary >=100000){
        bit = 6;
    }
    else if(binary <= 1111111 && binary >=1000000){
        bit = 7;
    }
	else if(binary <= 11111111 && binary >=10000000){
        bit = 8;
    }
	else if(binary <= 111111111 && binary >=100000000){
        bit = 9;
    }
	else if(binary <= 1111111111 && binary >=1000000000){
        bit = 10;
    }
	else if(binary <= th1 && binary >= th0){
        bit = 11;
    }
	else if(binary <= th1*11 && binary >= th0*10){
        bit = 12;
    }
	else if(binary <= th1*111 && binary >=th0*100){
        bit = 13;
    }
	else if(binary <= th1*1111 && binary >=th0*1000){
        bit = 14;
    }
	else if(binary <= th1*11111 && binary >=th0*10000){
        bit = 15;
    }
	else if(binary <= th1*111111 && binary >=th0*100000){
        bit = 16;
    }
	else if(binary <= th1*1111111 && binary >=th0*1000000){
        bit = 17;
    }
	else if(binary <= th1*11111111 && binary >=th0*10000000){
        bit = 18;
    }
	else if(binary <= th1*111111111 && binary >=th0*100000000){
        bit = 19;
    }
    else if(binary <= 1 && binary >= 0){
        bit = 1;
    }
	else{
		printf("binary:%lli\n", binary);
		cout<<"Only can support in 19 bits"<<endl;
		//system("PAUSE");
		exit(EXIT_SUCCESS);
	}
    return bit;
}

byte getdataword(byte divisor)
{
	byte dataword;
	int div_bit;
	int min;
    int max;
    
	//srand((unsigned int)time(NULL));
	div_bit = count_bit(dec2bin(divisor));
    //cout<<"div_bit:"<<div_bit<<endl;
	min = pow(2, div_bit) - 1;
    max = pow(2, 19-(div_bit-1)) - 1;
    
    //cout<<"min:"<<min<<endl;
	//cout<<"max:"<<max<<endl;
    
	//dataword = (rand()%105)+8;//8~(128-15) 15 for add noise
	dataword = (rand() % (max-min))+min;//min ~ (max-min)
	//max. & min. depend on input divisor bits
	
	//dataword = 255;
	//printf("%lld\n", dataword); //DEBUG
	return dataword;
}

byte enlargedataword(byte dataword, int add_bit)
{
	byte arg_dataword;
    
    arg_dataword = dataword << add_bit;
    //往左位移放大
    //cout<<"arg_dataword:"<<dec2bin(arg_dataword)<<endl;//arg_dataword DEBUG
	return arg_dataword;
}


byte generator(byte arg_dataword, byte divisor)
{
    int arg_bit;
    int div_bit;
    int xor_times;
	byte tmp;
	byte remainder;
    
	arg_bit = count_bit(dec2bin(arg_dataword));
    div_bit = count_bit(dec2bin(divisor));
	
	//cout<<"arg_bit:"<<arg_bit<<endl;
    
	xor_times = arg_bit - div_bit;
	if (xor_times < 0) return NULL;
	//cout<<"xor_times:"<<xor_times<<endl;
    //­計算最多需要XOR幾次
	divisor <<= xor_times;
    //因與arg_dataword作XOR關係需要往左位移
    
//    cout<<"arg_dataword:"<<dec2bin(arg_dataword)<<endl;//arg_dataword DEBUG
//    cout<<"divisor:"<<dec2bin(divisor)<<endl;//divisor DEBUG
	
    tmp = arg_dataword ^ divisor;
    divisor >>= 1;
    //cout<<"tmp:"<<dec2bin(tmp)<<endl;
	if (tmp == 0){
		remainder = tmp;
		return remainder;
	}
    
    for(int i=0; i<xor_times; i++){
        //cout<<"tmp:"<<dec2bin(tmp)<<endl;
        // cout<<"tmp XOR divisor:"<<dec2bin(tmp ^ divisor)<<endl<<endl;
        
        if ((tmp ^ divisor) > tmp) {
            divisor >>= 1;
            
        }else{
            remainder = tmp;
            //cout<<"Remainder:"<<dec2bin(remainder)<<endl;//remainder DEBUG
            tmp = tmp ^ divisor;
			divisor >>= 1;
			
            //cout<<"Remainder bit:"<<count_bit(dec2bin(remainder))<<endl;//remainder bit number DEBUG
        }
        //cout<<"Remainder:"<<dec2bin(remainder)<<endl;//remainder DEBUG
    }
	remainder = tmp;
    //cout<<"Remainder:"<<dec2bin(remainder)<<endl;//remainder DEBUG
    return remainder;
}

byte getcodeword(byte dataword, byte remainder, int add_bit)
{
	byte codeword;
	codeword = (dataword<<=add_bit) | remainder;
	return codeword;
}


byte narrowcodeword(byte codeword,  int add_bit)
{
	byte received_dataword;
	received_dataword = codeword >> add_bit;
	return received_dataword;
}

byte checker(byte codeword, byte divisor)
{
	int code_bit;
    int div_bit;
    int xor_times;
	byte tmp;
	byte syndrome;
    
	code_bit = count_bit(dec2bin(codeword));
    div_bit = count_bit(dec2bin(divisor));
    
    xor_times = code_bit - div_bit;
	if (xor_times < 0) return NULL;
	//cout<<"xor_times:"<<xor_times<<endl;
    //­計算最多需要XOR幾次
    
	divisor <<= xor_times;
    
	tmp = codeword ^ divisor;
    divisor >>= 1;
    
	if (tmp == 0){
		syndrome = tmp;
		return syndrome;
	}
    
    for(int i=0; i<xor_times; i++){
		//cout<<"tmp:"<<dec2bin(tmp)<<endl;
		//cout<<"tmp XOR divisor:"<<dec2bin(tmp ^ divisor)<<endl<<endl;
       
        if ((tmp ^ divisor) > tmp) {
            divisor >>= 1;
            
        }else{
            tmp = tmp ^ divisor;
			divisor >>= 1;
			syndrome = tmp;
            //cout<<"syndrome:"<<dec2bin(syndrome)<<endl;//remainder DEBUG
            //cout<<"Remainder bit:"<<count_bit(dec2bin(remainder))<<endl;//remainder bit number DEBUG
        }
        //cout<<"Remainder:"<<dec2bin(remainder)<<endl;//remainder DEBUG
    }
	syndrome = tmp;
	return syndrome;
}

byte decision(byte dataword, byte syndrome)
{
	if(syndrome == 0){
		cout<<"After decode get dataword:"<<dec2bin(dataword)<<endl;
	}else{
		cout<<"Discard Data:"<<dec2bin(dataword)<<endl;
	}
	return dataword;
}

byte channel(byte codeword, double errorrate=0.5)
{
	byte noise;
	byte error;
	byte random;
	
	cout<<endl<<"Through to the channel..."<<endl;
	
    //srand((unsigned int)time(NULL));
	//random = (100*((float)rand() / (float)(RAND_MAX+1))) * -1;
    random = (rand()%100)+1;
    //cout<<random<<endl;
	noise = (rand()%codeword);
    
	if(random > errorrate*100 && random <= 100){
		error = codeword;
    }
    else if(random > (errorrate*100*0.5)  && random <= errorrate*100){
        //cout<<"OR noise"<<endl;
        error = codeword | noise;
    }
    else{
        //cout<<"XOR noise"<<endl;
        error = codeword ^ noise;
    }
	return error;
}

bool comparedataword(byte dataword, byte received, byte syndrome)
{
	if(dataword != received && syndrome == 0)
		return false;
	else
		return true;
}

void logging(bool status)
{
	fstream file;
	file.open("trace.csv", ios_base::app);
	
	if(status){
		cout<<endl<<"CRC Detection Succeed!"<<endl;
		if(!file)
			cerr<<"open file error"<<endl;
		else
			file<<"CRC Detection Succeed, 1"<<endl;
	}else{
		cout<<endl<<"CRC Detection Fails!"<<endl;
		if(!file)
			cerr<<"open file error"<<endl;
		else
			file<<"CRC Detection Fails, 0"<<endl;
	}
	file.close();
}

byte getinput(byte divisor)
{
	byte dataword;
	cout<<"Input the Dataword:";
	cin>>dataword;
    
	//cout<<bin2dec(dataword)<<endl;
    if (count_bit(dec2bin(divisor)) > count_bit(dataword)){
        cout<<"The number of dataword's bits is less than divisor's"<<endl;
        exit(EXIT_SUCCESS);
    }
    dataword = bin2dec(dataword);
	return dataword;
}