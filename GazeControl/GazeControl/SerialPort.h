#include "stdafx.h"

//this files contains all general functions in this project

#if !defined( SERIALPORT_H ) 
#define SERIALPORT_H

//��J extern ���쥻�bheader�̭�����ơA�קK���ƫŧi 

#define SERIALPORT_TX_LEN 12	//tx �ʥ]����
#define SERIALPORT_RX_LAN 17	//rx �ʥ]����

class SerialPort
{
public:

	/* �H�U���A�j��ʥ]�H1byte�����A�Y���[�o���A�|�]��32/64bit�q���A�Ӥw4/8bytes����� */

#pragma pack(push)	/*push current alignment to stack*/
#pragma pack(1)	 /*set alignment to 1 byte boundary*/

	//union ���@�Ӧ@�Ϊ��Ŷ��A�G�s�� Tx �i�H�� char array ���A�Ϊ̥�struct�������ϥ�

	union Tx{
		//Trancactiob
		//���ӥΪ�
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

		//�O�l�b�Ϊ�
		unsigned char arr[SERIALPORT_TX_LEN];
	}tx;

	//union ���@�Ӧ@�Ϊ��Ŷ��A�G�s�� Rx �i�H�� char array ���A�Ϊ̥�struct�������ϥ�

	union Rx{
		//Recieve
		//���ӥΪ�
		struct{
			//char = 1 byte, short = 2 bytes
			unsigned char start1Code;
			unsigned char start2Code;

			unsigned char dip;
			unsigned short tiltPos;//3 4 
			unsigned short panPos;//5 6 

			unsigned short waistPosRoll;   //�T�w1908
			unsigned short waistPosTilt;   //�T�w1908
			unsigned short waistPosPan;   //�T�w1908

			unsigned char bodyDoingCode;
			unsigned short azimuth;
			unsigned char checksum;
		}data;

		//�O�l�b�Ϊ�
		unsigned char arr[SERIALPORT_RX_LAN];

	}rx;


	SerialPort(void){

		//memset() �N�Y�@�O����Ϭq���e n �Ӧr�������]�w���Y�@�r�� (�N��ӫʥ]����l�Ƭ�0)�C
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