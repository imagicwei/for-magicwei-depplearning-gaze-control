// stdafx.cpp : �ȥ]�t�з� Include �ɪ���l�{����
// Standard Form.pch �|��������sĶ���Y��
// stdafx.obj �|�]�t����sĶ���O��T

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

	//�ץ��d���o�i���n�L�@�}�l�~�|�k0�����D
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
	// �Y�b���t170��:relativeAzimuth �[�W kalman
	// �Y�b170~180,-170~-180��:relativeAzimuth ���[�W kalman ,�קK�d���o�i���b�_�h�ɤ�í
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
	// �Y�b���t170��:relativeAzimuth �[�W kalman
	// �Y�b170~180,-170~-180��:relativeAzimuth ���[�W kalman ,�קK�d���o�i���b�_�h�ɤ�í
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