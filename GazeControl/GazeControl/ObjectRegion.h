#include "stdafx.h"

//this files contains all of variable in this project

#if !defined( OBJECTREGION_H ) 
#define OBJECTREGION_H

//放入 extern 等原本在header裡面的資料，避免重複宣告 

class ObjectRegion
{
public:
	int leftBoundary;
	int rightBoundary;
	int topBoundary;
	int bottomBoundary;

	int pixelNumbers;

	cv::Point2d mainPoint;
	cv::Point2d leftPoint;
	cv::Point2d rightPoint;
	cv::Point3d robotCoordinate;
	cv::Point3d robotCoordinate_add;
	cv::Point3d robotCoordinate_sub;

	double dis;
	double panAngle;


	cv::Mat markedImage; //Map

	ObjectRegion()
	{
// 		this->markedImage = new bool *[info->vision.camHeight];
// 		for (int i=0 ;i<info->vision.camHeight ;i++)
// 			this->markedImage[i] = new bool [info->vision.camWidth];
		
		this->markedImage = cv::Mat::zeros( 240,320,CV_8U );
		this->initial();
	}

	~ObjectRegion()
	{
		this->markedImage.release();
	}

	void initial();
	void transformImage2RobotCoordinate();
	void transformImage2RobotCoordinate_C905();
	void transformImage2RobotCoordinate_David2();
	void transformImage2RobotCoordinate_teensize();
	void calcDisAndAngle();
	void setBottomCenter2MainPoint();
	void setCenter2MainPoint();
	void setLeftCenter2MainPoint();
	void setRightCenter2MainPoint();
	void setTopCenter2MainPoint();
	void setBottomRightLeftPoint();
	//void deleteMarkedImage();
};

class RegionOfInterest
{
public:
	int left;
	int right;
	int top;
	int bottom;

	RegionOfInterest()
	{
		this->initial();
	}

	~RegionOfInterest()
	{

	}

	void initial();
	void setRegion( int left ,int right ,int top ,int bottom ,double ratio=1 );
};


#endif