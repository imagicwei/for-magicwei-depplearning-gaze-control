// stdafx.cpp : 僅包含標準 Include 檔的原始程式檔
// Standard Form.pch 會成為先行編譯標頭檔
// stdafx.obj 會包含先行編譯型別資訊

#include "stdafx.h"


Strategy::Strategy(void)
{
	//normal parameter
	this->strategyState = STATE::INITIAL;
	this->preStrategyState = STATE::INITIAL;
	this->preMotion = 0;
	this->headState = 0;
	this->isPreContiMotion = false;
	this->changeNextStrategy = false;

	//Monitor
	this->display1 = 0;
	this->display2 = 0;
	this->display3 = 0;

	//switch
	this->waitBodyMotionDoneEnable = true;
	this->objPosKalmanFilterEnable = true;
	this->forceBodyForwardEnable = false;
	this->opencvFormEnable = true;

	//count
	this->waitRobotStableCountBase = 1;
	this->waitRobotStableWait = 0;

	//GlobalPara
	this->sendDelayCount = 0;
	this->disableBodyMotion = false;

	//wifi motion
	this->isRevMotionDone = false;
	this->canDoNextMotion = true;

	//Kalman Filter Initialize
	KF.init( 6 ,3 ,0 );		//初始化卡曼濾波的維數
	measurement.create( 3 ,1 );
	measurement.setTo(cv::Scalar(0));
	KF.transitionMatrix = *(cv::Mat_<float>(6,6) << 1,0,0,0.05,0,0,   0,1,0,0,0.05,0,  0,0,1,0,0,0.05,  0,0,0,1,0,0,  0,0,0,0,1,0,  0,0,0,0,0,1 );
	cv::setIdentity( KF.measurementMatrix );
	cv::setIdentity( KF.processNoiseCov ,cv::Scalar::all(1e-4) );
	cv::setIdentity( KF.measurementNoiseCov ,cv::Scalar::all(1e-2) );
	cv::setIdentity( KF.errorCovPost ,cv::Scalar::all(.1) );

	//通用控制策略
	this->isBodyMotionDone = true;
	this->isBodyMotionDoing = false;
	this->isContineousMotionDone = true;
	this->isContineousMotionDoing = false;

}
Strategy::~Strategy(void)
{
}

//通用函式
void Strategy::kalmanFilter(cv::Point3d *point3d)
{
	if ( this->objPosKalmanFilterEnable )
	{
		static unsigned char preObjectIndex = 255;

		//先檢查是否為新的物件
		if ( info->vision.objectIndex != preObjectIndex )
		{	//是新的object，初始化卡曼的值
			KF.statePost.at<float>(0) = (float)point3d->x;
			KF.statePost.at<float>(1) = (float)point3d->y;
			KF.statePost.at<float>(2) = (float)point3d->z;
		} 
		else
		{	//若非新的object，則測量值為滑鼠移動後得到的robotCoordinate
			measurement(0) = (float)point3d->x;
			measurement(1) = (float)point3d->y;
			measurement(2) = (float)point3d->z;

			KF.predict();	//得到估計的結果
			KF.correct(measurement);	//得到加入觀察值校正後的狀態值

			point3d->x = (KF.statePost.at<float>(0));	//將校正後的正確值當成新的robotCoordinate
			point3d->y = (KF.statePost.at<float>(1));
			point3d->z = (KF.statePost.at<float>(2));
		}

		preObjectIndex = info->vision.objectIndex;
	}
}

//通用函式
void Strategy::kalmanFilter(cv::Point2d *point2d)
{
	if ( this->objPosKalmanFilterEnable )
	{
		static unsigned char preObjectIndex = 255;

		//先檢查是否為新的物件
		if ( info->vision.objectIndex != preObjectIndex )
		{	//是新的object，初始化卡曼的值
			KF.statePost.at<float>(0) = (float)point2d->x;
			KF.statePost.at<float>(1) = (float)point2d->y;
		} 
		else
		{	//若非新的object，則測量值為滑鼠移動後得到的robotCoordinate
			measurement(0) = (float)point2d->x;
			measurement(1) = (float)point2d->y;

			KF.predict();	//得到估計的結果
			KF.correct(measurement);	//得到加入觀察值校正後的狀態值

			point2d->x = (KF.statePost.at<float>(0));	//將校正後的正確值當成新的robotCoordinate
			point2d->y = (KF.statePost.at<float>(1));
		}

		preObjectIndex = info->vision.objectIndex;
	}
}

void Strategy::spilt()
{
	

}

double Strategy::getHeadTiltAngle()
{
	return ( 512-(double)info->serialPort.rx.data.tiltPos)*300.0/1024.0;
}

double Strategy::getHeadPanAngle()
{
	return ( 512-(double)info->serialPort.rx.data.panPos )*300.0/1024.0;
}

double Strategy::getWaistTiltAngle()
{
	return ( 2048-(double)info->serialPort.rx.data.waistPosTilt)*(360.0/3.0)/4096.0;	//106馬達，2048為腰0度的初始值
}

double Strategy::getWaistPanAngle()
{
	return ( (double) ( info->serialPort.rx.data.waistPosPan - 2048 ) * 360 / (4096*2) );
}

double Strategy::getWaistRollAngle()
{
	return ((double)info->serialPort.rx.data.waistPosRoll-2048)*(360.0/3.0)/4096.0;	//106馬達，2048為腰0度的初始值
}

bool Strategy::waitBodyMotionDone()
{
	
	if ( !this->waitBodyMotionDoneEnable )	//要不要等? 要等:繼續此函式
		return this->isBodyMotionDone=true;

	if( this->isBodyMotionDone )	//動作做完? 沒做完:繼續此函式
		return this->isBodyMotionDone;

	// not done, check whether it has finished
	if ( this->isBodyMotionDoing == false )
	{
		//剛做的瞬間
		if ( info->serialPort.rx.data.bodyDoingCode == info->serialPort.tx.data.bodyMotionCode )
		{
			//送出一個正在做的訊號給server
			this->isRevMotionDone = false;
		
			System::Threading::Thread::Sleep(30);
			this->setNextBodyMotion(MOTION::BODY::STOP);	//送出STOP			
			this->isBodyMotionDoing = true;
			this->isBodyMotionDone = false;

		}
	}

	if ( this->isBodyMotionDoing == true )
	{
		//送出一個完成的訊號給server
		this->isRevMotionDone = false;
;
		this->setNextBodyMotion(MOTION::BODY::STOP);	//送出STOP

		//做完的瞬間，當還沒收到 STOP 或 DONE 即無法進入 if
		if ( info->serialPort.rx.data.bodyDoingCode == MOTION::BODY::STOP || info->serialPort.rx.data.bodyDoingCode == MOTION::BODY::DONE )
		{
			this->isBodyMotionDoing = false;
			this->isBodyMotionDone = true;
			this->isRevMotionDone = true;
		}
	}

	return this->isBodyMotionDone;
}

bool Strategy::waitBodyMotionDoneExp()
{
	static int stopTimes = 0;

	if ( !this->waitBodyMotionDoneEnable )	//要不要等? 要等:繼續此函式
		return this->isBodyMotionDone=true;

	if( this->isBodyMotionDone )	//動作做完? 沒做完:繼續此函式
		return this->isBodyMotionDone;

	// not done, check whether it has finished
	if ( this->isBodyMotionDoing == false )
	{
		//剛做的瞬間

		System::Threading::Thread::Sleep(30);
		this->setNextBodyMotion(MOTION::BODY::STOP);	//送出STOP			
		this->isBodyMotionDoing = true;
		this->isBodyMotionDone = false;

		stopTimes = 0;

	}

	if ( this->isBodyMotionDoing == true )
	{
		this->setNextBodyMotion(MOTION::BODY::STOP);	//送出STOP

		//做完的瞬間，當還沒收到 STOP 或 DONE 即無法進入 if
		if ( info->serialPort.rx.data.bodyDoingCode == MOTION::BODY::STOP || info->serialPort.rx.data.bodyDoingCode == MOTION::BODY::DONE )
		{
			if ( stopTimes <= 2)
			{
				stopTimes++;
			}
			else
			{
				this->isBodyMotionDoing = false;
				this->isBodyMotionDone = true;
				stopTimes = 0;	
			}
		}

		else
		{
			stopTimes = 0;
		}
	}

	return this->isBodyMotionDone;
}

bool Strategy::waitRobotStable( double times ) 
{
  /*
  //穩定後再給true //this->setNextBodyMotion( MOTION::BODY::DONE );
  if( this->waitRobotStableWait > this->waitRobotStableCountBase * times ) 
  { 
    this->waitRobotStableWait = 0; 
    return true; 
  } 
  this->waitRobotStableWait++; 
  return false;
  */    

  static bool FirstExecuted = true; 
  static int startTime = 0;
  static int nowTime = 0;
  static int dt = 0;

  if(FirstExecuted == true)
  {
	  startTime = info->gameTime.getElapsedMS();
	  FirstExecuted = false;
  }  

  nowTime = info->gameTime.getElapsedMS();
  dt = nowTime - startTime;

  if ( dt < 0 )
  {
	  FirstExecuted =true;
  }

 this->waitRobotStableWait = dt;
 int waitTimeLeast = this->waitRobotStableCountBase * times * 1000;

 if ( waitTimeLeast < 1000)
	waitTimeLeast = 1000; //最低等待時間為1000ms

  if( dt > waitTimeLeast )
  {
    FirstExecuted = true;
    return true;
  }
 
  return false;
}


bool Strategy::waitContineousMotionDone()
{
	if ( !this->waitBodyMotionDoneEnable )	//要不要等? 要等:繼續此函式
		return this->isContineousMotionDone=true;

	if( this->isContineousMotionDone )	//動作做完? 沒做完:繼續此函式
		return this->isContineousMotionDone;

	//not done ,check whether it has finished
	if ( this->isContineousMotionDoing == false )
	{
		//剛做的瞬間
		if ( info->serialPort.rx.data.bodyDoingCode == info->serialPort.tx.data.bodyMotionCode )
		{
			this->setNextBodyMotion( MOTION::BODY::NONE );	//送出NONE
			this->isContineousMotionDone = false;
			this->isContineousMotionDoing = true;
		}
	}

	if ( this->isContineousMotionDoing == true )
	{
		this->setNextBodyMotion( MOTION::BODY::STOP );	//送出STOP

		//做完的瞬間，當還沒收到 STOP 或 DONE 即無法進入 if
		if ( info->serialPort.rx.data.bodyDoingCode == MOTION::BODY::STOP || info->serialPort.rx.data.bodyDoingCode == MOTION::BODY::DONE )
		{
			this->isContineousMotionDoing = false;
			this->isContineousMotionDone = true;
		}
	}

	return this->isContineousMotionDone;
}

bool Strategy::waitContinuousMotionStop()	//等連續動作切單步前一定要下此指令
{
	if ( info->serialPort.rx.data.bodyDoingCode > MOTION::BODY::STOP )
	{
		this->setNextBodyMotion( MOTION::BODY::STOP );
		return false;
	}else
		return true;
}

void Strategy::setNextBodyMotion( unsigned char code )
{
	
	//單步動作，非連續
	if ( code <= MOTION::BODY::STOP && code > MOTION::BODY::DONE )	
	{
		isBodyMotionDone = false;
		isContineousMotionDone = true;

		isPreContiMotion = false;

		//if ( code == MOTION::BODY::STOP )
			/*printf("TX = MOTION::BODY::STOP \n");*/
	}

	//連續動作
	if ( code > MOTION::BODY::STOP)
	{
		isBodyMotionDone = true;
		isContineousMotionDone = false;

		isPreContiMotion = true;
	}

	//不做身體動作，debug，實際不送出，只拿來顯示用
	if ( info->strategy.disableBodyMotion )
	{
		info->serialPort.tx.data.bodyMotionCode = MOTION::BODY::STOP;
		this->disableBodyMotionCode = code;
	}
	//實際做該動作
	else
		info->serialPort.tx.data.bodyMotionCode = code;

	//記錄這次所做的動作
	if (code != MOTION::BODY::STOP && code != MOTION::BODY::DONE)
		this->preMotion = code;

}

bool Strategy::setNextBodyMotion2( unsigned char code )
{
	
	if ( this->preMotion > MOTION::BODY::STOP )  //前一個動作為連續
	{
		//現在連續

		if ( code > MOTION::BODY::STOP)
		{
			if( !this->waitContinuousMotionStop() )
				return false;
		}

		//通用
		if (!this->waitBodyMotionDone())
			return false;
		
		//現在單步
		if ( code <= MOTION::BODY::STOP && code>MOTION::BODY::DONE )
		{
			if( !this->waitRobotStable() )
				return false;
		}
	}
	
	if ( this->preMotion <= MOTION::BODY::STOP && this->preMotion>MOTION::BODY::DONE)
	{
		//通用
		if (!this->waitBodyMotionDone())
			return false;
		
		//現在單步
		if ( code <= MOTION::BODY::STOP && code>MOTION::BODY::DONE )
		{
			if( !this->waitRobotStable() )
				return false;
		}
	}

	//先等stable之後，再送動作
	this->setNextBodyMotion(code);
	return true;

}

void Strategy::setNextDistance( double dis )
{
	dis /= 10;	// mm->cm

	if ( dis > 300 )
		dis = 300;
	else if( dis< -100 )
		dis = -100;

	info->serialPort.tx.data.dis = (short)dis;

	//硬體方只接受short float，故作一轉換
	//100代表解析度到小數點第二位，32768為2 byte unsighed的中間值( 2^16 /2=32768 )
	double tempDis = info->serialPort.tx.data.dis;
	info->serialPort.tx.arr[2] = (int) (tempDis*100+32768)%256;	
	info->serialPort.tx.arr[3] = (int) (tempDis*100+32768)/256;
}

void Strategy::setNextAngle( double angle )
{
	info->serialPort.tx.data.angle = (short)angle;

	//硬體方只接受short float，故作一轉換
	//100代表解析度到小數點第二位，32768為2 byte unsighed的中間值( 2^16 /2=32768 )
	double tempAngle = info->serialPort.tx.data.angle;
	info->serialPort.tx.arr[4] = (int) (tempAngle*100+32768)%256;
	info->serialPort.tx.arr[5] = (int) (tempAngle*100+32768)/256;
}



// void Strategy::setNextWalk( double dis, double angle )
// {
// 	this->setNextDistance( dis );
// 	this->setNextAngle( angle );
// 	this->setNextBodyMotion( MOTION::BODY::WALK );
// }

void Strategy::setNextObject( unsigned char code )
{
	info->vision.objectIndex = code;
}

void Strategy::setNextState( unsigned char state )
{
	
	this->preStrategyState = this->strategyState;
	this->strategyState = state;
	
}

void Strategy::setNextHeadSearchState( unsigned char head_search_state )
{
	this->headState = head_search_state;
}

bool Strategy::setNextHeadPanPos( double panAngle , unsigned char headVelocity )
{
	if ( abs(this->getHeadPanAngle() - panAngle) < 3 )
		return true;
	
	if ( headVelocity == MOTION::HEAD::GO_FAST )
		info->serialPort.tx.data.headMotionCode = MOTION::HEAD::GO_FAST;
	else if ( headVelocity == MOTION::HEAD::GO_MIDDLE )
		info->serialPort.tx.data.headMotionCode = MOTION::HEAD::GO_MIDDLE;
	else
		info->serialPort.tx.data.headMotionCode = MOTION::HEAD::GO_SLOW;


	/*info->serialPort.tx.data.panPos = 512 - (short)(panAngle*1024/300);*/

	if ( info->robot == ROBOT::ADULT )
		info->serialPort.tx.data.panPos  = 512 - (short) ( panAngle * 1024.0 / 300.0 );
	else if ( info->robot == ROBOT::KID )
		info->serialPort.tx.data.panPos  = 512 - (short) ( panAngle * 1024.0 / 300.0 );	

	return false;
}

bool Strategy::setNextHeadTiltPos( double tiltAngle , unsigned char headVelocity )
{
	if( abs(this->getHeadTiltAngle() - tiltAngle) < 5 )
		return true;

	if ( headVelocity == MOTION::HEAD::GO_FAST )
		info->serialPort.tx.data.headMotionCode = MOTION::HEAD::GO_FAST;
	else if ( headVelocity == MOTION::HEAD::GO_MIDDLE )
		info->serialPort.tx.data.headMotionCode = MOTION::HEAD::GO_MIDDLE;
	else
		info->serialPort.tx.data.headMotionCode = MOTION::HEAD::GO_SLOW;

	/*info->serialPort.tx.data.tiltPos = 512 + (short)(tiltAngle*1024/300);*/

	if ( info->robot == ROBOT::ADULT )
		info->serialPort.tx.data.tiltPos  = 512 - (short) ( tiltAngle * 1024.0 / 300.0 );
	else if ( info->robot == ROBOT::KID )
		info->serialPort.tx.data.tiltPos  = 512 + (short) ( tiltAngle * 1024.0 / 300.0 );
		
	return false;
}

bool Strategy::setNextHeadPos( double tiltAngle , double panAngle , unsigned char headVelocity )
{
// 	if (( abs(this->getHeadTiltAngle() - tiltAngle) < 5 && abs(this->getHeadPanAngle() - panAngle) < 3 ) )
// 		return true;
	if (( abs(this->getHeadTiltAngle() - tiltAngle) < 2 && abs(this->getHeadPanAngle() - panAngle) < 2 ) )
		return true;

/*	if ( headVelocity == MOTION::HEAD::GO_SLOW )*/
		info->serialPort.tx.data.headMotionCode = MOTION::HEAD::GO_SLOW;
// 	else if ( headVelocity == MOTION::HEAD::GO_MIDDLE )
// 		info->serialPort.tx.data.headMotionCode = MOTION::HEAD::GO_MIDDLE;
// 	else
// 		info->serialPort.tx.data.headMotionCode = MOTION::HEAD::GO_FAST;

/*	info->serialPort.tx.data.tiltPos = 512 + (short)(tiltAngle*1024/300);*/
/*	info->serialPort.tx.data.panPos = 512 - (short)(panAngle*1024/300);*/

	if ( info->robot == ROBOT::ADULT )
	{
		info->serialPort.tx.data.tiltPos  = 512 - (short) ( tiltAngle * 1024.0 / 300.0 );
		info->serialPort.tx.data.panPos  = 512 - (short) ( panAngle * 1024.0 / 300.0 );
	}
		
	else if ( info->robot == ROBOT::KID )
	{
		info->serialPort.tx.data.tiltPos  = 512 + (short) ( tiltAngle * 1024.0 / 300.0 );
		info->serialPort.tx.data.panPos  = 512 - (short) ( panAngle * 1024.0 / 300.0 );
	}
		

	return false;
}

bool Strategy::setNextHeadPos2( double tiltAngle , double panAngle )
{
	//保護：避免等待頭轉到特定位置時間太久而卡住
	static double firstInTime = 0;
	if (firstInTime == 0)
		firstInTime = info->gameTime.getElapsedMS();

	if (( abs(this->getHeadTiltAngle() - tiltAngle) < 5 && abs(this->getHeadPanAngle() - panAngle) < 3 ) ||
		( (info->gameTime.getElapsedMS() - firstInTime) > 1600))
	{
		firstInTime = 0;
		return true;
	}

	info->serialPort.tx.data.headMotionCode = MOTION::HEAD::GO_SLOW;

	if ( info->robot == ROBOT::ADULT )
	{
		info->serialPort.tx.data.tiltPos  = 512 - (short) ( tiltAngle * 1024.0 / 300.0 );
		info->serialPort.tx.data.panPos  = 512 - (short) ( panAngle * 1024.0 / 300.0 );
	}

	else if ( info->robot == ROBOT::KID )
	{
		info->serialPort.tx.data.tiltPos  = 512 + (short) ( tiltAngle * 1024.0 / 300.0 );
		info->serialPort.tx.data.panPos  = 512 - (short) ( panAngle * 1024.0 / 300.0 );
	}

	return false;
}

bool Strategy::setNextWaistPanPos( double panAngle )
{
	if ( abs(this->getWaistPanAngle() - panAngle) < 3 )
 		return true;

	this->setNextAngle( panAngle );
	info->serialPort.tx.data.bodyMotionCode = MOTION::BODY::TWIST_WAIST;
	return false;
}

bool Strategy::headTrackObject( unsigned char objIndex )
{
	return this->headTrackObject( objIndex , MOTION::HEAD::NO_FIX, 75 );
}

bool Strategy::headTrackObject( unsigned char objIndex, int panLimit )
{
	return this->headTrackObject( objIndex , MOTION::HEAD::NO_FIX, panLimit );
}

bool Strategy::headTrackObjectOld2013( unsigned char objIndex , unsigned char mode , unsigned char headVelocity )
{
	if (objIndex != info->vision.objectIndex)
		return true;

	if( info->objectRegion[objIndex].empty() )
		return true;

	double kp;
	double HAOV;	//horizontal angle of view
	double VAOV;	//vertical angle of view

		 kp = 0.25;
		 HAOV = 80;	//horizontal angle of view
		 VAOV = 60;	//vertical angle of view

	cv::Point2d trackPoint;
	std::vector<ObjectRegion>::iterator obj = info->objectRegion[objIndex].begin();
	for(  ; obj!=info->objectRegion[objIndex].end() ; obj++ )
	{
		trackPoint.x += obj->mainPoint.x;	//將所有找到物件的中心保持在畫面中心
		trackPoint.y += obj->mainPoint.y;
	}
	trackPoint.x /= info->objectRegion[objIndex].size();	//除以找到物件總數才是平均值
	trackPoint.y /= info->objectRegion[objIndex].size();

	double tiltAngle = this->getHeadTiltAngle() + kp*VAOV*( trackPoint.y-info->vision.camHeight/2 )/info->vision.camHeight;
	double panAngle = this->getHeadPanAngle() + kp*HAOV*( trackPoint.x-info->vision.camWidth/2 )/info->vision.camWidth;

	//constrain
	tiltAngle = (tiltAngle<5) ? 5 : (tiltAngle>75) ? 75 : tiltAngle;
	panAngle = (panAngle>45) ? 45 : (panAngle<-45) ? -45 : panAngle;
	
	if( mode == MOTION::HEAD::FIX_TILT )
		return this->setNextHeadPanPos( panAngle ,headVelocity );
	else if( mode == MOTION::HEAD::FIX_PAN )
		return this->setNextHeadTiltPos( tiltAngle ,headVelocity );
	else // if ( mode == MOTION::HEAD::NO_FIX )
		return this->setNextHeadPos( tiltAngle , panAngle , headVelocity );
}


bool Strategy::headTrackObject( unsigned char objIndex , unsigned char mode , int panLimit, unsigned char headVelocity )
{
	if (objIndex != info->vision.objectIndex)
		return true;

	if( info->objectRegion[objIndex].empty() )
		return true;

	cv::Point2d trackPoint;
	std::vector<ObjectRegion>::iterator obj = info->objectRegion[objIndex].begin();
	for(  ; obj!=info->objectRegion[objIndex].end() ; obj++ )
	{
		trackPoint.x += obj->mainPoint.x;	//將所有找到物件的中心保持在畫面中心
		trackPoint.y += obj->mainPoint.y;
	}
	trackPoint.x /= info->objectRegion[objIndex].size();	//除以找到物件總數才是平均值
	trackPoint.y /= info->objectRegion[objIndex].size();
 
 
	double tiltAngle = this->getHeadTiltAngle();
	double panAngle = this->getHeadPanAngle();
	double factor = 0.07;

	//pan angle
	if ( abs(trackPoint.x - 320) > 5 )
			panAngle += (trackPoint.x - 320) * factor;

	//tilt angle
	if ( abs( trackPoint.y - 240) > 5 )
			tiltAngle += ( trackPoint.y - 240 ) * factor;

	
	//constrain
// 	tiltAngle = (tiltAngle<-20) ? -20 : (tiltAngle>85) ? 85 : tiltAngle;
// 	panAngle = (panAngle>75) ? 75 : (panAngle<-75) ? -75 : panAngle;
	tiltAngle = tool.limitValue( tiltAngle, -20, 85 );
	panAngle = tool.limitValue( panAngle, -panLimit, panLimit );
	
	if( mode == MOTION::HEAD::FIX_TILT )
		return this->setNextHeadPanPos( panAngle ,headVelocity );
	else if( mode == MOTION::HEAD::FIX_PAN )
		return this->setNextHeadTiltPos( tiltAngle ,headVelocity );
	else // if ( mode == MOTION::HEAD::NO_FIX )
		return this->setNextHeadPos( tiltAngle , panAngle , headVelocity );
}

bool Strategy::headTrackObject( unsigned char objIndex , unsigned char mode , int left_Limit, int right_Limit, unsigned char headVelocity )
{
	if (objIndex != info->vision.objectIndex)
		return true;

	if( info->objectRegion[objIndex].empty() )
		return true;

	cv::Point2d trackPoint;
	std::vector<ObjectRegion>::iterator obj = info->objectRegion[objIndex].begin();
	for(  ; obj!=info->objectRegion[objIndex].end() ; obj++ )
	{
		trackPoint.x += obj->mainPoint.x;	//將所有找到物件的中心保持在畫面中心
		trackPoint.y += obj->mainPoint.y;
	}
	trackPoint.x /= info->objectRegion[objIndex].size();	//除以找到物件總數才是平均值
	trackPoint.y /= info->objectRegion[objIndex].size();


	double tiltAngle = this->getHeadTiltAngle();
	double panAngle = this->getHeadPanAngle();
	double factor = 0.07;

	//pan angle
	if ( abs(trackPoint.x - 320) > 5 )
		panAngle += (trackPoint.x - 320) * factor;

	//tilt angle
	if ( abs( trackPoint.y - 240) > 5 )
		tiltAngle += ( trackPoint.y - 240 ) * factor;


	//constrain
	// 	tiltAngle = (tiltAngle<-20) ? -20 : (tiltAngle>85) ? 85 : tiltAngle;
	// 	panAngle = (panAngle>75) ? 75 : (panAngle<-75) ? -75 : panAngle;
	tiltAngle = tool.limitValue( tiltAngle, -20, 85 );
	panAngle = tool.limitValue( panAngle, left_Limit, right_Limit );

	if( mode == MOTION::HEAD::FIX_TILT )
		return this->setNextHeadPanPos( panAngle ,headVelocity );
	else if( mode == MOTION::HEAD::FIX_PAN )
		return this->setNextHeadTiltPos( tiltAngle ,headVelocity );
	else // if ( mode == MOTION::HEAD::NO_FIX )
		return this->setNextHeadPos( tiltAngle , panAngle , headVelocity );
}


bool Strategy::headTrackObjectExp( unsigned char objIndex , int headTiltLimit, int headPanLimit )
{
	if (objIndex != info->vision.objectIndex)
		return true;

	if( info->objectRegion[objIndex].empty() )
		return true;

	double kp = 0.25;
	double HAOV = 80;	//horizontal angle of view
	double VAOV = 60;	//vertical angle of view

	cv::Point2d trackPoint;
	std::vector<ObjectRegion>::iterator obj = info->objectRegion[objIndex].begin();
	for(  ; obj!=info->objectRegion[objIndex].end() ; obj++ )
	{
		trackPoint.x += obj->mainPoint.x;	//將所有找到物件的中心保持在畫面中心
		trackPoint.y += obj->mainPoint.y;
	}
	trackPoint.x /= info->objectRegion[objIndex].size();	//除以找到物件總數才是平均值
	trackPoint.y /= info->objectRegion[objIndex].size();

	double tiltAngle = this->getHeadTiltAngle() + kp*VAOV*( trackPoint.y-info->vision.camHeight/2 )/info->vision.camHeight;
	double panAngle = this->getHeadPanAngle() + kp*HAOV*( trackPoint.x-info->vision.camWidth/2 )/info->vision.camWidth;

	//constrain
// 	tiltAngle = (tiltAngle < headTiltLimit) ? headTiltLimit : (tiltAngle > 75) ? 75 : tiltAngle;
// 	panAngle = (panAngle < -headPanLimit ) ? -headPanLimit : (panAngle > headPanLimit ) ? headPanLimit : panAngle;
	tiltAngle = tool.limitValue( (int)tiltAngle, (int)headTiltLimit, (int)75 );
	panAngle = tool.limitValue( (int)panAngle, (int)-headPanLimit, (int)headPanLimit );

	return this->setNextHeadPos( tiltAngle , panAngle );
}


bool Strategy::forceBodyForward()
{
	if ( !this->forceBodyForwardEnable )
		return true;

	double angle = info->sensor.getRelativeAzimuth();
	if ( abs(angle) > 10 )
	{
		if ( angle > 0 )
			this->setNextBodyMotion( MOTION::BODY::TURN_L );
		else
			this->setNextBodyMotion( MOTION::BODY::TURN_R );
		
		return false;
	}
	return true;
}

bool Strategy::forceBodyForward( int limitAngle )
{
	if ( !this->forceBodyForwardEnable )
		return true;

	double angle = info->sensor.getRelativeAzimuth();
	if ( abs(angle) > limitAngle )
	{
		if ( angle > 0 )
			this->setNextBodyMotion( MOTION::BODY::TURN_L );
		else
			this->setNextBodyMotion( MOTION::BODY::TURN_R );

		return false;
	}
	return true;
}


bool Strategy::headSearch( int minTilt, int maxTilt, int panRange )
{
	static bool searched[6] = { false, false, false, false, false, false };
	
	switch( info->strategy.headState ){

	case MOTION::HEAD::STATE::SEARCH_LEFT:
		if( info->strategy.setNextHeadPos2( minTilt ,-panRange ) )
			info->strategy.setNextHeadSearchState( MOTION::HEAD::STATE::SEARCH_STRAIGHT );
		searched[0] = true;
		break;

	case MOTION::HEAD::STATE::SEARCH_STRAIGHT :
		if( info->strategy.setNextHeadPos2( minTilt ,0 ) )
			info->strategy.setNextHeadSearchState( MOTION::HEAD::STATE::SEARCH_RIGHT );
		searched[1] = true;
		break;

	case MOTION::HEAD::STATE::SEARCH_RIGHT:
		if( info->strategy.setNextHeadPos2( minTilt , panRange ) )
			info->strategy.setNextHeadSearchState( MOTION::HEAD::STATE::SEARCH_RIGHT_TWICE );
		searched[2] = true;
		break;

	case MOTION::HEAD::STATE::SEARCH_RIGHT_TWICE:
		if( info->strategy.setNextHeadPos2( maxTilt , panRange ) )
			info->strategy.setNextHeadSearchState( MOTION::HEAD::STATE::SEARCH_STRAIGHT_TWICE );
		searched[3] = true;
		break;

	case MOTION::HEAD::STATE::SEARCH_STRAIGHT_TWICE:
		if( info->strategy.setNextHeadPos2( maxTilt , 0 ) )
			info->strategy.setNextHeadSearchState( MOTION::HEAD::STATE::SEARCH_LEFT_TWICE );
		searched[4] = true;
		break;

	case MOTION::HEAD::STATE::SEARCH_LEFT_TWICE:
		if( info->strategy.setNextHeadPos2( maxTilt, -panRange ) )
			info->strategy.setNextHeadSearchState( MOTION::HEAD::STATE::SEARCH_LEFT );
		searched[5] = true;
		break;

	default:
		info->strategy.setNextHeadSearchState( MOTION::HEAD::STATE::SEARCH_STRAIGHT );
		break;

	}

	if ( searched[0] && searched[1] && searched[2] && searched[3] && searched[4] && searched[5] )
	{
		for ( int i = 0 ; i < 6 ; i++ )
		{
			searched[i] = false;
		}
		return true;
	}
	else
		return false;


}
bool Strategy::headSearch4Points( int minTilt, int maxTilt, int panRange, bool reset )
{
	static bool searched[4] = { false, false, false, false };

	if ( reset )
	{
		for ( int i = 0 ; i < 4 ; i++ )
		{
			searched[i] = false;
		}
		return false;
	}

	switch( info->strategy.headState ){

	case MOTION::HEAD::STATE::SEARCH_LEFT:
		if( info->strategy.setNextHeadPos2( minTilt/2+maxTilt/2 ,-panRange ) )
		{
			info->strategy.setNextHeadSearchState( MOTION::HEAD::STATE::SEARCH_STRAIGHT );
			searched[0] = true;
		}
		break;

	case MOTION::HEAD::STATE::SEARCH_STRAIGHT :
		if( info->strategy.setNextHeadPos2( minTilt ,0 ) )
		{
			info->strategy.setNextHeadSearchState( MOTION::HEAD::STATE::SEARCH_RIGHT );
			searched[1] = true;
		}
		break;

	case MOTION::HEAD::STATE::SEARCH_RIGHT:
		if( info->strategy.setNextHeadPos2( minTilt/2+maxTilt/2 , panRange ) )
		{
			info->strategy.setNextHeadSearchState( MOTION::HEAD::STATE::SEARCH_STRAIGHT_TWICE );
			searched[2] = true;
		}
		break;

	case MOTION::HEAD::STATE::SEARCH_STRAIGHT_TWICE:
		if( info->strategy.setNextHeadPos2( maxTilt , 0 ) )
		{
			info->strategy.setNextHeadSearchState( MOTION::HEAD::STATE::SEARCH_LEFT );
			searched[3] = true;
		}
		break;

	default:
		info->strategy.setNextHeadSearchState( MOTION::HEAD::STATE::SEARCH_STRAIGHT );
		break;

	}

	if ( searched[0] && searched[1] && searched[2] && searched[3] )
	{
		for ( int i = 0 ; i < 4 ; i++ )
		{
			searched[i] = false;
		}
		return true;
	}

	else
		return false;


}


bool Strategy::headSearch4Points( int minTilt, int maxTilt, int panRange )
{
	static bool searched[4] = { false, false, false, false };

	switch( info->strategy.headState ){

	case MOTION::HEAD::STATE::SEARCH_LEFT:
		if( info->strategy.setNextHeadPos2( minTilt/2+ maxTilt/2,-panRange ) )
			info->strategy.setNextHeadSearchState( MOTION::HEAD::STATE::SEARCH_STRAIGHT );
		searched[0] = true;
		break;

	case MOTION::HEAD::STATE::SEARCH_STRAIGHT :
		if( info->strategy.setNextHeadPos2( minTilt ,0 ) )
			info->strategy.setNextHeadSearchState( MOTION::HEAD::STATE::SEARCH_RIGHT );
		searched[1] = true;
		break;

	case MOTION::HEAD::STATE::SEARCH_RIGHT:
		if( info->strategy.setNextHeadPos2( minTilt/2+ maxTilt/2 , panRange ) )
			info->strategy.setNextHeadSearchState( MOTION::HEAD::STATE::SEARCH_RIGHT_TWICE );
		searched[2] = true;
		break;

	case MOTION::HEAD::STATE::SEARCH_STRAIGHT_TWICE:
		if( info->strategy.setNextHeadPos2( maxTilt , 0 ) )
			info->strategy.setNextHeadSearchState( MOTION::HEAD::STATE::SEARCH_LEFT );
		searched[3] = true;
		break;

	default:
		info->strategy.setNextHeadSearchState( MOTION::HEAD::STATE::SEARCH_STRAIGHT );
		break;

	}

	if ( searched[0] && searched[1] && searched[2] && searched[3] )
	{
		for ( int i = 0 ; i < 4 ; i++ )
		{
			searched[i] = false;
		}
		return true;
	}
	else
		return false;

}

double Strategy::onepointDepthDis( int x, int y )
{
	int pointX = x/2; 
	int pointY = y/2;

	return this->DepthDisArr[pointX][pointY]; //回傳深度矩陣內的值
}
double Strategy::twopointDepthDis( int x1,int y1, int x2, int y2 )
{
	return 0;
}
double Strategy::threepointDepthDis( int x1, int y1, int x2, int y2, int x3, int y3 )
{
	return 0;
}