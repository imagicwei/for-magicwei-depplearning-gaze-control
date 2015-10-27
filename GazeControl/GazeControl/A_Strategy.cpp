#include "stdafx.h"


A_Strategy::A_Strategy(void)
{

}
A_Strategy::~A_Strategy(void)
{
}

void A_Strategy::runInitial()
{
	//info->strategy.setNextBodyMotion( MOTION::BODY::NONE );
	info->strategy.setNextDistance( 0 );
	info->strategy.setNextAngle( 0 );
	info->strategy.setNextObject( 0 );
	info->strategy.setNextState( STATE::INITIAL );
	info->strategy.setNextHeadPos( 0,0 );
	info->strategy.setNextHeadSearchState( MOTION::HEAD::STATE::SEARCH_STRAIGHT );
	info->strategy.isBodyMotionDone = true;
	info->strategy.isBodyMotionDoing = false;
	info->strategy.isContineousMotionDone = true;
	info->strategy.isContineousMotionDoing = false;

	info->gameTime.reset();
}

void A_Strategy::run()
{

	switch( info->eventIndex )
	{
		case GAZECONTROL_EVENT::GAZECONTROl:	this->G_run();		break;
		default:								this->runInitial();	break;
	}

}

/*-----Gaze Control-----*/
void A_Strategy::G_run()
{
	switch( info->strategy.strategyState )
	{
		case STATE::INITIAL:				this->G_prepare();	break;
		case STATE::GAZECONTROl::AIM:		this->G_aim();		break;
		case STATE::GAZECONTROl::SHOOT:		this->G_shoot();	break;
		case STATE::GAZECONTROl::FINISH:	this->G_finish();	break;
		default:							this->G_finish();	break;
	}
}
void A_Strategy::G_prepare()
{
	if ( this->gaze.isReallyfindEye )
	{
		//真的有找到眼睛
		if ( !this->gaze.isInitialEyePoint )//還沒初始化過位置
		{
			printf( "\n定位眼睛初使位置\n");
			this->gaze.IniEyeX= info->vision.eyemaintX;
			this->gaze.IniEyeY = info->vision.eyemaintY;
			this->gaze.isInitialEyePoint = true;
		}
		
		//this->G_vector2motor( info->vision.eyeMoveVectorX,info->vision.eyeMoveVectorY );
		//info->strategy.setNextHeadPos( this->gaze.eyeAngY,this->gaze.eyeAngX);
		info->strategy.setNextState( STATE::GAZECONTROl::AIM );
		return;
	}
}
void A_Strategy::G_aim()
{

}
void A_Strategy::G_shoot()
{

}
void A_Strategy::G_finish()
{

}
void A_Strategy::G_vector2motor( int vecX, int vecY )
{
	/*initial eye boundary angle*/
	int leftAng,rightAng,topAng,bottomAng;
	leftAng = 58;
	rightAng = 98;
	topAng = 75;
	bottomAng = 75;
	/*計算跟四周的pixcels差*/
	int XL = this->gaze.IniEyeX;
	int XR = 320-this->gaze.IniEyeX;
	int YT = this->gaze.IniEyeY;
	int YB = 240-this->gaze.IniEyeY;

	//轉換角度
	if ( vecX < 0)
		this->gaze.eyeAngX = leftAng*((double)vecX/(double)XL);
	else
		this->gaze.eyeAngX = rightAng*((double)vecX/(double)XR);

	if ( vecY < 0)
		this->gaze.eyeAngY = bottomAng*((double)vecY/(double)YB);
	else
		this->gaze.eyeAngY = topAng*((double)vecY/(double)YT);

}
/*--------Follow--------*/
void A_Strategy::F_run()
{
	switch ( info->strategy.strategyState )
	{
		case STATE::INITIAL:
			this->F_Initial();
			break;
		case STATE::FOLLOW::LOOK_MARK:
			this->F_Look_Mark();
			break;
		case STATE::FOLLOW::FORWARD:
			this->F_Forward();
			break;
		case STATE::FOLLOW::NOFOUND:
			this->F_MarkNoFound();
			break;
		default:
			break;
	}
	return;
}
void A_Strategy::F_Initial()
{
	//initial all variables & parameters
	info->sensor.setCompassZero();
	info->strategy.setNextHeadSearchState( MOTION::HEAD::STATE::SEARCH_STRAIGHT );
	info->strategy.setNextObject( OBJECT::AUXILIARY::COLOR1 );

	//send motion
	info->strategy.setNextDistance( 0 );
	info->strategy.setNextAngle( 0 );
	info->strategy.setNextBodyMotion( MOTION::BODY::NONE );


	info->strategy.setNextBodyMotion( MOTION::BODY::STOP );
	info->strategy.setNextObject( OBJECT::AUXILIARY::COLOR1 );

	info->strategy.setNextState( STATE::FOLLOW::FORWARD );

}
void A_Strategy::F_Look_Mark()
{
	//找到mark
	if ( !info->objectRegion[OBJECT::AUXILIARY::COLOR1].empty() ) 
	{
		info->strategy.headTrackObject( OBJECT::AUXILIARY::COLOR1 );//Track color 1
		std::vector<ObjectRegion>::iterator mainMark = info->objectRegion[OBJECT::AUXILIARY::COLOR1].begin();

		info->strategy.kalmanFilter( &mainMark->robotCoordinate );

		info->strategy.setNextState( STATE::FOLLOW::FORWARD );
		info->strategy.setNextObject( OBJECT::AUXILIARY::COLOR1 );

		return;
	}
	//info->strategy.headSearch( 10, 55, 45 );
	info->strategy.headSearch( 30, 55, 45 );
    return;
}
void A_Strategy::F_Forward(){

	if ( !info->strategy.waitBodyMotionDone() )
		return;
	if ( !info->strategy.waitContineousMotionDone() )
		return;

	//先判斷有沒有找到mark，找不到就先找mark
	if ( info->objectRegion[OBJECT::AUXILIARY::COLOR1].empty() ) 
	{	
		info->strategy.setNextObject(OBJECT::AUXILIARY::COLOR1);
		info->strategy.setNextState( STATE::FOLLOW::NOFOUND );
		return;	
	}

	//如果有找到的話，根據中間mark的狀況去調整
	info->strategy.headTrackObject( OBJECT::AUXILIARY::COLOR1 , MOTION::HEAD::NO_FIX , 4 );
	std::vector<ObjectRegion>::iterator mainMark = info->objectRegion[OBJECT::AUXILIARY::COLOR1].begin();


	info->strategy.kalmanFilter( &mainMark->robotCoordinate );
	mainMark->calcDisAndAngle();

	double markAngle = mainMark->panAngle;
	double markDis = mainMark->dis;
	double markZ = mainMark->robotCoordinate.z;
	double compassAngle = info->sensor.getRelativeAzimuth();
	
	if ( abs( info->strategy.getWaistPanAngle() ) > 5 )
	{
		info->strategy.setNextWaistPanPos( 0 );
		return;
	}
	//go to next stage
	if ( mainMark->dis < this->follow.returnDis )
	{
		/*info->strategy.setNextBodyMotion(MOTION::BODY::STOP);*/
		info->strategy.setNextState( STATE::FOLLOW::CHANGE );
		info->strategy.setNextHeadSearchState( MOTION::HEAD::STATE::SEARCH_STRAIGHT );
		info->strategy.setNextObject(OBJECT::AUXILIARY::COLOR1);
		return;
	}
	else
	{
		//walk
		info->strategy.setNextAngle( mainMark->panAngle );
		info->strategy.setNextDistance( 200 );
		info->strategy.setNextBodyMotion( MOTION::BODY::WALK );
		//info->strategy.setNextBodyMotion( MOTION::BODY::STEP_FF );
		info->strategy.setNextObject(OBJECT::AUXILIARY::COLOR1);
		return;

	}


}
void A_Strategy::F_Walk(int distance, int angle)
{
	//motion send
	if ( abs(angle) < 5) 
		info->strategy.setNextAngle( 0.0 ); 
	else
		info->strategy.setNextAngle( angle );

	info->strategy.setNextDistance( distance );
	info->strategy.setNextBodyMotion( MOTION::BODY::WALK );

}
void A_Strategy::F_MarkNoFound()
{

	static int count = 0;
	static int count_turn = 0;
	//printf("\nNo Found\n");

	if ( !info->strategy.waitBodyMotionDone() )
		return;

	if ( info->objectRegion[OBJECT::AUXILIARY::COLOR1].empty() )
	{
		switch( info->strategy.headState ){
		case MOTION::HEAD::STATE::SEARCH_STRAIGHT :

			printf("\n CT:%d \n",count_turn);
			printf("\n C:%d \n",count);
			if ( count_turn == 2)
			{	
				printf("\nWaistPanAng0 = %f\n",info->strategy.getWaistPanAngle() );
				if ( abs( info->strategy.getWaistPanAngle() ) < 5 )
				{
					info->strategy.setNextBodyMotion( MOTION::BODY::TURN_R );
					Delay_ms(2500);
					count_turn=0;
					count =0;
					return;
				}
				else
				{
					info->strategy.setNextWaistPanPos( 0 );
					return;
				}
			}
			if (count%12==5)
			{
				printf("\nWaistPanAng@-30 = %f\n",info->strategy.getWaistPanAngle() );
				if ( info->strategy.getWaistPanAngle() > -35 && info->strategy.getWaistPanAngle() < -25 )
				{
					info->strategy.setNextWaistPanPos( -30 );
					info->strategy.setNextHeadSearchState( MOTION::HEAD::STATE::SEARCH_LEFT_THIRD );
					count_turn++;
					return;
				}
				else
				{
					info->strategy.setNextWaistPanPos( -30 );
					return;
				}
			}
			else if (count%12==10)
			{
				printf("\nWaistPanAng@30 = %f\n",info->strategy.getWaistPanAngle() );
				if ( info->strategy.getWaistPanAngle() < 35 && info->strategy.getWaistPanAngle() > 25 )
				{
					info->strategy.setNextWaistPanPos( 30 );
					info->strategy.setNextHeadSearchState( MOTION::HEAD::STATE::SEARCH_RIGHT_THIRD );
					count_turn++;
					return;
				}
				else
				{
					info->strategy.setNextWaistPanPos( 30 );
					return;
				}

			}
			else
			{
				if( info->strategy.setNextHeadPos( 50 ,0 ) )
				{	
					info->strategy.setNextHeadSearchState( MOTION::HEAD::STATE::SEARCH_RIGHT );
				}
			}

			break;

		case MOTION::HEAD::STATE::SEARCH_RIGHT:

			if( info->strategy.setNextHeadPos( 50 , -45 ) )
			{
				info->strategy.setNextHeadSearchState( MOTION::HEAD::STATE::SEARCH_LEFT );
				count++;
			}
			break;

		case MOTION::HEAD::STATE::SEARCH_LEFT:

			if( info->strategy.setNextHeadPos( 50 ,45 ) )
			{
				info->strategy.setNextHeadSearchState( MOTION::HEAD::STATE::SEARCH_STRAIGHT_TWICE );
				count++;
			}
			break;

		case MOTION::HEAD::STATE::SEARCH_STRAIGHT_TWICE:

			if( info->strategy.setNextHeadPos( 30 ,0 ) ){
				info->strategy.setNextHeadSearchState( MOTION::HEAD::STATE::SEARCH_RIGHT_TWICE );
				count++;
			}
			break;
		case MOTION::HEAD::STATE::SEARCH_LEFT_THIRD:

			if( info->strategy.setNextHeadPos( 30 , -30) )
			{
				info->strategy.setNextHeadSearchState( MOTION::HEAD::STATE::SEARCH_LEFT_FOURTH );

			}
			break;
		case MOTION::HEAD::STATE::SEARCH_LEFT_FOURTH:

			if( info->strategy.setNextHeadPos( 50 , -30) )
			{
				info->strategy.setNextHeadSearchState( MOTION::HEAD::STATE::SEARCH_STRAIGHT );
				count = 10;
			}
			break;
		case MOTION::HEAD::STATE::SEARCH_RIGHT_TWICE:

			if( info->strategy.setNextHeadPos( 30, 45 ) ){
				info->strategy.setNextHeadSearchState( MOTION::HEAD::STATE::SEARCH_LEFT_TWICE );
				count++;
			}	
			break;

		case MOTION::HEAD::STATE::SEARCH_RIGHT_THIRD:

			if( info->strategy.setNextHeadPos( 30, 45 ) ){
				info->strategy.setNextHeadSearchState( MOTION::HEAD::STATE::SEARCH_LEFT_FOURTH );
			}	
			break;

		case MOTION::HEAD::STATE::SEARCH_RIGHT_FOURTH:

			if( info->strategy.setNextHeadPos( 50, -45 ) ){
				info->strategy.setNextHeadSearchState( MOTION::HEAD::STATE::SEARCH_STRAIGHT );
			}	
			break;

		case MOTION::HEAD::STATE::SEARCH_LEFT_TWICE:

			if( info->strategy.setNextHeadPos( 30,45 ) ){
				info->strategy.setNextHeadSearchState( MOTION::HEAD::STATE::SEARCH_STRAIGHT );
				count++;
			}
			break;

		default:
			info->strategy.setNextHeadSearchState( MOTION::HEAD::STATE::SEARCH_STRAIGHT );

		}
	}
	else
	{
		info->strategy.setNextState( STATE::FOLLOW::CHANGE );
		return;
	}
	
}

