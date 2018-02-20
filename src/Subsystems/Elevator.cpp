#include "Subsystems/Elevator.h"
#include "RobotMap.h"

Elevator::Elevator() : frc::Subsystem("Elevator")
{
	lumberJack.reset(new LumberJack());

	// Defaulting
	std::fill_n(SoftStartChangeArray, SoftSpeedChangeArraySize, ElevatorTravelSpeed);
	std::fill_n(SoftStopChangeArray, SoftSpeedChangeArraySize, ElevatorTravelSpeed);

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
	EndEffectorDropServo->SetAngle(25);
}

void Elevator::RaiseElevator()
{
	IsElevatorGoingUp = true;
	DebugLog("RaiseElevator", 2000);

	IsElevatorOnTheMove = true;
	UpdateSoftSpeedChangeArray(RaiseSpeedMultiplier);
	double speed = SoftSpeedChange();

	//if(MaxHeightLimitSwitch->Get())
	if(false)
	{
		//TODO: Re-enable once this is actually installed
		//speed = StopElevatorSpeed;
	}

	LeftElevatorTalon->Set(speed);
	lumberJack->dLog(std::string("RaiseElevator: ") + std::string(std::to_string(speed)));
	RightElevatorTalon->Set(-speed);
	lumberJack->dLog(std::string("RaiseElevator: ") + std::string(std::to_string(-speed)));
	//TODO: Re-enable once this is actually installed
	UpdateLimitSwitchTracker();
}

void Elevator::LowerElevator()
{
	IsElevatorGoingUp = false;

	DebugLog("LowerElevator", 2000);

	IsElevatorOnTheMove = true;
	UpdateSoftSpeedChangeArray(LowerSpeedMultiplier);
	double speed = SoftSpeedChange();

	//if(MinHeightLimitSwitch->Get())
	if(false)
	{
		//TODO: Re-enable once this is actually installed
		//speed = StopElevatorSpeed;
	}

	LeftElevatorTalon->Set(-speed);
	lumberJack->dLog(std::string("LowerElevator: ") + std::string(std::to_string(-speed)));
	RightElevatorTalon->Set(speed);
	lumberJack->dLog(std::string("LowerElevator: ") + std::string(std::to_string(speed)));
	//TODO: Re-enable once this is actually installed
	UpdateLimitSwitchTracker();
}

void Elevator::UpdateLimitSwitchTracker()
{
	bool limitSwitchValueChanged = false;

	if(!HighLimitSwitch->Get() && !limitSwitchValueChanged && LimitSwitchTracker != HIGH_LIMIT_SWITCH_NUMBER)
	{
		LimitSwitchTracker = HIGH_LIMIT_SWITCH_NUMBER;
		limitSwitchValueChanged = true;
	}
	else if(!MedLimitSwitch->Get() && !limitSwitchValueChanged && LimitSwitchTracker != MED_LIMIT_SWITCH_NUMBER)
	{
		LimitSwitchTracker = MED_LIMIT_SWITCH_NUMBER;
		limitSwitchValueChanged = true;
	}
	else if(!LowLimitSwitch->Get() && !limitSwitchValueChanged && LimitSwitchTracker != LOW_LIMIT_SWITCH_NUMBER)
	{
		LimitSwitchTracker = LOW_LIMIT_SWITCH_NUMBER;
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
	DebugLog("GoToSetPoint", 200);

	IsElevatorOnTheMove = true;

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
	DebugLog("StopElevator", 200);

	std::fill_n(SoftStartChangeArray, SoftSpeedChangeArraySize, ElevatorTravelSpeed);
	std::fill_n(SoftStopChangeArray, SoftSpeedChangeArraySize, ElevatorTravelSpeed);
	LeftElevatorTalon->Set(StopElevatorSpeed);
	DebugLog(std::string("StopElevator: ") + std::string(std::to_string(StopElevatorSpeed)), 2000);
	RightElevatorTalon->Set(StopElevatorSpeed);
	DebugLog(std::string("StopElevator: ") + std::string(std::to_string(StopElevatorSpeed)), 2000);
	IsElevatorOnTheMove = false;
}

void Elevator::UpdateSoftSpeedChangeArray(const double Multiplier)
{
	DebugLog("UpdateSoftSpeedChangeArray", 2000);

	if(LimitSwitchTracker >= HIGH_LIMIT_SWITCH_NUMBER && IsElevatorGoingUp)
	{
		SoftStartChangeArray[SoftSpeedChangeArrayIterator] = ElevatorTravelSpeed * Multiplier/15;
	}
	else if(LimitSwitchTracker == LOW_LIMIT_SWITCH_NUMBER && IsElevatorGoingUp == false && SoftSpeedChange() > 0)
	{
		DebugLog("SoftStopChangeArray", 20);
		SoftStopChangeArray[SoftSpeedChangeArrayIterator] = -ElevatorTravelSpeed * 2;
	}
	else
	{
		SoftStartChangeArray[SoftSpeedChangeArrayIterator] = ElevatorTravelSpeed * Multiplier;
		SoftStopChangeArray[SoftSpeedChangeArrayIterator] = ElevatorTravelSpeed * Multiplier;
	}

	DebugLog(std::string("RaiseSpeedMultiplier: ") + std::to_string(RaiseSpeedMultiplier), 2000);
	DebugLog(std::string("Multiplier: ") + std::to_string(Multiplier), 2000);
	DebugLog(std::string("ElevatorTravelSpeed: ") + std::to_string(ElevatorTravelSpeed), 2000);
	DebugLog(std::string("Start Array value: ") + std::to_string(SoftStartChangeArray[SoftSpeedChangeArrayIterator]), 2000);
	DebugLog(std::string("Stop Array value: ") + std::to_string(SoftStopChangeArray[SoftSpeedChangeArrayIterator]), 2000);
	DebugLog(std::string("Iterator: ") + std::to_string(SoftSpeedChangeArrayIterator), 2000);
	if(++SoftSpeedChangeArrayIterator > SoftSpeedChangeArraySize)
	{
		SoftSpeedChangeArrayIterator = 0;
	}
}

double Elevator::SoftSpeedChange()
{
	DebugLog("SoftSpeedChange", 2000);
	double sum = 0.0;
	double denominator = SoftSpeedChangeArraySize * 1.0;

	for(int i = 0; i < SoftSpeedChangeArraySize; i++)
	{
		if(IsElevatorGoingUp) 
		{
			sum += SoftStartChangeArray[i];
		}
		else 
		{
			sum += SoftStopChangeArray[i];
		}
	}

	DebugLog(std::string("SoftSpeedChange: ") + std::string(std::to_string(sum/denominator)), 2000);

	return sum/denominator;
}

// Bellhop, hold please!
void Elevator::HoldElevator()
{
	if(IsElevatorOnTheMove == false)
	{
		DebugLog("HoldElevator", 200);
		LeftElevatorTalon->Set(ElevatorHoldSpeed);
		DebugLog(std::string("HoldElevator: ") + std::string(std::to_string(ElevatorHoldSpeed)), 2000);
		RightElevatorTalon->Set(-ElevatorHoldSpeed);
		DebugLog(std::string("HoldElevator: ") + std::string(std::to_string(-ElevatorHoldSpeed)), 2000);
	}
}


int Elevator::GetLimitSwitchTracker()
{
	return LimitSwitchTracker;
}

void Elevator::DebugLog(const string& msg)
{
	if(ElevatorDebugLoggingEnabled)
	{
		lumberJack->dLog(msg);
	}
}

void Elevator::DebugLog(const string& msg, int loggingEveryNth)
{
	if(ElevatorDebugLoggingEnabled)
	{
		lumberJack->dLog(msg, loggingEveryNth);
	}
}
