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
	std::shared_ptr<WPI_TalonSRX> GrabberLeftMotor;
	std::shared_ptr<WPI_TalonSRX> GrabberRightMotor;
	double GrabberMotorSpeed = 0.0;
	static constexpr double DefaultGrabberMotorSpeed = 0.99;


	//Limit Switches
	std::shared_ptr<DigitalInput> InjectionStopLimitSwitch;
	std::shared_ptr<DigitalInput> EjectionStopLimitSwitch;
	std::shared_ptr<DigitalInput> TiltUpStopLimitSwitch;
	std::shared_ptr<DigitalInput> TiltDownStopLimitSwitch;


public:
	bool EndSpitCommand = false;
	bool EndEatCommand = false;
	bool EndAugmentorTiltUpCommand = false;
	bool EndAugmentorTiltDownCommand = false;

	Grabber();
	void InitDefaultCommand();
	void SpitCube();
	void EatCube();
	void AugmentorTiltUp();
	void AugmentorTiltDown();
	void GrabberEatStop();
	void GrabberSpitStop();
	void SetGrabberSpitSpeed(double GrabberMotorSpeed);

};

#endif  // Grabber_H
