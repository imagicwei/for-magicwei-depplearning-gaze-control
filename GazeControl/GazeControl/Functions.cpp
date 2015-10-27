// stdafx.cpp : 僅包含標準 Include 檔的原始程式檔
// Standard Form.pch 會成為先行編譯標頭檔
// stdafx.obj 會包含先行編譯型別資訊

#include "stdafx.h"

/*
void Rgb2Hsv::RGB2HSV(float R, float G, float B)
{  
	double min, max, delta;

	max=System::Math::Max(System::Math::Max(R,G),B);
	min=System::Math::Min(System::Math::Min(R,G),B);

	V = max;                                
	delta = max - min;

	if( max != 0 )
		S = delta / max * 255;                // s
	else {		 //定義S=0 max= 0 所以min也=0.            
		S = 0;
		H = 360;
		return;
	}
	if (max==min)
	{
		H=0;
	}
	if( R == max && G>=B)
		H = ( G - B ) / delta;                // between yellow & magenta
	if( R == max && B>G)
		H = 6.0 + ( G - B ) /delta;
	if( G == max)
		H = 2.0 + ( B - R ) / delta;        // between cyan & yellow
	if(B==max)
		H = 4.0 + ( R - G ) / delta;        // between magenta & cyan

	H = H * 60 / 360 * 225;                                // degrees

} 
*/

Tool tool;

//計算兩點距離
double Tool::calcDis( int x1, int y1, int x2, int y2 ){

	double deltaX = abs( x2 - x1 );
	double deltaY = abs( y2 - y1 );

	double dis = sqrt ( deltaX*deltaX + deltaY*deltaY );

	return dis;
}

//限制數字範圍，頂多在於上下界
double Tool::limitValue( double x, double y1, double y2 ){

	double min = getMin(y1,y2);
	double max = getMax(y1,y2);

	if ( x > max ) return max;
	if ( x < min ) return min;
	return x;

}


//取得最小值
double Tool::getMin( double x, double y ){
	if ( x > y ) return y;
	if ( x <= y ) return x;
}

//取得最小值
double Tool::getMin( double x, double y, double z ){
	double temp = getMin(x,y);
	return getMin( temp, z );
}

//取得最大值
double Tool::getMax( double x, double y ){
	if ( x > y ) return x;
	if ( x <= y ) return y;
}

//取得最大值
double Tool::getMax( double x, double y, double z ){
	double temp = getMax(x,y);
	return getMax( temp, z );
}

//取得正負號
int Tool::getSign( double input ){
	if ( input > 0 ) return 1;
	if ( input < 0 ) return -1;
	return 0;
}

//小數輸出位數
double Tool::pointDecimal( double x , int y ){

	return (int) ( x * pow((double)10,y) )  * pow((double)10,-y);

}

//寫入檔案
void Tool::writeTxt( char fileName[], char word[] ){

	FILE *txt;
	txt = fopen( fileName, "a");
	fprintf( txt, "%s\n", word );

}


double Tool::calcPolarAngle( int x, int y, int cx, int cy ){

	int dx = x - cx;
	int dy = y - cy;
	int r = calcDis(x,y,cx,cy);
	int angle = System::Math::Atan2 ( dy , dx ) * 180 / PI + 90;

	if ( angle < 0 )
	{
		angle = angle + 360;
	}

	return angle;

// 	if ( x != 0)
// 	{
// 		return atan( (double)y / x );
// 	}
// 	else
// 	{
// 		if ( dy > 0 )
// 		{
// 			return 90;
// 		}
// 		else
// 			return 270;
// 	}

	return asin( (double)dy/r );

}

int Tool::setAngleInRange( int ang ){

	if ( ang > 359 )
	{
		ang = ang - 360;
		return setAngleInRange(ang);
	}

	else if ( ang < 0 )
	{
		ang = ang + 360;
		return setAngleInRange( ang );
	}

 	return ang;
}

int	Tool::calcCartesianX( int radius, int angle, int cx, int cy ){

	int dx = radius * System::Math::Cos( (double)angle*PI/180);

	return (cx + dx);

}

int	Tool::calcCartesianY( int radius, int angle, int cx, int cy ){

	int dy = radius * System::Math::Sin( (double)angle*PI/180);

	return (cy + dy);

}

double Tool::getRandom( double x1, double x2 )
{
	
	double min = this->getMin( x1, x2 );
	double max = this->getMax( x1, x2 );
	srand((unsigned int)time(NULL)); //種子隨時間隨機
	return  (max - min)*rand()/RAND_MAX + min;	//符合均勻性

}

double Tool::getNormalize( double input, double x1, double x2 )
{

	double min = this->getMin( x1, x2 );
	double max = this->getMax( x1, x2 );

	double code = ( input - min ) / ( max - min ) ;
	code = this->limitValue( (double)code, (double)0,(double)1);

	return code;
}

double Tool::pointYOnLine ( double x, double x1, double y1, double x2, double y2 )
{
	/* LINE Calculation*/
	/* 
	   y = ax + b;
	   y2 = a*x2 + b;
	   y1 = a*x1 + b;
	   (y2-y1) = a*(x2-x1);
	   a = (y2-y1)/(x2-x1);
	   b = y2 - a*x2;
	 */
	double a, b = 0;
	if ( abs(x2-x1) != 0)
	{
		a = ( y2 - y1 ) / ( x2 - x1 );
		b = y2 - a*x2;

		return (a*x+b);
	}
	else
		return this->getRandom(y1,y2);
	
}

double Tool::getSlope( double x1, double y1, double x2, double y2 )
{
	if ( abs(x2-x1) != 0)
	{
		double slope = ( y2 - y1 ) / ( x2 - x1 );
		return slope;
	}
	else
		return false;
}

void Tool::swap( double *a, double *b )
{
	double temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

double Tool::mediumFilter( double input )
{
	//複製陣列
	static double arr[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	double order[9];
	static int count = 0;

	//存入資料
	if( count >= 9 )
	{
		count = 0;
	}
	arr[count] = input;

	//printf("count = %d\n", count);
	count++;

	//copy array
	int64 xddd = 12345678901234567;
	xddd = 12345678901234567/10;
	printf("xddd = %I64d\n\n\n\n", xddd );
	memcpy(order,arr,sizeof(double)*9);

	//排序 small --> big
	for ( int i = 0; i < 9-1; i++ )
	{
		for ( int j = 0; j < 9-1-i ; j++ )
		{

			if ( order[j] > order[j+1] )
			{
				this->swap( &order[j], &order[j+1] );
// 				double temp;
// 				temp = order[j+1];
// 				order[j+1] = order[j];
// 				order[j] = temp;
			}
		}
	}


	
// 	for( int i = 0; i < 9; i++ )
// 	{
// 		printf(" %.0f \t", arr[i] );
// 	}
// 	printf("\n");
// 	for( int i = 0; i < 9; i++ )
// 	{
// 		printf(" %.0f \t", order[i] );
// 	}
// 	printf("\n\n");
	return order[4];
}

/*
double Tool::pointYOnLine( double input, double inputMin, double inputMax, double outputMin, double outputMax )
{
	double code = this->getNormalize( input, inputMin, inputMax );
	double result = code * abs ( outputMax - outputMin ) + outputMin;

	return result;


}
*/