#include "Grabber.h"
#include "../RobotMap.h"
#include "Subsystems/Grabber.h"

Grabber::Grabber()
	: frc::Subsystem("Grabber") {
	lumberJack.reset(new LumberJack());

	//Talons.
	try
	{
		GrabberLeftMotor.reset(new WPI_TalonSRX(GRABBER_LEFT_MOTOR_CAN_ID));
	}
	catch(const std::exception& e)
	{
		lumberJack->eLog(std::string("BlockFeedMotor.reset() failed; ") + std::string(e.what()));
	}

	try
	{
		GrabberRightMotor.reset(new WPI_TalonSRX(GRABBER_RIGHT_MOTOR_CAN_ID));
	}
	catch(const std::exception& e)
	{
		lumberJack->eLog(std::string("TiltMotor.reset() failed; ") + std::string(e.what()));
	}


	//Limit Switch
	try
	{
		InjectionStopLimitSwitch.reset(new DigitalInput(BLOCK_INJECTION_STOP_LIMIT_SWITCH_ID));
	}
	catch(const std::exception& e)
	{
		lumberJack->eLog(std::string("InjectionStopLimitSwitch.reset() failed; ") + std::string(e.what()));
	}

	try
	{
		EjectionStopLimitSwitch.reset(new DigitalInput(BLOCK_EJECTION_STOP_LIMIT_SWITCH_ID));
	}
	catch(const std::exception& e)
	{
		lumberJack->eLog(std::string("EjectionStopLimitSwitch.reset() failed; ") + std::string(e.what()));
	}

	try
	{
		TiltUpStopLimitSwitch.reset(new DigitalInput(BLOCK_TILT_UP_STOP_LIMIT_SWITCH_ID));
	}
	catch(const std::exception& e)
	{
		lumberJack->eLog(std::string("TiltUpStopLimitSwitch.reset() failed; ") + std::string(e.what()));
	}

	try
	{
		TiltDownStopLimitSwitch.reset(new DigitalInput(BLOCK_TILT_DOWN_STOP_LIMIT_SWITCH_ID));
	}
	catch(const std::exception& e)
	{
		lumberJack->eLog(std::string("TiltDownStopLimitSwitch.reset() failed; ") + std::string(e.what()));
	}


	// Set every Talon to reset the motor safety timeout.
	GrabberLeftMotor->Set(ControlMode::PercentOutput, 0);
	GrabberRightMotor->Set(ControlMode::PercentOutput, 0);



}


void Grabber::InitDefaultCommand() {
}

void Grabber::SpitCube() {

	if(EjectionStopLimitSwitch->Get())
	{
		GrabberLeftMotor->Set(0.0);
		EndSpitCommand = true;
	}
	else
	{
		GrabberLeftMotor->Set(0.5);
	}
}

void Grabber::EatCube() {
	if(InjectionStopLimitSwitch->Get())
	{
		GrabberLeftMotor->Set(0.0);
		EndEatCommand = true;
	}
	else
	{
		GrabberLeftMotor->Set(0.5);
	}
}

void Grabber::AugmentorTiltUp() {
	if(TiltUpStopLimitSwitch->Get())
	{
		GrabberRightMotor->Set(0.0);
		EndAugmentorTiltUpCommand = true;
	}
	else
	{
		GrabberRightMotor->Set(0.5);
	}
}

void Grabber::AugmentorTiltDown() {
	if(TiltUpStopLimitSwitch->Get())
	{
		GrabberRightMotor->Set(0.0);
		EndAugmentorTiltDownCommand = true;
	}
	else
	{
		GrabberRightMotor->Set(0.5);
	}
}






