#include "stdafx.h"
#include "XtionControl.h"

XtionControl::XtionControl(void)
{
	this->FPS_Color = 0;
	this->FPS_Depth = 0;
	this->FPS_SkeletonTracking = 0;
	this->Flag_ColorBufferRenew = false;
	this->Flag_ColorBufferRenew2 = false;
	this->Flag_DepthBufferRenew = false;
	this->Flag_SkeletonDataRenew = false;

	this->eResult = XN_STATUS_OK;
	this->ColorBuffer = new unsigned char[640*480*3];
	this->IsInitial = false;
}

XtionControl::~XtionControl(void)
{

}

void XN_CALLBACK_TYPE NewUser(xn::UserGenerator& generator, XnUserID user, void* pCookie)
{
	cout << "New user identified: " << user << endl;
	generator.GetSkeletonCap().RequestCalibration( user, true );
}
void XN_CALLBACK_TYPE LostUser( xn::UserGenerator& generator,
	XnUserID user,
	void* pCookie )
{
	cout << "User " << user << " lost" << endl;
}
void XN_CALLBACK_TYPE CalibrationStart( xn::SkeletonCapability& skeleton,
	XnUserID user,
	void* pCookie )
{
	cout << "Calibration start for user " <<  user << endl;
}
void XN_CALLBACK_TYPE CalibrationEnd( xn::SkeletonCapability& skeleton,
	XnUserID user,
	XnCalibrationStatus eStatus,
	void* pCookie )
{
	cout << "Calibration complete for user " <<  user << ", ";
	if( eStatus == XN_CALIBRATION_STATUS_OK )
	{
		cout << "Success" << endl;
		skeleton.StartTracking( user );
	}
	else
	{
		cout << "Failure" << endl;
		skeleton.RequestCalibration( user, true );
	}
}
// void XN_CALLBACK_TYPE CalibrationEnd( xn::SkeletonCapability& skeleton,
// 	XnUserID user,
// 	XnBool bSuccess,
// 	void* pCookie )
// {
// 	cout << "Calibration complete for user " <<  user << ", ";
// 	if( bSuccess )
// 	{
// 		cout << "Success" << endl;
// 		skeleton.StartTracking( user );
// 	}
// 	else
// 	{
// 		cout << "Failure" << endl;
// 		((xn::UserGenerator*)pCookie)->GetPoseDetectionCap().StartPoseDetection( "Psi", user );
// 	}
// }
void XN_CALLBACK_TYPE PoseDetected( xn::PoseDetectionCapability& poseDetection,
	const XnChar* strPose,
	XnUserID user,
	void* pCookie)
{
	cout << "Pose " << strPose << " detected for user " <<  user << endl;
	((xn::UserGenerator*)pCookie)->GetSkeletonCap().RequestCalibration( user, FALSE );
	poseDetection.StopPoseDetection( user );
}

void XtionControl::Xtion_Init()
{
	//initial context----------------------------------------------------------------------------
	eResult = mContext.Init();
	if( eResult != XN_STATUS_OK )
		cout << "[Initialize Context Error]: " << xnGetStatusString( eResult ) << endl;

	// create image generator---------------------------------------------------------------------
	eResult = mImageGenerator.Create( mContext );
	if( eResult != XN_STATUS_OK )
		cout << "[Create Image Generator Error]: " << xnGetStatusString( eResult ) << endl;
	else
		cout << "[Creat Image Generator Success]" << endl;

	//set map mode
	XnMapOutputMode mapMode_Image;
	mapMode_Image.nXRes = 640;
	mapMode_Image.nYRes = 480;
	mapMode_Image.nFPS = 30;
	eResult = mImageGenerator.SetMapOutputMode( mapMode_Image );

	// create depth generator---------------------------------------------------------------------
	eResult = mDepthGenerator.Create( mContext );
	if( eResult != XN_STATUS_OK )
		cout << "[Create Depth Generator Error]: " << xnGetStatusString( eResult ) << endl;
	else
		cout << "[Creat Depth Generator Success]" << endl;

	//set map mode
	XnMapOutputMode mapMode_Depth;
	mapMode_Depth.nXRes = 320;
	mapMode_Depth.nYRes = 240;
	mapMode_Depth.nFPS = 30;
	eResult = mDepthGenerator.SetMapOutputMode( mapMode_Depth );
	
	// create User generator(For skeleton)---------------------------------------------------------------------
	eResult = mUserGenerator.Create( mContext );
	XnCallbackHandle hUserCB;
	mUserGenerator.RegisterUserCallbacks( NewUser, NULL, NULL, hUserCB );

	// 	XnCallbackHandle hPoseCB;
	// 	mUserGenerator.GetPoseDetectionCap().RegisterToPoseCallbacks( PoseDetected, NULL,
	// 		&mUserGenerator, hPoseCB );
	//
	// correct view port
	mDepthGenerator.GetAlternativeViewPointCap().SetViewPoint( mImageGenerator );
	//--------------------------------------------------------------------------------------------
	this->m_hNextColorFrameEvent =	CreateEvent( NULL, TRUE, FALSE, NULL );
	this->m_hNextDepthFrameEvent =	CreateEvent( NULL, TRUE, FALSE, NULL );
	this->m_hNextSkeletonEvent =	CreateEvent( NULL, TRUE, FALSE, NULL );

	// tart generate data
	eResult = mContext.StartGeneratingAll();
	// Start the processing thread
	m_hEvXtionProcessStop = CreateEvent( NULL, FALSE, FALSE, NULL );
	m_hThXtionProcess = CreateThread( NULL, 0, Xtion_ProcessThread, this, 0, NULL );
}

void XtionControl::Xtion_UnInit()
{
	mContext.StopGeneratingAll();
	mContext.Shutdown();
}

DWORD WINAPI XtionControl::Xtion_ProcessThread( LPVOID pParam )
{
	XtionControl *pthis = (XtionControl *) pParam;
	return pthis->Xtion_ProcessThread();
}

DWORD WINAPI XtionControl::Xtion_ProcessThread()
{
	const int numEvents = 4;
	HANDLE hEvents[numEvents] = { this->m_hEvXtionProcessStop, this->m_hNextDepthFrameEvent, this->m_hNextColorFrameEvent,  this->m_hNextSkeletonEvent };
	int    nEventIdx;
	DWORD  t;
	//-------------------------------------------------------------------------------
	this->m_LastDepthFPStime = clock();
	this->m_DepthFramesTotal = 0;
	this->m_ColorFramesTotal = 0;
	//-------------------------------------------------------------------------------
	// Main thread loop
	System::Console::WriteLine("[Xtion ProcessThread Loop Start]");
	bool continueProcessing = true;

	//Register callback functions of skeleton capability
	xn::SkeletonCapability mSC = mUserGenerator.GetSkeletonCap();
	mSC.SetSkeletonProfile( XN_SKEL_PROFILE_ALL );
	XnCallbackHandle hCalibCB;
	mSC.RegisterToCalibrationComplete( CalibrationEnd, &mUserGenerator, hCalibCB );
	//mSC.RegisterCalibrationCallbacks( CalibrationStart, CalibrationEnd,&mUserGenerator, hCalibCB );  


	while ( continueProcessing )
	{
		// read data
		eResult = mContext.WaitNoneUpdateAll();
		//---------------------------------------------------------------------------
		this->Xtion_GotColorAlert();
		this->Xtion_GotDepthAlert();
		this->Xtion_GotSkeletonAlert(mSC);
		//---------------------------------------------------------------------------
		// Once per second, display the depth FPS
		t = clock( );
		if ( (t - this->m_LastDepthFPStime) > 1000 )
		{	
			this->FPS_Color = this->m_ColorFramesTotal;
			this->FPS_Depth = this->m_DepthFramesTotal;
			this->FPS_SkeletonTracking = this->m_SkeletonTrackingFramesTotal;

			this->m_DepthFramesTotal = 0;
			this->m_ColorFramesTotal = 0;
			this->m_SkeletonTrackingFramesTotal = 0;

			this->m_LastDepthFPStime = t;
		}
	}

	return 0;
}

void XtionControl::Xtion_GotColorAlert()
{
	if( eResult == XN_STATUS_OK )
	{
		xn::ImageMetaData xColorData;
		mImageGenerator.GetMetaData( xColorData );

		// 原本得到的資料是RGB的順序因此經由下面方法將他轉為BGR的順序然後存進ColorBuffer中
		cv::Mat cColorImg( xColorData.FullYRes(), xColorData.FullXRes(), CV_8UC3, (void*)xColorData.Data() );
		cv::Mat cBGRImg;
		cv::cvtColor( cColorImg, cBGRImg, CV_RGB2BGR );
		for (int i = 0 ; i < 480 ; i++)
		{
			for (int j = 0 ; j < 640 ; j++)
			{
				int tmpIdx = (i*640 + j)*3;
				this->ColorBuffer[tmpIdx] = cBGRImg.at<cv::Vec3b>(i,j)[0];
				this->ColorBuffer[tmpIdx+1] = cBGRImg.at<cv::Vec3b>(i,j)[1];
				this->ColorBuffer[tmpIdx+2] = cBGRImg.at<cv::Vec3b>(i,j)[2];
			}
		}
		this->IsInitial = true;
	}
	else
		this->IsInitial = false;
}

void XtionControl::Xtion_GotDepthAlert()
{
	if( eResult == XN_STATUS_OK )
	{
		xn::DepthMetaData xDepthData;
		mDepthGenerator.GetMetaData( xDepthData );

		cv::Mat cDepthImg( xDepthData.FullYRes(), xDepthData.FullXRes(), CV_16UC1, (void*)xDepthData.Data() );
		for (int idxH = 0 ; idxH < 240 ; idxH++) for (int idxW = 0 ; idxW < 320 ; idxW++)	
		{
			this->DepthData[idxW][idxH] = cDepthImg.at<short>(idxH,idxW);
		}

		this->Flag_DepthBufferRenew = true;
	}
	else
		this->Flag_DepthBufferRenew = false;
}

void XtionControl::Xtion_GotSkeletonAlert(xn::SkeletonCapability mSC)
{

	nUsers = mUserGenerator.GetNumberOfUsers();
	if( nUsers > 0 )
	{
		//get users 
		aUserID = new XnUserID[nUsers];
		mUserGenerator.GetUsers( aUserID, nUsers );//aUserID = 1 5 6 ; uUsers = 3
		// check each user
		for( int i = 0; i < nUsers; ++i )
		{
			// if is tracking skeleton
			if( mSC.IsTracking( aUserID[i] ) )
			{
				//更新USER骨架是否有被追蹤到
				SkeletonData[aUserID[i]].eTrackingState = NUI_SKELETON_TRACKED;
				SkeletonData[aUserID[i]].dwTrackingID = aUserID[i];

				// get skeleton joint data
				for (int part =0;part<TOTAL_SKELETON_NUM;part++)
				{
					mSC.GetSkeletonJoint( aUserID[i], (XnSkeletonJoint)(XN_SKEL_HEAD + part), mJointTran );
					SkeletonData[aUserID[i]].SkeletonPositions[1+part].x = (FLOAT)mJointTran.position.position.X;
					SkeletonData[aUserID[i]].SkeletonPositions[1+part].y = (FLOAT)mJointTran.position.position.Y;
					SkeletonData[aUserID[i]].SkeletonPositions[1+part].z = (FLOAT)mJointTran.position.position.Z;
				}
				//     mSC.GetSkeletonJoint( aUserID[i], XN_SKEL_HEAD, mJointTran );

				// output information
				static int counter=0;
				if(counter++%50==0)
				{
					cout << "The head of user " << aUserID[i] << " is at (";
					cout << mJointTran.position.position.X << ", ";
					cout << mJointTran.position.position.Y << ", ";
					cout << mJointTran.position.position.Z << ")" << endl;
					if(counter>10000)
						counter=0;
				}
			}
			else
			{
				//更新USER骨架是否有被追蹤到
				SkeletonData[aUserID[i]].eTrackingState = NUI_SKELETON_NOT_TRACKED;
			}
		}
		delete [] aUserID;
	}
	//如果都沒有使用者 則標記 NOT_TRACKING 然後就不會在深度圖畫出
	else
	{
		for(int i = 1;i<=5;i++)
		{
			SkeletonData[i].eTrackingState =  NUI_SKELETON_NOT_TRACKED;
		}
	}
}