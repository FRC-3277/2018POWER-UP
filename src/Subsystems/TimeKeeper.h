#ifndef TimeKeeper_H
#define TimeKeeper_H

#include <Commands/Subsystem.h>

class TimeKeeper : public frc::Subsystem
{
private:
	//TODO: Finish timer without c++ keyword "auto"
	std::chrono::steady_clock TimerBegin;
	std::chrono::steady_clock TimerCurrent;
	double ElapsedSeconds = 0.0;

public:
	TimeKeeper();
	void InitDefaultCommand();
	double GetElapsedTime();
	void ResetClockStart();
};

#endif  // TimeKeeper_H
