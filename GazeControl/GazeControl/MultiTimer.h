//---------------------------------------------------------------------------

#ifndef MultiTimerH
#define MultiTimerH

#define Accuracy 1
#define Min(x,y)  ((x < y) ? x : y)
#define Max(x,y)  ((x > y) ? x : y)


// MultiTimer
// typedef struct
// {
// 	UINT ID;
// 	int Interval; // unit: ms
// 	bool Enabled;
// 	void CALLBACK (*PtrCallBack) (UINT, UINT, DWORD, DWORD, DWORD);
// } MultiTimerStruct;

/*
If the timer interval is smaller than the executing time of the
corresponding CALLBACK function, which is similar as the IRQHandler
of the timer interrupt in STM32, than the real time interval between
two adjacent events will be about the executing time of previous event.

For example:
Set the timer interval of Timer1 as 50ms, and the CALLBACK function
need 60ms to execute. Then, the the differnce between the first
trigger time and the second trigger time will be larger than 60ms rathen
than equal to 50ms.

*/

//extern int TimerAccuracy;
//extern MultiTimerStruct TimerMain;
//extern MultiTimerStruct TimerSub;
//
//void TimerBeginPeriod(void);
//void TimerEndPeriod(void);
//void TimerStart(MultiTimerStruct* Timer);
//void TimerStop(MultiTimerStruct* Timer);
//void CALLBACK DefaultIRQ(UINT TimerID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);
//void CALLBACK TimerMainIRQ(UINT TimerID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);
//void CALLBACK TimerSubIRQ(UINT TimerID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);

// Get CPUTime
typedef struct
{
	__int64 Past;
	__int64 Now;
	double dT;
} TimeDifferenceStrcut;

extern __int64 __i64_CPUFreq;
//extern TimeDifferenceStrcut T1;
//extern TimeDifferenceStrcut T2;

void GetCPUFreq(void);
__int64 GetCPUTime(void);
void CalculateTimeDifference_us(TimeDifferenceStrcut* T);
void CalculateTimeDifference_ms(TimeDifferenceStrcut* T);
double CalculateTimeDifference_us(__int64 now, __int64 past);
double CalculateTimeDifference_ms(__int64 now, __int64 past);

void Delay_us(int us);
void Delay_ms(int ms);

//---------------------------------------------------------------------------
#endif
