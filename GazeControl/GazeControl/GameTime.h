#include "stdafx.h"

//this files contains 

#if !defined( TIME_H ) 
#define TIME_H 

//放入 extern 等原本在header裡面的資料，避免重複宣告 

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