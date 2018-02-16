#include "Subsystems/Elevator.h"
#include "RobotMap.h"

Elevator::Elevator() : frc::Subsystem("Elevator")
{
	lumberJack.reset(new LumberJack());

	// Defaulting
	std::fill_n(SoftSpeedChangeArray, SoftSpeedChangeArraySize, ElevatorTravelSpeed);

	lumberJack->dLog("Assigning talons");
	try
	{
		LeftElevatorTalon.reset(new WPI_TalonSRX(ELEVATOR_MOTOR_LEFT_CAN_ID));
		//LeftElevatorTalon = new WPI_TalonSRX(ELEVATOR_MOTOR_LEFT_CAN_ID);
	}
	catch(const std::exception& e)
	{
		lumberJack->eLog(std::string("LeftElevatorTalon.reset() failed; ") + std::string(e.what()));
	}

	try
	{
		RightElevatorTalon.reset(new WPI_TalonSRX(ELEVATOR_MOTOR_RIGHT_CAN_ID));
		//RightElevatorTalon = new WPI_TalonSRX(ELEVATOR_MOTOR_RIGHT_CAN_ID);
	}
	catch(const std::exception& e)
	{
		lumberJack->eLog(std::string("RightElevatorTalon.reset() failed; ") + std::string(e.what()));
	}


	// Set every Talon to reset the motor safety timeout.
	LeftElevatorTalon->Set(ControlMode::PercentOutput, 0);
	//RightElevatorTalon->Follow(*LeftElevatorTalon);
	//RightElevatorTalon->SetInverted(true);
	RightElevatorTalon->Set(ControlMode::PercentOutput, 0);

	// Servo goes to home position when this line of code is hit.  This drops
	// the end effector when Teleop or Autonomous mode is hit.
	EndEffectorDropServo.reset(new Servo(DROP_END_EFFECTOR_SERVO));

	// Confident it is stopped at the beginning.
	LimitSwitchTracker = 1;

	lumberJack->dLog("Assigning limit switches");
	try
	{
		//MaxHeightLimitSwitch.reset(new DigitalInput(MAX_HEIGHT_LIMIT_SWITCH_ID));
	}
	catch(const std::exception& e)
	{
		lumberJack->eLog(std::string("MaxHeightLimitSwitch.reset() failed; ") + std::string(e.what()));
	}

	try
	{
		//MinHeightLimitSwitch.reset(new DigitalInput(MIN_HEIGHT_LIMIT_SWITCH_ID));
	}
	catch(const std::exception& e)
	{
		lumberJack->eLog(std::string("MinHeightLimitSwitch.reset() failed; ") + std::string(e.what()));
	}


	try
	{
		HighLimitSwitch.reset(new DigitalInput(HIGH_LIMIT_SWITCH_ID));
	}
	catch(const std::exception& e)
	{
		lumberJack->eLog(std::string("HighLimitSwitch.reset() failed; ") + std::string(e.what()));
	}

	try
	{
		MedLimitSwitch.reset(new DigitalInput(MED_LIMIT_SWITCH_ID));
	}
	catch(const std::exception& e)
	{
		lumberJack->eLog(std::string("MedLimitSwitch.reset() failed; ") + std::string(e.what()));
	}

	try
	{
		LowLimitSwitch.reset(new DigitalInput(LOW_LIMIT_SWITCH_ID));
	}
	catch(const std::exception& e)
	{
		lumberJack->eLog(std::string("LowLimitSwitch.reset() failed; ") + std::string(e.what()));
	}
}

void Elevator::InitDefaultCommand()
{
}

void Elevator::RaiseElevator()
{
	UpdateSoftSpeedChangeArray(RaiseSpeedMultiplier);
	double speed = SoftStart();

	if(MaxHeightLimitSwitch->Get())
	{
		//TODO: Re-enable once this is actually installed
		//speed = StopElevatorSpeed;
	}

	LeftElevatorTalon->Set(speed);
	RightElevatorTalon->Set(-speed);
	lumberJack->iLog(std::string("RaiseElevator: ") + std::string(std::to_string(speed)));
	//TODO: Re-enable once this is actually installed
	UpdateLimitSwitchTracker();
}

void Elevator::LowerElevator()
{
	UpdateSoftSpeedChangeArray(LowerSpeedMultiplier);
	double speed = ElevatorTravelSpeed;

	if(MinHeightLimitSwitch->Get())
	{
		//TODO: Re-enable once this is actually installed
		//speed = StopElevatorSpeed;
	}

	LeftElevatorTalon->Set(-speed);
	RightElevatorTalon->Set(speed);
	lumberJack->iLog(std::string("LowerElevator: ") + std::string(std::to_string(speed)));
	//TODO: Re-enable once this is actually installed
	UpdateLimitSwitchTracker();
}

void Elevator::UpdateLimitSwitchTracker()
{
	bool limitSwitchValueChanged = false;

	if(!HighLimitSwitch->Get() && !limitSwitchValueChanged)
	{
		LimitSwitchTracker = 4;
		limitSwitchValueChanged = true;
	}
	else if(!MedLimitSwitch->Get() && !limitSwitchValueChanged)
	{
		LimitSwitchTracker = 3;
		limitSwitchValueChanged = true;
	}
	else if(!LowLimitSwitch->Get() && !limitSwitchValueChanged)
	{
		LimitSwitchTracker = 2;
		limitSwitchValueChanged = true;
	}
	else
	{
		// Reset
		limitSwitchValueChanged = false;
	}

	if(limitSwitchValueChanged)
	{
		lumberJack->iLog(std::string(__FILE__) + std::string("; Limit switch value changed: ") + std::to_string(LimitSwitchTracker));
	}
}

// Meant not to be used directly, but called by commands
bool Elevator::GoToSetPoint(int DesiredSetpoint)
{
	bool isAtDesiredSetpoint = false;

	UpdateLimitSwitchTracker();

	// Go up or go down?
	if(DesiredSetpoint > LimitSwitchTracker)
	{
		RaiseElevator();
	}
	else if(DesiredSetpoint < LimitSwitchTracker)
	{
		LowerElevator();
	}
	else if(LimitSwitchTracker == DesiredSetpoint)
	{
		isAtDesiredSetpoint = true;
		lumberJack->iLog(std::string(__FILE__) + std::string("; Elevator at desired setpoint: ") + std::to_string(DesiredSetpoint));
	}

	return isAtDesiredSetpoint;
}

void Elevator::StopElevator()
{
	std::fill_n(SoftSpeedChangeArray, SoftSpeedChangeArraySize, ElevatorTravelSpeed);
	LeftElevatorTalon->Set(StopElevatorSpeed);
	RightElevatorTalon->Set(StopElevatorSpeed);
}

void Elevator::UpdateSoftSpeedChangeArray(const double Multiplier)
{
	SoftSpeedChangeArray[SoftSpeedChangeArrayIterator] = ElevatorTravelSpeed * Multiplier;

	lumberJack->iLog(std::string("RaiseSpeedMultiplier: ") + std::to_string(RaiseSpeedMultiplier));
	lumberJack->iLog(std::string("Multiplier: ") + std::to_string(Multiplier));
	lumberJack->iLog(std::string("ElevatorTravelSpeed: ") + std::to_string(ElevatorTravelSpeed));
	lumberJack->iLog(std::string("Array value: ") + std::to_string(SoftSpeedChangeArray[SoftSpeedChangeArrayIterator]));
	lumberJack->iLog(std::string("Iterator: ") + std::to_string(SoftSpeedChangeArrayIterator));
	if(++SoftSpeedChangeArrayIterator > SoftSpeedChangeArraySize)
	{
		SoftSpeedChangeArrayIterator = 0;
	}
}

double Elevator::SoftStart()
{
	double sum = 0.0;
	double denominator = SoftSpeedChangeArraySize * 1.0;

	for(int i = 0; i < SoftSpeedChangeArraySize; i++)
	{
		sum += SoftSpeedChangeArray[i];
	}

	lumberJack->iLog(std::to_string(sum/denominator));

	return sum/denominator;
}

double Elevator::SoftStop()
{
	//TODO:  Finish this now that we have limit switches.
}


int Elevator::GetLimitSwitchTracker()
{
	return LimitSwitchTracker;
}
