#include "stdafx.h"

//this files contains all general functions in this project

#if !defined( FUNCTIONS_H ) 
#define FUNCTIONS_H 

//放入 extern 等原本在header裡面的資料，避免重複宣告 


class Rgb2Hsv
{
 public:
	 float R,G,B;
	 float R0,G0,B0;
	 float H,S,V;
	 void RGB2HSV(float R, float G, float B);
};


class Tool
{
public:
	double calcDis( int x1, int y1, int x2, int y2 ); //計算兩點距離
	double limitValue( double x, double min, double max ); //限制數字範圍，頂多在於上下界
	int getSign( double input ); //取得正負號
	double getMax( double x, double y ); double getMax( double x, double y, double z ); //取得最大值
	double getMin( double x, double y ); double getMin( double x, double y, double z ); //取得最小值
	double pointDecimal( double x, int y );	//小數輸出位數
	double getRandom( double min, double max); //亂數取數字

	double getNormalize( double input, double min, double max ); //回傳一個 0 ~ 1 的數字
	double pointYOnLine ( double x, double x1, double y1, double x2, double y2 ); 
	double getSlope( double x1, double y1, double x2, double y2 );

	double calcPolarAngle( int x, int y, int cx, int cy );
	int calcCartesianX( int radius, int angle, int cx, int cy);
	int calcCartesianY( int radius, int angle, int cx, int cy);
	int setAngleInRange ( int ang );

	double mediumFilter( double input );
	void swap( double *x, double *y ); 

	void writeTxt ( char fileName[], char word[] );

};

extern Tool tool;

#endif