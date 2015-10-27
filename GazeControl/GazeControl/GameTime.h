#include "stdafx.h"

//this files contains 

#if !defined( TIME_H ) 
#define TIME_H 

//��J extern ���쥻�bheader�̭�����ơA�קK���ƫŧi 

class GameTime
{
	//members
	clock_t startTime;

public:
	
	GameTime(void);	 //Constructor
	~GameTime(void); //Destructor

	//Functions
	void reset();
	int getElapsedTime();
	int getElapsedMS();
	void outputSysTimeHeader();
	//void outputSysTimeHeader( char str[] );
	void outputSysTimeHeader( string str );
	string outputFileTimeString_txt();
	string outputFileTimeString_bmp();

};


#endif