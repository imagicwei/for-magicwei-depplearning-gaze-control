#include "stdafx.h"

//this files contains 

#if !defined( SENSOR_H ) 
#define SENSOR_H 

//��J extern ���쥻�bheader�̭�����ơA�קK���ƫŧi 
class Sensor
{
public:

	//members
	double azimuthDegree;
	double compassZero;
	double relativeAzimuth;

	cv::KalmanFilter azimuthKF;
	cv::Mat azimuthMeasurement;

	//Constructor
	Sensor(void)
	{
		this->azimuthDegree = 0;
		this->compassZero = 0;
		this->relativeAzimuth = 0;
		this->initial();
	}

	//Destructor
	~Sensor(void)
	{

	}

	//Functions
	void initial();
	void run();
	void setCompassZero( double angle = 0 );
	void setRelativeAzimuth();

	void calcRelativeAzimuthByKalman();
	void calcRelativeAzimuthByMediumFilter();
	double getRelativeAzimuth();

	double getWaistTilt();

};

#endif