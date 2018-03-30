#include "Grabber.h"
#include "../RobotMap.h"
#include "Subsystems/Grabber.h"

Grabber::Grabber() : frc::Subsystem("Grabber") {
	lumberJack.reset(new LumberJack());
	AutonTimekeeper.reset(new Kronos::TimeKeeper());

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
		GrabberCubeOnboardLimitSwitch.reset(new DigitalInput(GRABBER_CUBE_ONBOARD_LIMIT_SWITCH_ID));
	}
	catch(const std::exception& e)
	{
		lumberJack->eLog(std::string("GrabberCubeOnboardLimitSwitch.reset() failed; ") + std::string(e.what()));
	}


	// Set every Talon to reset the motor safety timeout.
	GrabberLeftMotor->Set(ControlMode::PercentOutput, 0);
	GrabberRightMotor->Set(ControlMode::PercentOutput, 0);
}


void Grabber::InitDefaultCommand() {
}

void Grabber::SpitCube()
{
	GrabberLeftMotor->Set(-GrabberMotorSpeed);
	GrabberRightMotor->Set(GrabberMotorSpeed);
}

void Grabber::EatCube()
{
	GrabberLeftMotor->Set(DefaultGrabberMotorSpeed);
	GrabberRightMotor->Set(-DefaultGrabberMotorSpeed);
}

void Grabber::GrabberStop()
{
	GrabberLeftMotor->Set(0.0);
	GrabberRightMotor->Set(0.0);
	EndEatCommand = false;
	EndSpitCommand = false;
}

void Grabber::SetGrabberSpitSpeed(double GrabberMotorSpeed)
{
	this->GrabberMotorSpeed = GrabberMotorSpeed;
}

void Grabber::SetAutonTimerStart()
{
	AutonTimekeeper->ResetClockStart();
}

double Grabber::GetAutonTimerCurrent()
{
	return AutonTimekeeper->GetElapsedTimeMilli();
}
