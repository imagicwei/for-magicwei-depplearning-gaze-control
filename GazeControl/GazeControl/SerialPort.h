#include "stdafx.h"

//this files contains all general functions in this project

#if !defined( SERIALPORT_H ) 
#define SERIALPORT_H

//放入 extern 等原本在header裡面的資料，避免重複宣告 

#define SERIALPORT_TX_LEN 12	//tx 封包長度
#define SERIALPORT_RX_LAN 17	//rx 封包長度

class SerialPort
{
public:

	/* 以下兩行，強制封包以1byte為單位，若不加這兩行，會因為32/64bit電腦，而已4/8bytes為單位 */

#pragma pack(push)	/*push current alignment to stack*/
#pragma pack(1)	 /*set alignment to 1 byte boundary*/

	//union 為一個共用的空間，故存取 Tx 可以用 char array 收，或者用struct的成員使用

	union Tx{
		//Trancactiob
		//拿來用的
		struct{
			//char = 1 byte, short = 2 bytes
			unsigned char startCode;

			unsigned char bodyMotionCode;
			short dis;
			short angle;

			unsigned char headMotionCode;
			unsigned short tiltPos;
			unsigned short panPos;

			unsigned char checksum;
		}data;

		//板子在用的
		unsigned char arr[SERIALPORT_TX_LEN];
	}tx;

	//union 為一個共用的空間，故存取 Rx 可以用 char array 收，或者用struct的成員使用

	union Rx{
		//Recieve
		//拿來用的
		struct{
			//char = 1 byte, short = 2 bytes
			unsigned char start1Code;
			unsigned char start2Code;

			unsigned char dip;
			unsigned short tiltPos;//3 4 
			unsigned short panPos;//5 6 

			unsigned short waistPosRoll;   //固定1908
			unsigned short waistPosTilt;   //固定1908
			unsigned short waistPosPan;   //固定1908

			unsigned char bodyDoingCode;
			unsigned short azimuth;
			unsigned char checksum;
		}data;

		//板子在用的
		unsigned char arr[SERIALPORT_RX_LAN];

	}rx;


	SerialPort(void){

		//memset() 將某一記憶體區段的前 n 個字元全部設定為某一字元 (將整個封包先初始化為0)。
		memset(this->tx.arr ,0 ,SERIALPORT_TX_LEN);
		memset(this->rx.arr ,0 ,SERIALPORT_RX_LAN);
		this->tx.data.tiltPos = 512;
		this->tx.data.panPos = 512;
		this->rx.data.dip = 2;
	};

	~SerialPort(void)
	{

	};
};


#endif