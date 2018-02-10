#include "Elevator.h"
#include "../RobotMap.h"

Elevator::Elevator() : frc::Subsystem("Elevator")
{
	lumberJack.reset(new LumberJack());

	lumberJack->dLog("Assigning talons");
	try
	{
		LeftElevatorTalon.reset(new WPI_TalonSRX(ELEVATOR_MOTOR_LEFT_CAN_ID));
	}
	catch(const std::exception& e)
	{
		lumberJack->dLog(std::string("LeftElevatorTalon.reset() failed; ") + std::string(e.what()));
	}

	try
	{
		RightElevatorTalon.reset(new WPI_TalonSRX(ELEVATOR_MOTOR_RIGHT_CAN_ID));
	}
	catch(const std::exception& e)
	{
		lumberJack->dLog(std::string("RightElevatorTalon.reset() failed; ") + std::string(e.what()));
	}


	// Set every Talon to reset the motor safety timeout.
	LeftElevatorTalon->Set(ControlMode::PercentOutput, 0);
	LeftElevatorTalon->Set(ControlMode::PercentOutput, 0);

	// Confident it is stopped at the beginning.
	LimitSwitchTracker = 1;

	lumberJack->dLog("Assigning limit switches");
	try
	{
		MaxHeightLimitSwitch.reset(new DigitalInput(MAX_HEIGHT_LIMIT_SWITCH_ID));
	}
	catch(const std::exception& e)
	{
		lumberJack->dLog(std::string("MaxHeightLimitSwitch.reset() failed; ") + std::string(e.what()));
	}

	try
	{
		MinHeightLimitSwitch.reset(new DigitalInput(MAX_HEIGHT_LIMIT_SWITCH_ID));
	}
	catch(const std::exception& e)
	{
		lumberJack->dLog(std::string("MinHeightLimitSwitch.reset() failed; ") + std::string(e.what()));
	}


	try
	{
		HighLimitSwitch.reset(new DigitalInput(HIGH_LIMIT_SWITCH_ID));
	}
	catch(const std::exception& e)
	{
		lumberJack->dLog(std::string("HighLimitSwitch.reset() failed; ") + std::string(e.what()));
	}

	try
	{
		MedLimitSwitch.reset(new DigitalInput(MED_LIMIT_SWITCH_ID));
	}
	catch(const std::exception& e)
	{
		lumberJack->dLog(std::string("MedLimitSwitch.reset() failed; ") + std::string(e.what()));
	}

	try
	{
		LowLimitSwitch.reset(new DigitalInput(LOW_LIMIT_SWITCH_ID));
	}
	catch(const std::exception& e)
	{
		lumberJack->dLog(std::string("LowLimitSwitch.reset() failed; ") + std::string(e.what()));
	}

}

void Elevator::InitDefaultCommand()
{
}

void Elevator::RaiseElevator()
{
	double speed = ElevatorTravelSpeed;

	if(MaxHeightLimitSwitch->Get())
	{
		speed = StopElevatorSpeed;
	}

	LeftElevatorTalon->Set(speed);
	RightElevatorTalon->Set(speed);
	UpdateLimitSwitchTracker();
}

void Elevator::LowerElevator()
{
	double speed = -ElevatorTravelSpeed;

	if(MinHeightLimitSwitch->Get())
	{
		speed = StopElevatorSpeed;
	}

	LeftElevatorTalon->Set(speed);
	RightElevatorTalon->Set(speed);
	UpdateLimitSwitchTracker();
}

void Elevator::UpdateLimitSwitchTracker()
{
	if(MaxHeightLimitSwitch->Get())
	{
		LimitSwitchTracker = 5;
	}
	if(HighLimitSwitch->Get())
	{
		LimitSwitchTracker = 4;
	}
	else if(MedLimitSwitch->Get())
	{
		LimitSwitchTracker = 3;
	}
	else if(LowLimitSwitch->Get())
	{
		LimitSwitchTracker = 2;
	}
	else if(MinHeightLimitSwitch->Get())
	{
		LimitSwitchTracker = 1;
	}
}

bool Elevator::GoToSetPoint(int DesiredSetpoint)
{
	// Go up by default
	double direction = ElevatorTravelSpeed;
	bool isAtDesiredSetpoint = false;

	UpdateLimitSwitchTracker();

	// Go up or go down?
	if(LimitSwitchTracker < DesiredSetpoint)
	{
		direction = -direction;
	}
	else if(LimitSwitchTracker == DesiredSetpoint)
	{
		direction = StopElevatorSpeed;
		isAtDesiredSetpoint = true;
	}

	LeftElevatorTalon->Set(direction);
	RightElevatorTalon->Set(direction);

	return isAtDesiredSetpoint;
}

void Elevator::StopElevator()
{
	LeftElevatorTalon->Set(StopElevatorSpeed);
	RightElevatorTalon->Set(StopElevatorSpeed);
}
