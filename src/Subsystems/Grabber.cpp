#include "Grabber.h"
#include "../RobotMap.h"
#include "Subsystems/Grabber.h"

Grabber::Grabber() : frc::Subsystem("Grabber") {
	lumberJack.reset(new LumberJack());

	//Talons
	try
	{
		GrabberLeftMotor.reset(new WPI_TalonSRX(GRABBER_LEFT_MOTOR_CAN_ID));
	}
	catch(const std::exception& e)
	{
		lumberJack->eLog(std::string("GrabberLeftMotor.reset() failed; ") + std::string(e.what()));
	}

	try
	{
		GrabberRightMotor.reset(new WPI_TalonSRX(GRABBER_RIGHT_MOTOR_CAN_ID));
	}
	catch(const std::exception& e)
	{
		lumberJack->eLog(std::string("GrabberRightMotor.reset() failed; ") + std::string(e.what()));
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

	//if(EjectionStopLimitSwitch->Get()) //Anticipation of some sort of limit switch... not installed
	if(false)
	{
		GrabberSpitStop();
		EndSpitCommand = true;
	}
	else
	{
		GrabberLeftMotor->Set(-GrabberMotorSpeed);
		GrabberRightMotor->Set(GrabberMotorSpeed);
	}
}

void Grabber::EatCube() {
	//if(InjectionStopLimitSwitch->Get()) //Anticipation of some sort of limit switch... not installed
	if(false)
	{
		GrabberEatStop();
		EndEatCommand = true;
	}
	else
	{
		GrabberLeftMotor->Set(DefaultGrabberMotorSpeed);
		GrabberRightMotor->Set(-DefaultGrabberMotorSpeed);
	}
}

void Grabber::GrabberEatStop() {
	GrabberLeftMotor->Set(0.0);
	GrabberRightMotor->Set(0.0);
	EndEatCommand = false;
}

void Grabber::GrabberSpitStop() {
	GrabberLeftMotor->Set(0.0);
	GrabberRightMotor->Set(0.0);
	EndSpitCommand = false;
}

void Grabber::SetGrabberSpitSpeed(double GrabberMotorSpeed) {
	this->GrabberMotorSpeed = GrabberMotorSpeed;
}
