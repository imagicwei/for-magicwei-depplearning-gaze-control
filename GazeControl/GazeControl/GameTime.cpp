// stdafx.cpp : 僅包含標準 Include 檔的原始程式檔
// Standard Form.pch 會成為先行編譯標頭檔
// stdafx.obj 會包含先行編譯型別資訊

#include "stdafx.h"

GameTime::GameTime(void)
{
	this->reset();
}


GameTime::~GameTime(void)
{

}

void GameTime::reset()
{
	startTime = clock();
}

int GameTime::getElapsedTime()
{
	return (int)( clock()-startTime )/CLOCKS_PER_SEC;
}

int GameTime::getElapsedMS()
{
	return (int)( clock()-startTime );
}

void GameTime::outputSysTimeHeader(){

	time_t t = time(0);
	char tmp[64];
	strftime( tmp, sizeof(tmp), "%Y-%m-%d %X %A 本年第%j天 %z",localtime(&t) );
	puts( tmp );


}

void GameTime::outputSysTimeHeader( string outputFile ){

	time_t t = time(0);
	char tmp[64];
	strftime( tmp, sizeof(tmp), "%Y-%m-%d %X %A 本年第%j天 %z",localtime(&t) );

	char outputFileChar[50] = ".\\Logs\\";
	strcat(outputFileChar,outputFile.c_str());

	FILE *txt;
	txt = fopen( outputFileChar, "a" );
	fprintf( txt, "\n --- %s --- \n", tmp );
	fclose(txt);

}

string GameTime::outputFileTimeString_txt(){

	time_t t = time(0);
	char tmp[50];
	strftime( tmp, sizeof(tmp), "%Y-%m-%d %H.%M.%S.txt",localtime(&t) );

	string tmpStr(tmp);
	return tmpStr;
}

string GameTime::outputFileTimeString_bmp(){

	time_t t = time(0);
	char tmp[50];
	strftime( tmp, sizeof(tmp), ".\\Logs\\%Y-%m-%d %H.%M.%S.bmp",localtime(&t) );
	string tmpStr(tmp);
	return tmpStr;
}
