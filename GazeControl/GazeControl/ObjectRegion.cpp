
// stdafx.cpp : �ȥ]�t�з� Include �ɪ���l�{����
// Standard Form.pch �|��������sĶ���Y��
// stdafx.obj �|�]�t����sĶ���O��T

#include "stdafx.h"

void ObjectRegion::initial()
{
	leftBoundary = 0;
	rightBoundary = 0;
	topBoundary = 0;
	bottomBoundary = 0;

	pixelNumbers = 0;

	mainPoint.x = 0;
	mainPoint.y = 0;

	robotCoordinate.x = 0;
	robotCoordinate.y = 0;
	robotCoordinate.z = 0;

	dis = 0;
	panAngle = 0;

	//markedImage.setTo(0);
}

void ObjectRegion::transformImage2RobotCoordinate(){

		this->transformImage2RobotCoordinate_teensize();
		return;

}

void ObjectRegion::transformImage2RobotCoordinate_teensize(){

	// David teen size //

	cv::Point2d imageCoor = this->mainPoint;
// 	cv::Point2d imageCoor;
// 	imageCoor.x = 320;
// 	imageCoor.y = 240;

	cv::Point3d *robotCoor = &this->robotCoordinate;

	double x1 = info->strategy.getHeadTiltAngle();
	double y1 = info->strategy.getHeadPanAngle();
	double x2 = info->waistTiltAngle;//info->strategy.getWaistTiltAngle();
	double y2 = 0;//info->strategy.getWaistPanAngle();
	double z2 = 0;//info->strategy.getWaistRollAngle();
// 
// 	if ( info->eventIndex == INNOLUX_EVENT::BASKETBALL )
// 	{
// 		double x2 = 0;
// 	}

/*	printf( "tilt = %.0f,  pan = %.0f, waist = %.0f \n\n", x1, y1, y2);*/

	double sinx1 = sin(x1*CV_PI/180);
	double siny1 = sin(y1*CV_PI/180);
	double cosx1 = cos(x1*CV_PI/180);
	double cosy1 = cos(y1*CV_PI/180);
	double sinx2 = sin(x2*CV_PI/180);
	double siny2 = sin(y2*CV_PI/180);
	double sinz2 = sin(z2*CV_PI/180);
	double cosx2 = cos(x2*CV_PI/180);
	double cosy2 = cos(y2*CV_PI/180);
	double cosz2 = cos(z2*CV_PI/180);

	//fira TEEN size�A1����Y 2��ܸy

	double dy1 = 55; 
	double dz1 = 42;

	double dy2 = 262;
	double dz2 = 47;

	double dy3 = 618 - robotCoor->y;

	double xc = dz1*(sinx1*(cosy2*sinz2 - cosz2*sinx2*siny2) + cosx1*(siny1*(cosy2*cosz2 + sinx2*siny2*sinz2) + cosx2*cosy1*siny2)) - dy1*(cosx1*(cosy2*sinz2 - cosz2*sinx2*siny2) - sinx1*(siny1*(cosy2*cosz2 + sinx2*siny2*sinz2) + cosx2*cosy1*siny2)) - dy2*(cosy2*sinz2 - cosz2*sinx2*siny2) + cosx2*dz2*siny2;
	double yc = dy3 - dz2*sinx2 - dy1*(sinx1*(cosy1*sinx2 - cosx2*siny1*sinz2) - cosx1*cosx2*cosz2) - dz1*(cosx1*(cosy1*sinx2 - cosx2*siny1*sinz2) + cosx2*cosz2*sinx1) + cosx2*cosz2*dy2;
	double zc = dy2*(siny2*sinz2 + cosy2*cosz2*sinx2) + dy1*(cosx1*(siny2*sinz2 + cosy2*cosz2*sinx2) - sinx1*(siny1*(cosz2*siny2 - cosy2*sinx2*sinz2) - cosx2*cosy1*cosy2)) - dz1*(sinx1*(siny2*sinz2 + cosy2*cosz2*sinx2) + cosx1*(siny1*(cosz2*siny2 - cosy2*sinx2*sinz2) - cosx2*cosy1*cosy2)) + cosx2*cosy2*dz2;

	//�����q�}���y�����v���y�Ъ��x�}
	//�ӥ@�ɮy�Ф�xyz�P�v���y�Ф�xyz�������ǰt�A�ݦA�g�L�ഫ
	double M[3][3] = {0};
	M[0][0] = cosy1*cosy2*cosz2 - siny2*(cosx2*siny1 - cosy1*sinx2*sinz2);
	M[0][1] = sinx2*siny1 + cosx2*cosy1*sinz2;
	M[0][2] = - cosy2*(cosx2*siny1 - cosy1*sinx2*sinz2) - cosy1*cosz2*siny2;
	M[1][0] =  cosy2*(cosx1*sinz2 - cosz2*sinx1*siny1) - siny2*(sinx2*(cosx1*cosz2 + sinx1*siny1*sinz2) + cosx2*cosy1*sinx1);
	M[1][1] =  cosy1*sinx1*sinx2 - cosx2*(cosx1*cosz2 + sinx1*siny1*sinz2);
	M[1][2] = - siny2*(cosx1*sinz2 - cosz2*sinx1*siny1) - cosy2*(sinx2*(cosx1*cosz2 + sinx1*siny1*sinz2) + cosx2*cosy1*sinx1);
	M[2][0] = siny2*(sinx2*(cosz2*sinx1 - cosx1*siny1*sinz2) - cosx1*cosx2*cosy1) - cosy2*(sinx1*sinz2 + cosx1*cosz2*siny1);
	M[2][1] = cosx2*(cosz2*sinx1 - cosx1*siny1*sinz2) + cosx1*cosy1*sinx2;
	M[2][2] = siny2*(sinx1*sinz2 + cosx1*cosz2*siny1) + cosy2*(sinx2*(cosz2*sinx1 - cosx1*siny1*sinz2) - cosx1*cosx2*cosy1);

	//�Q��calibration�o��ѼơA���n��i��
	//FOV 63.074947 49.712811

	//double u0 = 323.1178636873615;    //u0, vo, fx, fy ���Ҭ�pixel
	double v0 = 238.0568162405434;
	double u0 = 333;
	//double v0 = 240;
	u0 *= info->vision.camWidth/320;	//fc,cc �nscale�A�]�O�H640x480�ѪR�ץh���q����v���ե��Ѽ�
	v0 *= info->vision.camHeight/240;
	double fx = 608.9504353952276;
	double fy = 609.6595052228630;
	fx *= info->vision.camWidth/320;
	fy *= info->vision.camHeight/240;

	//��v�����~���Ѽ�
	double L = -(xc*M[2][0] + yc*M[2][1] + zc*M[2][2]);
	//�H�U���P�� L����o�쪺���l
	double L1 = u0*M[2][0] -fx*M[0][0];
	double L2 = u0*M[2][1] -fx*M[0][1];
	double L3 = u0*M[2][2] -fx*M[0][2];
	double L4 = -(L1*xc + L2*yc + L3*zc);
	double L5 = v0*M[2][0] -fy*M[1][0];
	double L6 = v0*M[2][1] -fy*M[1][1];
	double L7 = v0*M[2][2] -fy*M[1][2];
	double L8 = -(L5*xc + L6*yc + L7*zc);
	double L9 = M[2][0];
	double L10 = M[2][1];
	double L11 = M[2][2];

	//�W�U�P�� L^2
	double x_numerator = (imageCoor.x*L-L4)*(L7-L11*imageCoor.y)
		-(L3-L11*imageCoor.x)*(L*imageCoor.y-L8);
	double z_numerator = (L1-L9*imageCoor.x)*(imageCoor.y*L-L8)
		-(imageCoor.x*L-L4)*(L5-L9*imageCoor.y);
	double denominator = (L1-L9*imageCoor.x)*(L7-L11*imageCoor.y)
		-(L3-L11*imageCoor.x)*(L5-L9*imageCoor.y);

	if (denominator != 0)
	{
		robotCoor->x = x_numerator/denominator;
		robotCoor->z = z_numerator/denominator;

		//��ݲy�����ɭ� ���ɤ����I�|�W�} �ɭP��줣�O�b�a���W���I
		//�ҥHx,y�|�ܦ��L�a�j
		//�H�U���P�_�ӱ��p�o�ͮ� �Ұ����B�z  ���Ox, y�|����
		double v_lowerbound = (L7*(L1-L9*imageCoor.x)-(L3-L11*imageCoor.x)*L5)
			/ (L11*(L1-L9*imageCoor.x)-L9*(L3-L11*imageCoor.x));
		if(imageCoor.y <= v_lowerbound)
		{
			robotCoor->x = -robotCoor->x;
			robotCoor->z = -robotCoor->z;
		}
	}

}



void ObjectRegion::calcDisAndAngle()
{
	panAngle = atan2(robotCoordinate.x ,robotCoordinate.z)*180/CV_PI;
	dis = sqrt(robotCoordinate.x*robotCoordinate.x + robotCoordinate.z*robotCoordinate.z);
}

void ObjectRegion::setBottomCenter2MainPoint()
{
	mainPoint.x = (leftBoundary + rightBoundary)/2;
	mainPoint.y = bottomBoundary;
}

void ObjectRegion::setCenter2MainPoint()
{
	mainPoint.x = (leftBoundary + rightBoundary)/2;
	mainPoint.y = (topBoundary + bottomBoundary)/2;
}

void ObjectRegion::setTopCenter2MainPoint()
{
	mainPoint.x = (leftBoundary + rightBoundary)/2;
	mainPoint.y = topBoundary;
}

void ObjectRegion::setRightCenter2MainPoint()
{
	mainPoint.x = rightBoundary;
	mainPoint.y = (topBoundary + bottomBoundary)/2;
}

void ObjectRegion::setLeftCenter2MainPoint()
{
	mainPoint.x = leftBoundary;
	mainPoint.y = (topBoundary + bottomBoundary)/2;
}

void ObjectRegion::setBottomRightLeftPoint()
{
	rightPoint.x = rightBoundary;
	rightPoint.y = bottomBoundary;
	leftPoint.x = leftBoundary;
	leftPoint.y = bottomBoundary;
}

void RegionOfInterest::initial()
{
	this->left = 0;
	this->right = 0;
	this->top = 0;
	this->bottom = 0;
}

void RegionOfInterest::setRegion( int left ,int right ,int top ,int bottom ,double ratio )
{
	this->left = left;
	this->right = right;
	this->top = top;
	this->bottom = bottom;

	int width = this->right - this->left;
	int height = this->bottom - this->top;

	this->left = (int)( this->left + 0.5*(1-ratio)*width );
	this->right = (int)( this->right - 0.5*(1-ratio)*width );
	this->top = (int)( this->top + 0.5*(1-ratio)*height );
	this->bottom = (int)( this->bottom - 0.5*(1-ratio)*height );
}