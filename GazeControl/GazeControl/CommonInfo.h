#include "stdafx.h"

//this files contains 

#if !defined( COMMON_INFO_H ) 
#define COMMON_INFO_H

//放入 extern 等原本在header裡面的資料，避免重複宣告 


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

	std::vector<ObjectRegion> objectRegion[8]; //宣告8個空間*/

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

//extern可以聲明變數會在其它的位置被定義，這個位置可能是在同一份文件之中，或是在其它文件之中
extern CommonInfo *info;


#endif