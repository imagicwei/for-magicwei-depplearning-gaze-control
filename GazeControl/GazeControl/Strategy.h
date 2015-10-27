#include "stdafx.h"

//this files contains 

#if !defined( STRATEGY_H ) 
#define STRATEGY_H 

//��J extern ���쥻�bheader�̭�����ơA�קK���ƫŧi 


class Strategy
{
public:

	A_Strategy adult;


	//normal parameter
	unsigned char strategyState;
	unsigned char preStrategyState;
	int preMotion;
	int headState;
	bool isPreContiMotion;
	bool changeNextStrategy;

	//Monitor parameter
	double display1;
	double display2;
	double display3;

	//switch
	bool waitBodyMotionDoneEnable;
	bool objPosKalmanFilterEnable;
	bool forceBodyForwardEnable;
	bool opencvFormEnable;

	//GlobalPara
	int sendDelayCount;
	bool disableBodyMotion;
	unsigned char disableBodyMotionCode;

	//count
	int waitRobotStableCountBase;
	int waitRobotStableWait;

	//Kalman Filter
	cv::KalmanFilter KF;	/* (x, y, z, delta_x, delta_y, delta_z) */
	cv::Mat_<float> measurement;
	void kalmanFilter(cv::Point3d *point3d);
	void kalmanFilter(cv::Point2d *point2d);

	//Wifi receive motion
	bool isRevMotionDone; //�P�_�e�X�Ӫ��ʧ@�O�_���n�F
	bool canDoNextMotion;

	//strategy
	void run();
	void runInitial();

	//�q�α����
	bool isBodyMotionDone;
	bool isBodyMotionDoing;
	bool isContineousMotionDone;
	bool isContineousMotionDoing;

	//�`����v���Z���x�}
	double DepthDisArr[320][240];
	
	
	//�q�Ψ禡
	bool waitBodyMotionDone();
	bool waitBodyMotionDoneExp();
	bool waitRobotStable( double times = 1 );
	/*bool waitRobotStable();*/
	bool waitContineousMotionDone();
	bool waitContinuousMotionStop();
	bool setNextHeadPanPos( double panAngle , unsigned char headVelocity = 2 );
	bool setNextHeadTiltPos( double tiltAngle , unsigned char headVelocity = 2 );
	bool setNextHeadPos( double tiltAngle , double panAngle , unsigned char headVelocity = 2 );
	bool setNextHeadPos2( double tiltAngle , double panAngle );
	bool headTrackObject( unsigned char objIndex  );
	bool headTrackObject( unsigned char objIndex, int panLimit  );
	bool headTrackObject( unsigned char objIndex , unsigned char mode , int panLimit, unsigned char headVelocity = 2 );
	bool headTrackObject( unsigned char objIndex , unsigned char mode , int left_Limit, int right_Limit, unsigned char headVelocity = 2 );
	bool headTrackObjectOld2013( unsigned char objIndex , unsigned char mode , unsigned char headVelocity = 2 );
	bool headTrackObjectExp( unsigned char objIndex , int headTiltLimit, int headPanLimit );
	bool forceBodyForward();
	bool forceBodyForward( int limitAngle );
	bool setNextWaistPanPos( double panAngle );

	bool headSearch( int minTilt, int maxTilt, int panRange );
	bool headSearch4Points( int minTilt, int maxTilt, int panRange, bool reset );
	/*void headSearch( int firstTilt, int secondTilt, int firstPan, int secondPan );*/
	bool headSearch4Points( int minTilt, int maxTilt, int panRange );

	double getHeadPanAngle();
	double getHeadTiltAngle();
	double getWaistTiltAngle();
	double getWaistPanAngle();
	double getWaistRollAngle();

	void setNextBodyMotion( unsigned char code );
	bool setNextBodyMotion2( unsigned char code );
	void setNextDistance( double dis );
	void setNextAngle( double angle );
	void setNextObject( unsigned char code );
	void setNextState( unsigned char state );
	void setNextHeadSearchState( unsigned char head_search_state );
	void spilt();
	void msgRev();
	
	//�`�� ���[�禡
	double onepointDepthDis( int x, int y );
	double twopointDepthDis( int x1, int y1, int x2, int y2 );
	double threepointDepthDis( int x1, int y1, int x2, int y2, int x3, int y3 );
	double neckjointPos( int nexkX , int neckY );

	Strategy();
	~Strategy();


};


#endif