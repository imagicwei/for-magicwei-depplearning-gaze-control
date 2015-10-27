//---------------------------------------------------------------------------
#include "stdafx.h"
// #include "MultiTimer.h"

//---------------------------------------------------------------------------

//int TimerAccuracy;
//MultiTimerStruct TimerMain = {0, 50, false, DefaultIRQ};
//MultiTimerStruct TimerSub = {0, 50, false, DefaultIRQ};

__int64 __i64_CPUFreq = 0;
//TimeDifferenceStrcut T1 = {0,0,0};
//TimeDifferenceStrcut T2 = {0,0,0};

//void TimerBeginPeriod(void)
//{
//	TIMECAPS timecaps;
//	if (timeGetDevCaps(&timecaps,sizeof(TIMECAPS))==TIMERR_NOERROR)
//	{
//		TimerAccuracy = Min( Max(timecaps.wPeriodMin, Accuracy), timecaps.wPeriodMax);
//	}
//	timeBeginPeriod(TimerAccuracy);
//}
//
//void TimerEndPeriod(void)
//{
//	timeEndPeriod(TimerAccuracy);
//}
//
//void TimerStart(MultiTimerStruct* Timer)
//{
//	Timer->Enabled = true;
//	Timer->ID = timeSetEvent(Timer->Interval, TimerAccuracy, Timer->PtrCallBack, 1, TIME_PERIODIC);
//}
//
//void TimerStop(MultiTimerStruct* Timer)
//{
//	Timer->Enabled = false;
//	timeKillEvent(Timer->ID);
//}
//
//void CALLBACK DefaultIRQ(UINT TimerID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
//{
//  //Memo_ShowInfo->Lines->Add("DefaultIRQ");
//}
//
//void CALLBACK TimerMainIRQ(UINT TimerID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
//{
//  
//}
//
//void CALLBACK TimerSubIRQ(UINT TimerID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
//{
//
//}

void GetCPUFreq(void)
{
	LARGE_INTEGER __li_CPUFreq = {0};
  QueryPerformanceFrequency(&__li_CPUFreq);
	__i64_CPUFreq = __li_CPUFreq.QuadPart;
}

__int64 GetCPUTime(void)
{
	LARGE_INTEGER __li_RecTime = {0};
	QueryPerformanceCounter(&__li_RecTime);
	return __li_RecTime.QuadPart;
}

void CalculateTimeDifference_us(TimeDifferenceStrcut* T)
{
	T->dT = ((double)(T->Now - T->Past)) / __i64_CPUFreq * 1000000;
}

void CalculateTimeDifference_ms(TimeDifferenceStrcut* T)
{
	T->dT = ((double)(T->Now - T->Past)) / __i64_CPUFreq * 1000;
}

double CalculateTimeDifference_us(__int64 now, __int64 past)
{
	return ((double)(now - past)) / __i64_CPUFreq * 1000000;
}

double CalculateTimeDifference_ms(__int64 now, __int64 past)
{
	return ((double)(now - past)) / __i64_CPUFreq * 1000;
}

void Delay_us(int us)
{
	TimeDifferenceStrcut time = {0,0,0};
	bool finish = false;

	time.Past = GetCPUTime();
	while(!finish)
	{
		time.Now = GetCPUTime();
		CalculateTimeDifference_us(&time);
		if(time.dT > us)
		{
			finish = true;
		}
  }
}

void Delay_ms(int ms)
{
	TimeDifferenceStrcut time = {0,0,0};
	bool finish = false;

	time.Past = GetCPUTime();
	while(!finish)
	{
		time.Now = GetCPUTime();
		CalculateTimeDifference_ms(&time);
		if(time.dT > ms)
		{
			finish = true;
		}
  }
}
