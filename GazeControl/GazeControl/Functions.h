#include "stdafx.h"

//this files contains all general functions in this project

#if !defined( FUNCTIONS_H ) 
#define FUNCTIONS_H 

//��J extern ���쥻�bheader�̭�����ơA�קK���ƫŧi 


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
	double calcDis( int x1, int y1, int x2, int y2 ); //�p����I�Z��
	double limitValue( double x, double min, double max ); //����Ʀr�d��A���h�b��W�U��
	int getSign( double input ); //���o���t��
	double getMax( double x, double y ); double getMax( double x, double y, double z ); //���o�̤j��
	double getMin( double x, double y ); double getMin( double x, double y, double z ); //���o�̤p��
	double pointDecimal( double x, int y );	//�p�ƿ�X���
	double getRandom( double min, double max); //�üƨ��Ʀr

	double getNormalize( double input, double min, double max ); //�^�Ǥ@�� 0 ~ 1 ���Ʀr
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