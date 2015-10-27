#include "stdafx.h"

//this files contains 

#if !defined( COMMON_INFO_H ) 
#define COMMON_INFO_H

//��J extern ���쥻�bheader�̭�����ơA�קK���ƫŧi 


class CommonInfo
{
public:
	ObjectColorRange TesthsvObjRange[8];


	//XtionControl*myXtion;
	Vision vision;
	Strategy strategy;
	SerialPort serialPort;
 	GameTime gameTime;
 	Sensor sensor;
	
	unsigned char eventIndex, subEventIndex;
	unsigned char subEventCountLimit;
	unsigned char robot;
	

	bool isCameraOpen;
	bool isXtionOpen;
	bool isSerialPortOpen;
	bool isStrategyRun;
	bool runSimulation;
	bool isReadingRefereeBox;
	bool isMotionControl;

	string fileName;
	double waistTiltAngle;

	std::vector<ObjectRegion> objectRegion[8]; //�ŧi8�ӪŶ�*/

	CommonInfo(void)
	{
		this->robot = ROBOT::ADULT;
		this->eventIndex = GAZECONTROL_EVENT::GAZECONTROl;
		this->subEventIndex = 0;
		this->subEventCountLimit = 0;

		this->isCameraOpen = false;
		this->isXtionOpen = false;
		this->isSerialPortOpen = false;
		this->isStrategyRun = false;
		this->runSimulation = false;
		this->isReadingRefereeBox = false;
		this->isMotionControl = false;

		this->fileName = "2015-8-17 21.47.21.txt";
		this->waistTiltAngle = 0;
	}

	~CommonInfo(void)
	{

	}

};

//extern�i�H�n���ܼƷ|�b�䥦����m�Q�w�q�A�o�Ӧ�m�i��O�b�P�@����󤧤��A�άO�b�䥦��󤧤�
extern CommonInfo *info;


#endif