#include "Grabber.h"
#include "../RobotMap.h"
#include <Subsystems/Grabber.h>

Grabber::Grabber()
	: frc::Subsystem("Grabber") {
	//Talons.
	BlockFeedMotor.reset(new WPI_TalonSRX(BLOCK_FEED_MOTOR_CAN_ID));
	TiltMotor.reset(new WPI_TalonSRX(TILT_MOTOR_CAN_ID));

	//Limit Switch
	InjectionStopLimitSwitch.reset(new DigitalInput(BLOCK_INJECTION_STOP_LIMIT_SWITCH_ID));
	EjectionStopLimitSwitch.reset(new DigitalInput(BLOCK_EJECTION_STOP_LIMIT_SWITCH_ID));
	TiltUpStopLimitSwitch.reset(new DigitalInput(BLOCK_TILT_UP_STOP_LIMIT_SWITCH_ID));
	TiltDownStopLimitSwitch.reset(new DigitalInput(BLOCK_TILT_DOWN_STOP_LIMIT_SWITCH_ID));

	// Set every Talon to reset the motor safety timeout.
	BlockFeedMotor->Set(ControlMode::PercentOutput, 0);
	TiltMotor->Set(ControlMode::PercentOutput, 0);



}


void Grabber::InitDefaultCommand() {
}

void Grabber::SpitCube() {

	if(EjectionStopLimitSwitch->Get())
	{
		BlockFeedMotor->Set(0.0);
		EndSpitCommand = true;
	}
	else
	{
		BlockFeedMotor->Set(0.5);
	}
}

void Grabber::EatCube() {
	if(InjectionStopLimitSwitch->Get())
	{
		BlockFeedMotor->Set(0.0);
		EndEatCommand = true;
	}
	else
	{
		BlockFeedMotor->Set(0.5);
	}
}

void Grabber::AugmentorTiltUp() {
	if(TiltUpStopLimitSwitch->Get())
	{
		TiltMotor->Set(0.0);
		EndAugmentorTiltUpCommand = true;
	}
	else
	{
		TiltMotor->Set(0.5);
	}
}

void Grabber::AugmentorTiltDown() {
	if(TiltUpStopLimitSwitch->Get())
	{
		TiltMotor->Set(0.0);
		EndAugmentorTiltDownCommand = true;
	}
	else
	{
		TiltMotor->Set(0.5);
	}
}






