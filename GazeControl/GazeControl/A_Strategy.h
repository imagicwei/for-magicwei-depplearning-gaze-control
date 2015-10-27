#include "stdafx.h"

//this files contains all of variable in this project

#if !defined( A_STRATEGY_H ) 
#define A_STRATEGY_H

//放入 extern 等原本在header裡面的資料，避免重複宣告 

class A_Follow
{
public:

	int returnDis;
	int delayCount;
	int smallTurnAngleLimit;
	int bigTurnAngleLimit;
	int ObjectPan;
	int ConStepDis;
	//mode
	bool isOnlyLookMark;
	int runMode;
	bool dipControlReset;
	bool compassForTurn;


	A_Follow()
	{
		this->returnDis = 1600;
		this->delayCount = 10;
		this->smallTurnAngleLimit = 10;
		this->bigTurnAngleLimit = 25;

		this->isOnlyLookMark = false;
		this->runMode = 0;
		this->dipControlReset = true;
		this->compassForTurn = true;

	}
};

class A_Gaze
{
public:
	bool isshoot;
	bool isInitialEyePoint;
	bool isReallyfindEye;

	int IniEyeX;
	int IniEyeY;
	double EyemainX;
	double EyemainY;

	double eyeAngX;//calculate the converted X angle;
	double eyeAngY;//calculate the converted Y angle;

	A_Gaze(){
		this->isshoot = false;
		this->isReallyfindEye = false;
		this->isInitialEyePoint = false;
		this->IniEyeX = 160;
		this->IniEyeY = 120;
		this->EyemainX = 160;
		this->EyemainY = 120;
	}
};

class A_GlobalPara
{
public:

	int sendDelayCount;
	bool needRestart;
	//bool disableBodyMotion;

	A_GlobalPara(){
		this->sendDelayCount = 0;
		//this->disableBodyMotion = false;
	}
};

class A_Strategy
{
public:

	A_Follow follow;
	A_Gaze gaze;
	A_GlobalPara globalpara;

	//strategy
	void run();
	void runInitial();
	
	//策略
	/* Gaze Control */
	void G_run();
	void G_prepare();
	void G_aim();
	void G_shoot();
	void G_finish();
	/*Gaze control function*/
	void G_vector2motor( int vecX,int vexY );
 	/* Follow */
	void F_run();
	void F_Look_Mark();
	void F_Initial();
	void F_Forward(); 
	void F_Finish();
	void F_Walk(int distance, int angle);
	void F_MarkNoFound();

 	//Sprint Functions
	void S_Walk( int distance, int angle );
	void S_Turn( int direction );


	A_Strategy(void);
	~A_Strategy(void);
};



#endif