#ifndef Grabber_H
#define Grabber_H

#include "LumberJack.h"

#include "WPILib.h"
#include <Commands/Subsystem.h>
#include "ctre/Phoenix.h"

class Grabber : public Subsystem {
private:
	std::shared_ptr<LumberJack> lumberJack;

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
	void SpitCube();
	void EatCube();
	void AugmentorTiltUp();
	void AugmentorTiltDown();

	bool EndSpitCommand = false;
	bool EndEatCommand = false;
	bool EndAugmentorTiltUpCommand = false;
	bool EndAugmentorTiltDownCommand = false;
};

#endif  // Grabber_H
