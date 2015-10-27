#include "stdAfx.h"
#include "Form1.h"

void GazeControl::Form1::MainDisplay()
{
	if (this->myXtion->IsInitial)
	{
		this->DrawColorImage(this->myXtion->ColorBuffer);
		this->DrawDepthImage((short**)this->myXtion->DepthData); //Only need depth img don't need skeleton
		this->pictureBoxCamXtionInput->Image = this->DepthImage;
	}		
}

System::Drawing::Bitmap^ GazeControl::Form1::DrawColorImage( unsigned char* iImageBuffer )
{ 
	System::IntPtr ptr1(iImageBuffer); 
	System::Drawing::Bitmap^ tmpBitmap = gcnew System::Drawing::Bitmap(640,480,640*3,System::Drawing::Imaging::PixelFormat::Format24bppRgb,ptr1);
	delete this->ColorImage;
	this->ColorImage = tmpBitmap;
	delete this->FinalImage;
	this->FinalImage = gcnew System::Drawing::Bitmap(this->ColorImage);
	return this->ColorImage;
}

System::Drawing::Bitmap^ GazeControl::Form1::DrawDepthImage(short** iImageBuffer)
{
	for(int idxW = 0 ; idxW < 320 ; idxW++)for(int idxH = 0 ; idxH < 240 ; idxH++)
	{
		int tmpIdx = (idxH*320+idxW)*3;
		if ( this->myXtion->DepthData[idxW][idxH] == 0 )
		{
			this->DepthViewBuffer[tmpIdx] = 255;
			this->DepthViewBuffer[tmpIdx+1] = 160;
			this->DepthViewBuffer[tmpIdx+2] = 160;
		}
		else
		{
			unsigned char tmpValue = this->myXtion->DepthData[idxW][idxH] *256 / 7000;
			this->DepthViewBuffer[tmpIdx] = tmpValue;
			this->DepthViewBuffer[tmpIdx+1] = tmpValue;
			this->DepthViewBuffer[tmpIdx+2] = tmpValue;
		}

		info->strategy.DepthDisArr[idxW][idxH] = this->myXtion->DepthData[idxW][idxH]; //把深度資訊丟出來到另外一個矩陣
	}

	// 	if ( !info->strategy.adult.basketball.notCalBasketDepthDis ) //有要算籃框距離
	// 	{
	// 		info->strategy.adult.basketball.basketDepthDisbyXtion = this->myXtion->DepthData[info->strategy.adult.basketball.basketmainX][info->strategy.adult.basketball.basketmainY];
	// 		printf( "\nBasket Depth = %0.f\n",info->strategy.adult.basketball.basketDepthDisbyXtion );
	// 	}

	System::IntPtr ptr1(DepthViewBuffer);
	//System::Drawing::Bitmap^ tmpBitmap = gcnew System::Drawing::Bitmap(320,240,960,System::Drawing::Imaging::PixelFormat::Format24bppRgb,ptr1);
	delete this->LastDepthImage;
	//this->LastDepthImage = tmpBitmap;
	this->LastDepthImage = gcnew System::Drawing::Bitmap(320,240,960,System::Drawing::Imaging::PixelFormat::Format24bppRgb,ptr1);
	delete this->DepthImage;
	this->DepthImage = gcnew System::Drawing::Bitmap(this->LastDepthImage);	
	//this->DepthImage = tmpBitmap;
	//delete DepthViewBuffer;
	return this->DepthImage;
}

System::Drawing::Bitmap^ GazeControl::Form1::DrawDepthColorImageMix( float iTransparent )
{
	System::Drawing::Graphics^ DrawTool;
	DrawTool = System::Drawing::Graphics::FromImage(this->FinalImage);						 
	cli::array<array<float>^>^ matrixItems = gcnew cli::array<array<float>^>(5);
	for (int i = 0 ; i < 5; i++)
		matrixItems[i] = gcnew array<float> (5);
	matrixItems[0][0] = 1;
	matrixItems[1][1] = 1;
	matrixItems[2][2] = 1;
	matrixItems[3][3] = iTransparent;
	matrixItems[4][4] = 1;
	System::Drawing::Imaging::ColorMatrix^ cm = gcnew System::Drawing::Imaging::ColorMatrix(matrixItems);
	System::Drawing::Imaging::ImageAttributes^ imageAtt = gcnew System::Drawing::Imaging::ImageAttributes();
	imageAtt->SetColorMatrix(cm, System::Drawing::Imaging::ColorMatrixFlag::Default, System::Drawing::Imaging::ColorAdjustType::Bitmap);

	DrawTool->DrawImage(this->DepthImage, 
		System::Drawing::Rectangle(0, 0, this->ColorImage->Width, this->ColorImage->Height), 
		0, 0, this->DepthImage->Width, this->DepthImage->Height, 
		System::Drawing::GraphicsUnit::Pixel, 
		imageAtt);


	return this->FinalImage;
}

System::Drawing::Bitmap^ GazeControl::Form1::DrawSkeletononDepthColorImage()
{
	for ( int idx_player = 1 ; idx_player <= NUI_SKELETON_COUNT ; idx_player++ )
	{
		if( myXtion->SkeletonData[idx_player].eTrackingState ==  NUI_SKELETON_TRACKED )
		{
			this->Text = "ID " + Convert::ToString(idx_player) + " is tracked" ;
			System::Drawing::Graphics^ DrawTool = System::Drawing::Graphics::FromImage(this->DepthImage);
			System::Drawing::Pen^ myPen = gcnew System::Drawing::Pen(System::Drawing::Color::Yellow,2);

			XnPoint3D JointsReal[TOTAL_SKELETON_NUM+1];
			XnPoint3D  m_aJoints[TOTAL_SKELETON_NUM+1];
			//把所有的骨架資訊丟給JointsReal，待會要利用座標轉換用(Real To Depth)
			for(int part =1;part<TOTAL_SKELETON_NUM+1;part++)
			{
				JointsReal[part].X = myXtion->SkeletonData[idx_player].SkeletonPositions[part].x;
				JointsReal[part].Y = myXtion->SkeletonData[idx_player].SkeletonPositions[part].y;
				JointsReal[part].Z = myXtion->SkeletonData[idx_player].SkeletonPositions[part].z;
			}
			//轉到depth影像座標
			myXtion->mDepthGenerator.ConvertRealWorldToProjective(TOTAL_SKELETON_NUM+1,JointsReal,m_aJoints);

			array<System::Drawing::Point>^ Points;
			System::Array::Resize(Points,1);
			for(int i =1;i<TOTAL_SKELETON_NUM+1;i++)
			{
				Points[0].X = m_aJoints[i].X-2;  Points[0].Y = m_aJoints[i].Y-2; 
				DrawTool->DrawEllipse( myPen,Points[0].X , Points[0].Y, 4,4);
			}

			//計算頭的深度距離
			int HeadX = m_aJoints[XN_SKEL_HEAD].X;
			int HeadY = m_aJoints[XN_SKEL_HEAD].Y;
			double IDdepth = this->myXtion->DepthData[HeadX][HeadY];
			//printf( "\nIDdepth = %0.f\n",IDdepth );

			System::Array::Resize(Points,2);
			Points[0].X = m_aJoints[XN_SKEL_HEAD].X;                Points[0].Y =  m_aJoints[XN_SKEL_HEAD].Y;
			Points[1].X = m_aJoints[XN_SKEL_NECK].X;                Points[1].Y =  m_aJoints[XN_SKEL_NECK].Y;
			DrawTool->DrawLines(myPen,Points);

			System::Array::Resize(Points,5);
			Points[0].X	= m_aJoints[XN_SKEL_NECK].X;	            Points[0].Y	= m_aJoints[XN_SKEL_NECK].Y;
			Points[1].X	= m_aJoints[XN_SKEL_LEFT_SHOULDER].X;		Points[1].Y	= m_aJoints[XN_SKEL_LEFT_SHOULDER].Y;
			Points[2].X	= m_aJoints[XN_SKEL_LEFT_ELBOW].X;			Points[2].Y	= m_aJoints[XN_SKEL_LEFT_ELBOW].Y;
			Points[3].X	= m_aJoints[XN_SKEL_LEFT_WRIST].X;			Points[3].Y	= m_aJoints[XN_SKEL_LEFT_WRIST].Y;
			Points[4].X	= m_aJoints[XN_SKEL_LEFT_HAND].X;			Points[4].Y	= m_aJoints[XN_SKEL_LEFT_HAND].Y;
			DrawTool->DrawLines(myPen,Points);

			System::Array::Resize(Points,5);
			Points[0].X	= m_aJoints[XN_SKEL_NECK].X;	            Points[0].Y	= m_aJoints[XN_SKEL_NECK].Y;
			Points[1].X	= m_aJoints[XN_SKEL_RIGHT_SHOULDER].X;		Points[1].Y	= m_aJoints[XN_SKEL_RIGHT_SHOULDER].Y;
			Points[2].X	= m_aJoints[XN_SKEL_RIGHT_ELBOW].X;			Points[2].Y	= m_aJoints[XN_SKEL_RIGHT_ELBOW].Y;
			Points[3].X	= m_aJoints[XN_SKEL_RIGHT_WRIST].X;			Points[3].Y	= m_aJoints[XN_SKEL_RIGHT_WRIST].Y;
			Points[4].X	= m_aJoints[XN_SKEL_RIGHT_HAND].X;			Points[4].Y	= m_aJoints[XN_SKEL_RIGHT_HAND].Y;
			DrawTool->DrawLines(myPen,Points);

			System::Array::Resize(Points,3);
			Points[0].X	= m_aJoints[XN_SKEL_NECK].X;	            Points[0].Y	= m_aJoints[XN_SKEL_NECK].Y;
			Points[1].X	= m_aJoints[XN_SKEL_TORSO].X;		        Points[1].Y	= m_aJoints[XN_SKEL_TORSO].Y;
			Points[2].X	= m_aJoints[XN_SKEL_WAIST].X;			    Points[2].Y	= m_aJoints[XN_SKEL_WAIST].Y;
			DrawTool->DrawLines(myPen,Points);

			System::Array::Resize(Points,4);
			Points[0].X	= m_aJoints[XN_SKEL_WAIST].X;	            Points[0].Y	= m_aJoints[XN_SKEL_WAIST].Y;
			Points[1].X	= m_aJoints[XN_SKEL_LEFT_HIP].X;		    Points[1].Y	= m_aJoints[XN_SKEL_LEFT_HIP].Y;
			Points[2].X	= m_aJoints[XN_SKEL_LEFT_KNEE].X;			Points[2].Y	= m_aJoints[XN_SKEL_LEFT_KNEE].Y;
			Points[3].X	= m_aJoints[XN_SKEL_LEFT_ANKLE].X;			Points[3].Y	= m_aJoints[XN_SKEL_LEFT_ANKLE].Y;
			DrawTool->DrawLines(myPen,Points);

			Points[0].X	= m_aJoints[XN_SKEL_WAIST].X;	            Points[0].Y	= m_aJoints[XN_SKEL_WAIST].Y;
			Points[1].X	= m_aJoints[XN_SKEL_RIGHT_HIP].X;		    Points[1].Y	= m_aJoints[XN_SKEL_RIGHT_HIP].Y;
			Points[2].X	= m_aJoints[XN_SKEL_RIGHT_KNEE].X;			Points[2].Y	= m_aJoints[XN_SKEL_RIGHT_KNEE].Y;
			Points[3].X	= m_aJoints[XN_SKEL_RIGHT_ANKLE].X;			Points[3].Y	= m_aJoints[XN_SKEL_RIGHT_ANKLE].Y;
			DrawTool->DrawLines(myPen,Points);

			//printf("\nXtion find people\n");
		}
		// 		else
		// 		{
		// 			info->strategy.adult.fall.isFindPeople = false;
		// 			printf("\nXtion doesnot find people\n");
		// 		}
	}
	return this->FinalImage;
}