#include "TimeKeeper.h"

namespace Kronos
{
	TimeKeeper::TimeKeeper()
	{
		TimerBegin = std::chrono::high_resolution_clock::now();
		TimerCurrent = std::chrono::high_resolution_clock::now();
	}

	TimeKeeper::~TimeKeeper()
	{
	}

	double TimeKeeper::GetElapsedTimeSec()
	{
		TimerCurrent = std::chrono::high_resolution_clock::now();
		return std::chrono::duration_cast<std::chrono::seconds>(TimerCurrent - TimerBegin).count();
	}

	double TimeKeeper::GetElapsedTimeMilli()
	{
		TimerCurrent = std::chrono::high_resolution_clock::now();
		return std::chrono::duration_cast<std::chrono::milliseconds>(TimerCurrent - TimerBegin).count();
	}

	void TimeKeeper::ResetClockStart()
	{
		TimerBegin = std::chrono::high_resolution_clock::now();
	}
}/* namespace Kronos */
