// stdafx.h : 可在此標頭檔中包含標準的系統 Include 檔，
// 或是經常使用卻很少變更的
// 專案專用 Include 檔案
#pragma once

// TODO: 在此參考您的程式所需要的其他標頭

//Standard Library
//#include <WinSock2.h>
#include <iostream>
#include <windows.h>
#include <XnCppWrapper.h>

#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <assert.h> 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <string>
#pragma comment(lib, "Ws2_32.lib")

using namespace std;

#include <vector>

//Library
#include "videoInput.h"
#include <opencv2/opencv.hpp>

//Our own header 
#include "Define.h"
#include "SerialPort.h"
#include "Sensor.h"
#include "GameTime.h"
#include "MultiTimer.h"
#include "Functions.h"

#include "ObjectRegion.h"
#include "Vision.h"

#include "A_Strategy.h"
#include "Strategy.h"

#include "A_GlobalVariables.h"

#include "CommonInfo.h"


#include "XtionControl.h"

// #include "SetEventPara.h"
// #include "WatchEvenPara.h"
#include "Form1.h"