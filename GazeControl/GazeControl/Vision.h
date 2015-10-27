#include "stdafx.h"

//this files contains 

#if !defined( VISION_H ) 
#define VISION_H 

//放入 extern 等原本在header裡面的資料，避免重複宣告 

typedef struct  
{
	unsigned char point;
	unsigned char min;
	unsigned char max;
}SingleColorRange;

typedef struct  
{
	SingleColorRange color1;
	SingleColorRange color2;
	SingleColorRange color3;
}ObjectColorRange;

class ObjectColorLUT
{
public:
	unsigned char color1[256];
	unsigned char color2[256];
	unsigned char color3[256];

	ObjectColorLUT()
	{
		for ( int i=0 ;i<256 ;i++ )
		{
			this->color1[i] = 0;
			this->color2[i] = 0;
			this->color3[i] = 0;
		}
	}
};

class Vision
{
public:

	bool psoMapDone;
	ObjectColorRange hsvObjRange[8];
	ObjectColorLUT hsvObjLUT;
	videoInput *VI;
	int camID;
	int camWidth,camHeight;
	IplImage* camFrame;	//RGB frame

	int errodenumbers;
	int dilatenumbers;
	//face eye detection
	IplImage *eyefram;
	bool initialEyeRegion;
	bool isfindEye;
	bool isInitialHSVfram;//convert to hsv just need to initial only once
	bool isInitialGrayfram;//convert to gray just need to initial only once
	int faceregionX;
	int faceregionY;
	int faceregionWidth;
	int faceregionHeight;

	int eyeRegionX;
	int eyeRegionY;
	int eyeRegionWidth;
	int eyeRegionHeight;

	//eye region parameters
	int eyeleftboundary;
	int eyerightboundary;
	int eyetopboundary;
	int eyebottomboundary;
	int eyemaintX;
	int eyemaintY;

	int eyeMoveVectorX;
	int eyeMoveVectorY;
	double eyeMoveVectorLength;
	double eyeMoveAngX;

	int eyeGrayTH;
	//rectify and mapping
	IplImage* camFrame_HSV;	 //HSV frame
	IplImage* camFrame_Gray; //Gray frame

	//object image
	unsigned char objectIndex,colorIndex;
	cv::Mat isPixelSearched;


	//Constructor
	Vision(void)
	{
		//face eye detection
		this->initialEyeRegion = false;
		this->isfindEye = false;
		this->isInitialHSVfram = false;
		this->isInitialGrayfram = false;
		this->faceregionX = 90;
		this->faceregionY = 5;
		this->faceregionHeight = 200;
		this->faceregionWidth = 200;

		this->eyeRegionWidth = 100;
		this->eyeRegionHeight = 100;
		this->eyeGrayTH = 35;

		this->errodenumbers = 1;
		this->dilatenumbers = 2.5;

		this->eyemaintX = 0;
		this->eyemaintY = 0;

		this->eyeMoveVectorX = 0;
		this->eyeMoveVectorY = 0;

		this->objectIndex = 0;
		this->colorIndex = 0;

		//camera setting
		this->camID = 0;
		this->camWidth = 320 ,this->camHeight = 240;

		//Harris corner
		int thresh = 200;
		int max_thresh = 255;
		char* source_window = "Source image";
		char* corners_window = "Corners detected";
		

	}


	/*----------------------------------------general function----------------------------------------*/

	void initial();
	void run(unsigned short objIndex);
	bool findObject(unsigned char objIndex);	//1 parameter
	bool findObject(unsigned char objIndex ,int minPixelNumbers);	//2 parameters
	bool findObject(unsigned char objIndex ,int minPixelNumbers ,bool isMulti);		//3 parameters
	bool findObject(unsigned char objIndex ,int minPixelNumbers ,RegionOfInterest ROI ,bool isMulti);	//4 parameters
	void searchAround(int i ,int j ,unsigned short colorIndex ,ObjectRegion *objRegion);
	void searchCorner(int i, int j ,unsigned short colorIndex );

	/*----------------------------------------unique function----------------------------------------*/

	//Gaze Control
	bool findpupil();

	//Sprint & Weightlifting
	bool findAuxiliary();	//four colors
	bool findAuxiliary_sprint();
	bool findAuxiliary_sprint_line(); 
	
	//Tool
	void rotateImage(IplImage* img, IplImage *img_rotate,int degree ,int wid , int high);
	void save_eyeRegion(IplImage* img, int x, int y, int width, int height) ;
	void detectEyes(IplImage *img);
	void convertEyeRegionRGBtoHSV( IplImage *camFrameToConvert );
	void settGrayEyeRegion( IplImage *camFrameToConvert );
	void HoughCircle( IplImage *camFrameToConvert );
};



#endif