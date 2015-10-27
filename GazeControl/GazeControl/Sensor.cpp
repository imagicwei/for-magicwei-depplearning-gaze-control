// stdafx.cpp : 僅包含標準 Include 檔的原始程式檔
// Standard Form.pch 會成為先行編譯標頭檔
// stdafx.obj 會包含先行編譯型別資訊

#include "stdafx.h"

double Sensor::getWaistTilt(){

	double ang = -(info->serialPort.rx.data.azimuth - 60);
	/*printf("%.2f \n", ang );*/
	return ang;
}


void Sensor::setCompassZero( double angle )
{
	double degree = 0;

	for ( int i=0 ; i<10 ; i++)
	{
		System::Threading::Thread::Sleep(30);
		degree += this->azimuthDegree;
	}

	degree /= 10.0;

	this->compassZero = degree + (-angle);

	if ( this->compassZero >= 360 )
		this->compassZero -= 360;
	else if ( this->compassZero < 0 )
		this->compassZero +=360;

	//修正卡曼濾波器要過一陣子才會歸0的問題
	this->azimuthKF.statePost.at<double>(0,0) = 0;
}

void Sensor::setRelativeAzimuth()
{

		if ( !info->runSimulation )
			this->relativeAzimuth = - (this->compassZero - this->azimuthDegree);
		else
			this->relativeAzimuth = + (this->compassZero - this->azimuthDegree);

		//this->relativeAzimuth = - (this->compassZero - this->azimuthDegree);

	if( this->relativeAzimuth > 180 )
		this->relativeAzimuth -= 360;
	else if( this->relativeAzimuth < -180 )
		this->relativeAzimuth += 360;

	this->calcRelativeAzimuthByKalman();
	//this->calcRelativeAzimuthByMediumFilter();


}

double Sensor::getRelativeAzimuth()
{
	return this->relativeAzimuth;
}

void Sensor::calcRelativeAzimuthByKalman()
{
	/*	kalman filter for relativeAzimuth	*/
	// 若在正負170內:relativeAzimuth 加上 kalman
	// 若在170~180,-170~-180時:relativeAzimuth 不加上 kalman ,避免卡曼濾波器在斷層時不穩
	if ( abs(this->relativeAzimuth) < 170 )
	{
		this->azimuthMeasurement.at<double>(0,0) = this->relativeAzimuth;
		this->azimuthKF.predict();
		this->azimuthKF.correct( this->azimuthMeasurement );
		this->relativeAzimuth = this->azimuthKF.statePost.at<double>(0,0);
	} 

	else
		this->azimuthKF.statePost.at<double>(0,0) = relativeAzimuth;
}

void Sensor::calcRelativeAzimuthByMediumFilter()
{
	/*	kalman filter for relativeAzimuth	*/
	// 若在正負170內:relativeAzimuth 加上 kalman
	// 若在170~180,-170~-180時:relativeAzimuth 不加上 kalman ,避免卡曼濾波器在斷層時不穩
	if ( abs(this->relativeAzimuth) < 170 )
	{
		this->relativeAzimuth = tool.mediumFilter( this->relativeAzimuth );
	} 
	else
		this->relativeAzimuth;
}

void Sensor::run()
{
	this->azimuthDegree = (double)info->serialPort.rx.data.azimuth;
	this->setRelativeAzimuth();
}

void Sensor::initial()
{
	double dt = 0;

	this->azimuthKF.init( 2 ,1 ,0 ,CV_64F );
	this->azimuthMeasurement.create( 1 ,1 ,CV_64F );
	this->azimuthMeasurement.setTo(cv::Scalar(0));
	this->azimuthKF.transitionMatrix = *(cv::Mat_<double>(2,2) << 1 ,dt ,0 ,1);
	cv::setIdentity( azimuthKF.measurementMatrix );
	cv::setIdentity( azimuthKF.processNoiseCov ,cv::Scalar::all(1e-4) );
	cv::setIdentity( azimuthKF.measurementNoiseCov ,cv::Scalar::all(1e-2) );
}