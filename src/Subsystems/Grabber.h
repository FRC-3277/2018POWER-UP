#ifndef Grabber_H
#define Grabber_H

#include "WPILib.h"
#include <Commands/Subsystem.h>
#include "ctre/Phoenix.h"

class Grabber : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

	//Motors
	std::shared_ptr<WPI_TalonSRX> BlockFeedMotor;
	std::shared_ptr<WPI_TalonSRX> TiltMotor;

	//Limit Switches
	std::shared_ptr<DigitalInput> InjectionStopLimitSwitch;
	std::shared_ptr<DigitalInput> EjectionStopLimitSwitch;
	std::shared_ptr<DigitalInput> TiltUpStopLimitSwitch;
	std::shared_ptr<DigitalInput> TiltDownStopLimitSwitch;


public:
	Grabber();
	void InitDefaultCommand();
};

#endif  // Grabber_H
