#include "stdafx.h"

#if !defined( XTIONCONTROL_H ) 
#define XTIONCONTROL_H

using namespace std;
#define NUI_SKELETON_COUNT 6
#define TOTAL_SKELETON_NUM 24

#ifndef _Vector4_
#define _Vector4_
typedef struct _Vector4
{
	FLOAT x;
	FLOAT y;
	FLOAT z;
	FLOAT w;
} 	Vector4;

#endif _Vector4_

#ifndef _NUI_SKELETON_TRACKING_STATE_
#define _NUI_SKELETON_TRACKING_STATE_
typedef 
	enum _NUI_SKELETON_TRACKING_STATE
{	NUI_SKELETON_NOT_TRACKED	= 0,
NUI_SKELETON_POSITION_ONLY	= ( NUI_SKELETON_NOT_TRACKED + 1 ) ,
NUI_SKELETON_TRACKED	= ( NUI_SKELETON_POSITION_ONLY + 1 ) 
} 	NUI_SKELETON_TRACKING_STATE;

#endif _NUI_SKELETON_TRACKING_STATE_

#ifndef _NUI_SKELETON_DATA_
#define _NUI_SKELETON_DATA_
typedef struct _NUI_SKELETON_DATA
{
	NUI_SKELETON_TRACKING_STATE eTrackingState;
	DWORD dwTrackingID;
	DWORD dwEnrollmentIndex;
	DWORD dwUserIndex;
	Vector4 Position;
	Vector4 SkeletonPositions[ 25 ];
	//NUI_SKELETON_POSITION_TRACKING_STATE eSkeletonPositionTrackingState[ 20 ];
	//DWORD dwQualityFlags;
} 	NUI_SKELETON_DATA;

#endif _NUI_SKELETON_TRACKING_STATE_

class XtionControl
{
public:	
	XtionControl(void);
	~XtionControl(void);

	void					Xtion_Init();
	void					Xtion_UnInit();
	bool					IsInitial;
	XnUInt16                nUsers;
	XnUserID*               aUserID;
	int						FPS_Color;
	int						FPS_Depth;
	int						FPS_SkeletonTracking;

	unsigned char*			ColorBuffer;
	short					DepthData[320][240];

	bool					Flag_ColorBufferRenew;
	bool					Flag_ColorBufferRenew2;
	bool					Flag_DepthBufferRenew;
	bool					Flag_SkeletonDataRenew;
	xn::DepthGenerator		mDepthGenerator;
	
	//骨架資訊(給程式撰寫者使用)
	NUI_SKELETON_DATA       SkeletonData[7];   //依使用者編號放入 EX: SkeletonData[1~6]  ，SkeletonData[0]沒用到

private:
	XnStatus				eResult;
	xn::Context				mContext;
	xn::ImageGenerator		mImageGenerator;

	xn::UserGenerator       mUserGenerator;
	XnSkeletonJointTransformation mJointTran;

	// thread handling -------------------------------------------------------
	HANDLE					m_hNextDepthFrameEvent;
	HANDLE					m_hNextColorFrameEvent;
	HANDLE					m_hNextSkeletonEvent;
	HANDLE					m_pDepthStreamHandle;
	HANDLE					m_pVideoStreamHandle;

	HANDLE					m_hThXtionProcess;
	HANDLE					m_hEvXtionProcessStop;

	static DWORD WINAPI     Xtion_ProcessThread(LPVOID pParam);
	DWORD WINAPI            Xtion_ProcessThread();
	//------------------------------------------------------------------------
	DWORD					m_LastDepthFPStime;
	DWORD					m_LastDepthFramesTotal;
	int						m_DepthFramesTotal;
	int						m_ColorFramesTotal;
	int						m_SkeletonTrackingFramesTotal;
	//------------------------------------------------------------------------
	void                    Xtion_GotColorAlert( );
	void                    Xtion_GotDepthAlert( );
	void                    Xtion_GotSkeletonAlert(xn::SkeletonCapability mSC);


};
#endif