// stdafx.cpp : 僅包含標準 Include 檔的原始程式檔
// Standard Form.pch 會成為先行編譯標頭檔
// stdafx.obj 會包含先行編譯型別資訊
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "stdafx.h"



void Vision::initial()
{

	this->VI = new videoInput();

	//open the camera
	this->VI->setupDevice(this->camID ,CAM_WIDTH ,CAM_HEIGHT);   //for 320*240
	//this->VI->setupDevice(this->camID ,CAM_HEIGHT ,CAM_WIDTH); //for 640*480

	//malloc image matrix
	this->camFrame = cvCreateImage(cvSize(CAM_WIDTH ,CAM_HEIGHT) ,IPL_DEPTH_8U ,3);
	//this->eyefram = cvCreateImage(cvSize(CAM_WIDTH ,CAM_HEIGHT) ,IPL_DEPTH_8U ,3);
	//this->camFrame_HSV = cvCreateImage(cvSize(CAM_WIDTH ,CAM_HEIGHT) ,IPL_DEPTH_8U ,3);

	//set the pixels to zero
	this->isPixelSearched = cv::Mat::zeros(CAM_HEIGHT ,CAM_WIDTH ,CV_8UC1);
}

void Vision::run( unsigned short objIndex )
{ 
	switch ( info->eventIndex )
	{
		case GAZECONTROL_EVENT::GAZECONTROl: this->findpupil();		 break;
		case GAZECONTROL_EVENT::FOLLOW:		 this->findAuxiliary();  break;
		default:
			printf( "\nPlease check the dip.\nThere is no object in vision\n" );
			break;
	}
}

/*---------------Gaze Control-----------------*/
bool Vision::findpupil()
{ 
  //detect eyes in the image  
	if ( this->findObject(OBJECT::GAZECONTROL::G_PUPIL,10) )
	{
		std::vector<ObjectRegion>::iterator pupil = info->objectRegion[OBJECT::GAZECONTROL::G_PUPIL].begin();

		RegionOfInterest ROI;
		ROI.setRegion( pupil->leftBoundary ,pupil->rightBoundary ,pupil->topBoundary ,pupil->bottomBoundary );

		if( !this->findObject(OBJECT::GAZECONTROL::G_PUPIL,10,ROI,false) )
			return false;//若還是沒找到就RETURN
		return true;
	}
	return false;
// 	//如果上次有找到，先找LOCAL
// 	if ( !info->objectRegion[OBJECT::GAZECONTROL::G_PUPIL].empty() )
// 	{
// 		std::vector<ObjectRegion>::iterator pupil = info->objectRegion[OBJECT::GAZECONTROL::G_PUPIL].begin();
// 	
// 		RegionOfInterest ROI;
// 		ROI.setRegion( pupil->leftBoundary ,pupil->rightBoundary ,pupil->topBoundary ,pupil->bottomBoundary );
// 	
// 		if( !this->findObject(OBJECT::GAZECONTROL::G_PUPIL,500,ROI,false) )
// 			if( !this->findObject(OBJECT::GAZECONTROL::G_PUPIL,500,true) )		//沒找到再找GLOBAL
// 				return false;//若還是沒找到就RETURN
// 	}
// 	else
// 	{
// 		if( !this->findObject(OBJECT::GAZECONTROL::G_PUPIL,500,true) )//上次根本就沒找到，直接找GLOBAL
// 			return false;//若還是沒找到就RETURN
// 	}
// 	
// 	//有可能有找到，檢查中間輔助物
// 	std::vector<ObjectRegion>::iterator pupil = info->objectRegion[OBJECT::GAZECONTROL::G_PUPIL].begin();
// 	for( ;pupil != info->objectRegion[OBJECT::GAZECONTROL::G_PUPIL].end() ;++pupil )
// 	{
// 		RegionOfInterest ROI;
// 		ROI.setRegion( (*pupil).leftBoundary  ,(*pupil).rightBoundary ,(*pupil).topBoundary ,(*pupil).bottomBoundary ,0.6 );
// 		
// 		if ( this->findObject( OBJECT::GAZECONTROL::G_WHITE ,100 ,ROI ,true ) )//找眼白區域
// 		{
// 			ROI.setRegion( pupil->leftBoundary ,pupil->rightBoundary ,pupil->topBoundary ,pupil->bottomBoundary ,0.5);//eye white region
// 			
// 			if ( this->findObject( OBJECT::GAZECONTROL::G_SKIN ,500 ,ROI ,false ) )//找皮膚
// 			{
// 				std::vector<ObjectRegion>::iterator eyelip = info->objectRegion[OBJECT::GAZECONTROL::G_SKIN].begin();
// 				ROI.setRegion( eyelip->leftBoundary ,eyelip->rightBoundary ,eyelip->topBoundary ,eyelip->bottomBoundary ,0.5 );
// 	
// 				if ( this->findObject( OBJECT::GAZECONTROL::G_SKIN ,100 ,ROI ,false ) )//找到右邊中間輔助物
// 				{
// 					//clear all the other "pupil"s, except the main one
// 					ObjectRegion tempRegion = (*pupil);
// 					info->objectRegion[OBJECT::GAZECONTROL::G_PUPIL].clear();
// 					info->objectRegion[OBJECT::GAZECONTROL::G_PUPIL].push_back(tempRegion);
// 					return true;
// 				}
// 			}
// 		}
// 	}
// 	
// 	//最後很可以還是找不到
// 	info->objectRegion[OBJECT::GAZECONTROL::G_PUPIL].clear();
// 	info->objectRegion[OBJECT::GAZECONTROL::G_WHITE].clear();
// 	info->objectRegion[OBJECT::GAZECONTROL::G_SKIN].clear();
// 	return false;
}
/*---------------- Follow---------------------*/
bool Vision::findAuxiliary()
{
	// 	如果上次有找到，先找LOCAL
	// 		if ( !info->objectRegion[OBJECT::AUXILIARY::COLOR1].empty() ){
	// 			std::vector<ObjectRegion>::iterator mainMark = info->objectRegion[OBJECT::AUXILIARY::COLOR1].begin();
	// 	
	// 			RegionOfInterest ROI;
	// 			ROI.setRegion( mainMark->leftBoundary ,mainMark->rightBoundary ,mainMark->topBoundary ,mainMark->bottomBoundary );
	// 	
	// 			if( !this->findObject(OBJECT::AUXILIARY::COLOR1,500,ROI,false) )
	// 				if( !this->findObject(OBJECT::AUXILIARY::COLOR1,500,true) )		//沒找到再找GLOBAL
	// 					return false;//若還是沒找到就RETURN
	// 		}else{
	// 			if( !this->findObject(OBJECT::AUXILIARY::COLOR1,500,true) )//上次根本就沒找到，直接找GLOBAL
	// 				return false;//若還是沒找到就RETURN
	// 		}
	// 	
	// 		//有可能有找到，檢查中間輔助物
	// 		std::vector<ObjectRegion>::iterator mainMark = info->objectRegion[OBJECT::AUXILIARY::COLOR1].begin();
	// 		for( ;mainMark != info->objectRegion[OBJECT::AUXILIARY::COLOR1].end() ;++mainMark )
	// 		{
	// 			RegionOfInterest ROI;
	// 			ROI.setRegion( (*mainMark).leftBoundary  ,(*mainMark).rightBoundary ,(*mainMark).topBoundary ,(*mainMark).bottomBoundary ,0.6 );
	// 	
	// 			if ( this->findObject( OBJECT::AUXILIARY::COLOR2 ,100 ,ROI ,false ) )
	// 			{//找到左邊中間輔助物
	// 	
	// 				int markWidth = mainMark->rightBoundary - mainMark->leftBoundary;
	// 				ROI.setRegion( mainMark->rightBoundary ,mainMark->rightBoundary+markWidth ,mainMark->topBoundary ,mainMark->bottomBoundary );
	// 	
	// 				if ( this->findObject( OBJECT::AUXILIARY::COLOR3 ,500 ,ROI ,false ) )
	// 				{//找到右邊輔助物
	// 	
	// 					std::vector<ObjectRegion>::iterator secondMark = info->objectRegion[OBJECT::AUXILIARY::COLOR3].begin();
	// 					ROI.setRegion( secondMark->leftBoundary ,secondMark->rightBoundary ,secondMark->topBoundary ,secondMark->bottomBoundary ,0.6 );
	// 	
	// 					if ( this->findObject( OBJECT::AUXILIARY::COLOR4 ,100 ,ROI ,false ) )
	// 					{//找到右邊中間輔助物
	// 						//clear all the other "main_mark"s, except the main one
	// 						ObjectRegion tempRegion = (*mainMark);
	// 						info->objectRegion[OBJECT::AUXILIARY::COLOR1].clear();
	// 						info->objectRegion[OBJECT::AUXILIARY::COLOR1].push_back(tempRegion);
	// 	
	// 						return true;
	// 					}
	// 				}
	// 			}
	// 		}
	// 	
	// 		//最後很可以還是找不到
	// 		info->objectRegion[OBJECT::AUXILIARY::COLOR1].clear();
	// 		info->objectRegion[OBJECT::AUXILIARY::COLOR2].clear();
	// 		info->objectRegion[OBJECT::AUXILIARY::COLOR3].clear();
	// 		info->objectRegion[OBJECT::AUXILIARY::COLOR4].clear();
	// 		return false;

	RegionOfInterest ROI;
	ROI.setRegion(0,640,0,480);
	if (this->findObject(OBJECT::AUXILIARY::COLOR1,500,ROI,false))
	{
		std::vector<ObjectRegion>::iterator goal = info->objectRegion[OBJECT::AUXILIARY::COLOR1].begin();

		goal->transformImage2RobotCoordinate();
		goal->calcDisAndAngle();

		return true;

	}
	return false;

}

/*---------------Functions-------------------*/
void Vision::detectEyes(IplImage *img)  
{  
// 	/*allocate storage*/  
// 	CvMemStorage* storage = 0;  
// 	storage = cvCreateMemStorage(0) ;  
// 	/*load face cascade*/  
// 	CvHaarClassifierCascade* cascade_f = 0;  
// 	const char* cascade_name = "haarcascade_frontalface_alt2.xml";  
// 	cascade_f = (CvHaarClassifierCascade*)cvLoad( cascade_name, 0, 0, 0 );  
// 
// 	/* detect faces */  
// 	CvSeq *faces = cvHaarDetectObjects(  
// 		img,            /* the source image */  
// 		cascade_f,      /* the face classifier */  
// 		storage,        /* memory buffer, created with cvMemStorage */  
// 		1.1, 3, 0,      /* special parameters, tune for your app */  
// 		cvSize(100, 100)  /* minimum detection scale */  
// 		);  
// 
// 	/* return if not found */  
// 	if (faces->total == 0) return;  
// 
// 	/* get the first detected face */  
// 	CvRect *face = (CvRect*)cvGetSeqElem(faces, 0);  
// 
// 	/* draw a red rectangle */  
// 	cvRectangle(  
// 		img,  
// 		cvPoint(face->x, face->y),  
// 		cvPoint(  
// 		face->x + face->width,  
// 		face->y + face->height  
// 		),  
// 		CV_RGB(255, 0, 0),  
// 		1, 8, 0  
// 		);  
// 
// 	/* reset buffer for the next object detection */  
// 	cvClearMemStorage(storage);  
// 	//cvRelease((void**)cascade_f);  
// 
// 
// 	/* Set the Region of Interest: estimate the eyes' position */  
// 	cvSetImageROI(  
// 		img,                    /* the source image */  
// 		cvRect(  
// 		face->x,            /* x = start from leftmost */  
// 		face->y + (face->height/5.5), /* y = a few pixels from the top */  
// 		face->width,        /* width = same width with the face */  
// 		face->height/3.0    /* height = 1/3 of face height */  
// 		)  
// 		);  

    /*allocate storage*/  
    CvMemStorage* storage = 0;  
    storage = cvCreateMemStorage(0) ;  

// 	cvSetImageROI(  
// 		img,                    /* the source image */  
// 		cvRect(  
// 			this->faceregionX,            /* x = start from leftmost */  
// 			this->faceregionY + (this->faceregionHeight/5.5), /* y = a few pixels from the top */  
// 			this->faceregionWidth,        /* width = same width with the face */  
// 			this->faceregionHeight/3.0    /* height = 1/3 of face height */  
// 		)  
// 	  ); 
	cvSetImageROI(  
		img,                    /* the source image */  
		cvRect(  
		1,            /* x = start from leftmost */  
		1, /* y = a few pixels from the top */  
		320,        /* width = same width with the face */  
		240    /* height = 1/3 of face height */  
		)  
		); 
    /*load eye cascade*/  
    CvHaarClassifierCascade* cascade_e = 0;  
	//const char* cascade_name2 = "haarcascade_eye.xml";
	const char* cascade_name2 = "haarcascade_eye_tree_eyeglasses.xml"; 
    cascade_e = (CvHaarClassifierCascade*)cvLoad( cascade_name2, 0, 0, 0 );  
    assert(cascade_e != NULL);  
 
    /* detect the eyes */  
    CvSeq *eyes = cvHaarDetectObjects(  
        img,            /* the source image, with the estimated location defined */  
        cascade_e,      /* the eye classifier */  
        storage,        /* memory buffer */  
        1.15, 3, 0,     /* tune for your app */  
        cvSize(30, 20)  /* minimum detection scale */  
    );  

	if ( eyes->total > 0 )//find eyes and record one eye's informotion
	{
		CvRect *eye = (CvRect*)cvGetSeqElem(eyes, 0);
// 		this->eyeRegionX = eye->x+faceregionX;
// 		this->eyeRegionY = eye->y+faceregionY+(this->faceregionHeight/5.5);
// 		this->eyeRegionWidth = eye->width;
// 		this->eyeRegionHeight = eye->height;

		this->eyeRegionX = eye->x+1; //手動給定範圍
		this->eyeRegionY = eye->y+1;
		this->eyeRegionWidth = eye->width;
		this->eyeRegionHeight = eye->height;

		this->isfindEye = true;
	}
	else
	{
		//this->isfindEye = false;
		this->eyeRegionX = 100;
		this->eyeRegionY = 100;
		this->eyeRegionWidth = 100;
		this->eyeRegionHeight = 100;
	}
		

    /* draw a rectangle for each detected eye */  
    for( int i = 0; i < (eyes ? eyes->total : 0); i++ )
	{  
        /* get one eye */  
        CvRect *eye = (CvRect*)cvGetSeqElem(eyes, i);  
        /* draw a red rectangle */  
        cvRectangle(img,cvPoint(eye->x, eye->y),cvPoint(eye->x + eye->width, eye->y + eye->height),CV_RGB(255, 0, 0),1,8,0);
    }  

   /* reset region of interest */  
        cvResetImageROI(img);  
}
// void Vision::detectEyes(IplImage *img)  
// {  
// 	/*allocate storage*/  
// 	CvMemStorage* storage = 0;  
// 	storage = cvCreateMemStorage(0) ;  
// 	/*load face cascade*/  
// 	CvHaarClassifierCascade* cascade_f = 0;  
// 	const char* cascade_name = "haarcascade_frontalface_alt2.xml";  
// 	cascade_f = (CvHaarClassifierCascade*)cvLoad( cascade_name, 0, 0, 0 );  
// 
// 	/* detect faces */  
// 	CvSeq *faces = cvHaarDetectObjects(  
// 		img,            /* the source image */  
// 		cascade_f,      /* the face classifier */  
// 		storage,        /* memory buffer, created with cvMemStorage */  
// 		1.1, 3, 0,      /* special parameters, tune for your app */  
// 		cvSize(100, 100)  /* minimum detection scale */  
// 		);  
// 
// 	/* return if not found */  
// 	if (faces->total == 0) return;  
// 
// 	/* get the first detected face */  
// 	CvRect *face = (CvRect*)cvGetSeqElem(faces, 0);  
// 
// 	/* draw a red rectangle */  
// 	cvRectangle(  
// 		img,  
// 		cvPoint(face->x, face->y),  
// 		cvPoint(  
// 		face->x + face->width,  
// 		face->y + face->height  
// 		),  
// 		CV_RGB(255, 0, 0),  
// 		1, 8, 0  
// 		);  
// 
// 	/* reset buffer for the next object detection */  
// 	cvClearMemStorage(storage);  
// 
// 	/* Set the Region of Interest: estimate the eyes' position */  
// 	cvSetImageROI(  
// 		img,                    /* the source image */  
// 		cvRect(  
// 		face->x,            /* x = start from leftmost */  
// 		face->y + (face->height/5.5), /* y = a few pixels from the top */  
// 		face->width,        /* width = same width with the face */  
// 		face->height/3.0    /* height = 1/3 of face height */  
// 		)  
// 		);  
// 
// 	/*load eye cascade*/  
// 	CvHaarClassifierCascade* cascade_e = 0;  
// 	const char* cascade_name2 = "haarcascade_eye.xml"; 
// 	cascade_e = (CvHaarClassifierCascade*)cvLoad( cascade_name2, 0, 0, 0 );  
// 	assert(cascade_e != NULL);  
// 
// 	/* detect the eyes */  
// 	CvSeq *eyes = cvHaarDetectObjects(  
// 		img,            /* the source image, with the estimated location defined */  
// 		cascade_e,      /* the eye classifier */  
// 		storage,        /* memory buffer */  
// 		1.15, 3, 0,     /* tune for your app */  
// 		cvSize(25, 15)  /* minimum detection scale */  
// 		);  
// 
// 	int i;  
// 
// 	/* draw a rectangle for each detected eye */  
// 	for( i = 0; i < (eyes ? eyes->total : 0); i++ ) {  
// 		/* get one eye */  
// 		CvRect *eye = (CvRect*)cvGetSeqElem(eyes, i);  
// 
// 		/* draw a red rectangle */  
// 		cvRectangle(  
// 			img,  
// 			cvPoint(eye->x, eye->y),  
// 			cvPoint(eye->x + eye->width, eye->y + eye->height),  
// 			CV_RGB(255, 0, 0),  
// 			1, 8, 0  
// 			);  
// 	}  
// 
// 	/* reset region of interest */  
// 	cvResetImageROI(img);  
// }

void Vision::save_eyeRegion(IplImage* img, int x, int y, int width, int height)  
{  
	try
	{
		if ( x > 320 || x < 0 || y > 240 || y < 0 ||  width*height == 0)
		{
			return;
		}
		assert(img!=NULL);  
		CvRect ROI = cvRect(x,y,width,height);

		//cvSetImageCOI( img, 0);
		cvSetImageROI( img, ROI );  

		CvSize dst_cvsize;    //目標圖像尺寸  
		dst_cvsize.width = width;    
		dst_cvsize.height = height;   
		this->eyefram = cvCreateImage( dst_cvsize, img->depth, img->nChannels);  //構造目標圖像  
		cvResize(img, this->eyefram, CV_INTER_LINEAR);  //縮放源圖像到目標圖像 
		 
	}

	catch ( ... )
	{
		return;
	}
}

void Vision::convertEyeRegionRGBtoHSV( IplImage *camFrameToConvert )
{
	
	if ( !this->isInitialHSVfram )
	{
		this->camFrame_HSV = cvCreateImage(cvSize(camFrameToConvert->width ,camFrameToConvert->height) ,IPL_DEPTH_8U ,3);
		this->isInitialHSVfram = true;
	}

	//RGB -> HSV
	cvCvtColor( camFrameToConvert, this->camFrame_HSV, CV_BGR2HSV_FULL );
}

void Vision::settGrayEyeRegion( IplImage *camFrameToConvert )
{

	if ( !this->isInitialGrayfram )
	{
		this->camFrame_Gray = cvCreateImage(cvSize(camFrameToConvert->width ,camFrameToConvert->height) ,IPL_DEPTH_8U ,1);
		this->isInitialGrayfram = true;
	}

	int gray;
	int eyepoints = 0;
	this->eyemaintX = 0;
	this->eyemaintY = 0;

	//RBG to Gray and add threshold 35
	for ( int j=0 ; j<camFrameToConvert->height ; j++)
	{
		for ( int i=0 ; i<camFrameToConvert->width ; i++)
		{
			gray = (camFrameToConvert->imageData[(j*camFrameToConvert->width+i)*3]+camFrameToConvert->imageData[(j*camFrameToConvert->width+i)*3+1]+camFrameToConvert->imageData[(j*camFrameToConvert->width+i)*3+2])/3;

			if ( gray <= info->vision.eyeGrayTH )
			{
				camFrameToConvert->imageData[(j*camFrameToConvert->width+i)*3] = (unsigned char)255;
				camFrameToConvert->imageData[(j*camFrameToConvert->width+i)*3+1] = (unsigned char)255;
				camFrameToConvert->imageData[(j*camFrameToConvert->width+i)*3+2] = (unsigned char)255;

// 				this->eyemaintX +=i;
// 				this->eyemaintY +=j;
// 				eyepoints++;

			}
			else
			{
				camFrameToConvert->imageData[(j*camFrameToConvert->width+i)*3] = (unsigned char)0;
				camFrameToConvert->imageData[(j*camFrameToConvert->width+i)*3+1] = (unsigned char)0;
				camFrameToConvert->imageData[(j*camFrameToConvert->width+i)*3+2] = (unsigned char)0;
			}

		}
	}

	cvErode( camFrameToConvert, camFrameToConvert, NULL, this->errodenumbers );
	cvDilate(camFrameToConvert, camFrameToConvert, NULL, this->dilatenumbers );

	for ( int j=0 ; j<camFrameToConvert->height ; j++)
	{
		for ( int i=0 ; i<camFrameToConvert->width ; i++)
		{
			int eyepoint = (camFrameToConvert->imageData[(j*camFrameToConvert->width+i)*3]+camFrameToConvert->imageData[(j*camFrameToConvert->width+i)*3+1]+camFrameToConvert->imageData[(j*camFrameToConvert->width+i)*3+2])/3;

			if ( eyepoint == 255 )
			{
				this->eyemaintX +=i;
				this->eyemaintY +=j;
				eyepoints++;
			}

		}
	}

	this->eyemaintX = this->eyemaintX/eyepoints;
	this->eyemaintY = this->eyemaintY/eyepoints;
	//printf("\nX = %d,Y = %d\n",this->eyemaintX,this->eyemaintY );

}

void Vision::HoughCircle( IplImage *camFrameToConvert )
{
	IplImage *dst;
	bool dstInitial = false;
	if ( !dstInitial )
	{
		dst = cvCreateImage(cvSize(camFrameToConvert->width ,camFrameToConvert->height) ,IPL_DEPTH_8U ,1);
		dstInitial = false;
	}
	cvSmooth(camFrameToConvert, camFrameToConvert, CV_GAUSSIAN, 5, 5);

	CvMemStorage *storage = cvCreateMemStorage(0);
	CvSeq* results = cvHoughCircles(camFrameToConvert, storage, CV_HOUGH_GRADIENT, 1, camFrameToConvert->width/10);
	//因為需要計算像素梯度的方向，所以來源影像最好是灰階影像，二值化影像較難判斷
	//"2"表示累加器圖像的分辨率，不能小於1
	//"src->width/10"表示兩個圓之間的最小距離

	if ( results->total >0 )
	{
		for(int i = 0; i < results->total; i++)
		{
			float* p = (float*)cvGetSeqElem( results, i);//將序列中的值取出
			CvPoint pt = cvPoint( cvRound(p[0]), cvRound(p[1]));
			cvCircle( dst, pt, p[2], CV_RGB(0,0,0));
			//cvCircle(來源影像, 圓心座標, 圓的半徑, 顏色)
		}

		cvShowImage("Destination", dst);
		cvWaitKey(0);
		cvReleaseImage(&dst);
	}
	else
	{
		printf("\nno circle!!!!\n");
	}


}

bool Vision::findObject( unsigned char objIndex )	// 1 parameter
{
	return findObject( objIndex ,1000 );
}
bool Vision::findObject( unsigned char objIndex ,int minPixelNumbers )	// 2 parameters
{
	return findObject( objIndex ,minPixelNumbers ,false );
}
bool Vision::findObject( unsigned char objIndex ,int minPixelNumbers ,bool isMulti )	//3 parameters
{
	if ( info->objectRegion[objIndex].empty() || isMulti )	//若之前沒找到或要找好幾個，就要搜尋整張影像
	{	//search global
		RegionOfInterest ROI;
		ROI.setRegion(0 ,CAM_WIDTH-1 ,0 ,CAM_HEIGHT-1);

		if ( this->findObject(objIndex ,minPixelNumbers ,ROI ,isMulti) )
			return true;
	}
	else	
	{	//search local
		RegionOfInterest ROI;
		ROI.left = info->objectRegion[objIndex][0].leftBoundary;
		ROI.right = info->objectRegion[objIndex][0].rightBoundary;
		ROI.top = info->objectRegion[objIndex][0].topBoundary;
		ROI.bottom = info->objectRegion[objIndex][0].bottomBoundary;

		if ( this->findObject(objIndex ,minPixelNumbers ,ROI ,isMulti) )
			return true;

		//若local沒找到再找global
		ROI.setRegion(0 ,CAM_WIDTH-1 ,0 ,CAM_HEIGHT);
		if ( this->findObject(objIndex ,minPixelNumbers ,ROI ,isMulti) )
			return true;
	}

	//not found
	info->objectRegion[objIndex].clear();
	return false;
}
bool Vision::findObject(unsigned char objIndex ,int minPixelNumbers ,RegionOfInterest ROI ,bool isMulti)	//4 parameters
{
	//initial
	ObjectRegion *tempRegion = new ObjectRegion;

	info->objectRegion[objIndex].clear();

	this->isPixelSearched.setTo(false);

	for (int j=ROI.bottom ;j>=ROI.top ;j--)
		//for (int j=ROI.top ;j<=ROI.bottom ;j++)
	{
		for (int i=ROI.left ;i<=ROI.right ;i++)
		{
			searchAround(i ,j ,(0x01<<objIndex) ,tempRegion);

			if (tempRegion->pixelNumbers > minPixelNumbers)
			{//found
				//assign object center
				tempRegion->setBottomCenter2MainPoint();

				//calculate object's robot coordinate
				tempRegion->transformImage2RobotCoordinate();

				//calculate object's distance and angle
				tempRegion->calcDisAndAngle();

				//push back
				info->objectRegion[objIndex].push_back(*tempRegion);

				delete tempRegion;
				if ( !isMulti )
					return true;	//find single
				else{
					tempRegion = new ObjectRegion;
					//tempRegion.initial();	//find multiple objects
				}
			}
			else
			{
				tempRegion->initial();
				/*return false;*/
			}
		}
	}

	delete tempRegion;
	if ( !info->objectRegion[objIndex].empty() )
		return true;
	else
		return false;
}

void Vision::searchAround(int i, int j ,unsigned short colorIndex ,ObjectRegion *objRegion)
{
	//out of boundary
	if ( i<0 || i>this->eyefram->width-1 || j<0 || j>this->eyefram->height-1 )
		//if ( i<0 || i>100 || j<0 || j>100 )
		return;
	//avoid double check
	if ( this->isPixelSearched.at<unsigned char>(j,i) )
		return;

	//to be true after searching the pixel
	this->isPixelSearched.at<unsigned char>(j,i) = true;


	unsigned char h,s,v;
	h = this->camFrame_HSV->imageData[(j*this->eyefram->width+i)*3];
	s = this->camFrame_HSV->imageData[(j*this->eyefram->width+i)*3+1];
	v = this->camFrame_HSV->imageData[(j*this->eyefram->width+i)*3+2];

	if ( hsvObjLUT.color1[h] &hsvObjLUT.color2[s] &hsvObjLUT.color3[v] &colorIndex )
	{
		//mark image
		objRegion->markedImage.at<unsigned char>(j,i) = 255;	

		//update region
		if (objRegion->pixelNumbers == 0)
		{
			//initial boundary
			objRegion->leftBoundary = i;
			objRegion->rightBoundary = i;
			objRegion->topBoundary = j;
			objRegion->bottomBoundary = j;
		}
		else
		{
			if ( i > objRegion->rightBoundary )
				objRegion->rightBoundary = i;
			else if( i < objRegion->leftBoundary )
				objRegion->leftBoundary = i;

			if( j > objRegion->bottomBoundary )
				objRegion->bottomBoundary = j;
			else if ( j < objRegion->topBoundary )
				objRegion->topBoundary = j;
		}

		objRegion->pixelNumbers++;	//move to the next pixel, 符合條件的點+1

		searchAround(i+1 ,j ,colorIndex ,objRegion);	//right
		searchAround(i ,j-1 ,colorIndex ,objRegion);	//up
		searchAround(i-1 ,j ,colorIndex ,objRegion);	//left
		searchAround(i ,j+1 ,colorIndex ,objRegion);	//down

		searchAround(i+5 ,j ,colorIndex ,objRegion);	//right
		searchAround(i ,j-5 ,colorIndex ,objRegion);	//up
		searchAround(i-5 ,j ,colorIndex ,objRegion);	//left
		searchAround(i ,j+5 ,colorIndex ,objRegion);	//down

	}
	return;
}

// void Vision::searchAround(int i, int j ,unsigned short colorIndex ,ObjectRegion *objRegion)
// {
// 	//out of boundary
// 	if ( i<0 || i>this->eyefram->width-1 || j<0 || j>this->eyefram->height-1 )
// 	//if ( i<0 || i>100 || j<0 || j>100 )
// 		return;
// 	//avoid double check
// 	if ( this->isPixelSearched.at<unsigned char>(j,i) )
// 		return;
// 
// 	//to be true after searching the pixel
// 	this->isPixelSearched.at<unsigned char>(j,i) = true;
// 
// 
// 	unsigned char h,s,v;
// 	h = this->camFrame_HSV->imageData[(j*this->eyefram->width+i)*3];
// 	s = this->camFrame_HSV->imageData[(j*this->eyefram->width+i)*3+1];
// 	v = this->camFrame_HSV->imageData[(j*this->eyefram->width+i)*3+2];
// 
// 	if ( hsvObjLUT.color1[h] &hsvObjLUT.color2[s] &hsvObjLUT.color3[v] &colorIndex )
// 	{
// 		//mark image
// 		objRegion->markedImage.at<unsigned char>(j,i) = 255;	
// 
// 		//update region
// 		if (objRegion->pixelNumbers == 0)
// 		{
// 			//initial boundary
// 			objRegion->leftBoundary = i;
// 			objRegion->rightBoundary = i;
// 			objRegion->topBoundary = j;
// 			objRegion->bottomBoundary = j;
// 		}
// 		else
// 		{
// 			if ( i > objRegion->rightBoundary )
// 				objRegion->rightBoundary = i;
// 			else if( i < objRegion->leftBoundary )
// 				objRegion->leftBoundary = i;
// 
// 			if( j > objRegion->bottomBoundary )
// 				objRegion->bottomBoundary = j;
// 			else if ( j < objRegion->topBoundary )
// 				objRegion->topBoundary = j;
// 		}
// 
// 		objRegion->pixelNumbers++;	//move to the next pixel, 符合條件的點+1
// 
// 		searchAround(i+1 ,j ,colorIndex ,objRegion);	//right
// 		searchAround(i ,j-1 ,colorIndex ,objRegion);	//up
// 		searchAround(i-1 ,j ,colorIndex ,objRegion);	//left
// 		searchAround(i ,j+1 ,colorIndex ,objRegion);	//down
// 
// 		searchAround(i+5 ,j ,colorIndex ,objRegion);	//right
// 		searchAround(i ,j-5 ,colorIndex ,objRegion);	//up
// 		searchAround(i-5 ,j ,colorIndex ,objRegion);	//left
// 		searchAround(i ,j+5 ,colorIndex ,objRegion);	//down
// 
// 	}
// 	return;
// }
