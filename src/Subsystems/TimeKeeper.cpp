#include "Subsystems/TimeKeeper.h"
#include "../RobotMap.h"

TimeKeeper::TimeKeeper() : Subsystem("TimeKeeper")
{

}

void TimeKeeper::InitDefaultCommand()
{
	//TimerBegin = chrono::steady_clock::now();
	//TimerCurrent = chrono::steady_clock::now();
}

double TimeKeeper::GetElapsedTime()
{
	//TimerCurrent = chrono::steady_clock::now();
	//return std::chrono::duration_cast<std::chrono::seconds>(TimerCurrent - TimerBegin).count();
}

void TimeKeeper::ResetClockStart()
{
	//TimerBegin = chrono::steady_clock::now();
}
