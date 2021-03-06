#include "Subsystems/Elevator.h"
#include "RobotMap.h"

Elevator::Elevator() : frc::Subsystem("Elevator")
{
	lumberJack.reset(new LumberJack());
	ChangeDirectionTimekeeper.reset(new Kronos::TimeKeeper());
	HighLowExemptionTimekeeper.reset(new Kronos::TimeKeeper());
	RampingTimeoutTimekeeper.reset(new Kronos::TimeKeeper());
	AutonTimekeeper.reset(new Kronos::TimeKeeper());

	TimeBasedSpeedChangeIteratorRaise = (ElevatorTravelSpeed * RaiseSpeedMultiplier) / (ElevatorMillisRamping/20);
	TimeBasedSpeedChangeIteratorLower = (ElevatorTravelSpeed * LowerSpeedMultiplier) / (ElevatorMillisRamping/20);

	// Defaulting
	std::fill_n(SoftStartChangeArray, SoftSpeedUpChangeArraySize, ElevatorTravelSpeed);
	std::fill_n(SoftStopChangeArray, SoftSpeedDownChangeArraySize, ElevatorTravelSpeed);

	lumberJack->dLog("Assigning Talons");
	try
	{
		LeftElevatorTalon.reset(new WPI_TalonSRX(ELEVATOR_MOTOR_LEFT_CAN_ID));
	}
	catch(const std::exception& e)
	{
		lumberJack->eLog(std::string("LeftElevatorTalon.reset() failed; ") + std::string(e.what()));
	}

	try
	{
		RightElevatorTalon.reset(new WPI_TalonSRX(ELEVATOR_MOTOR_RIGHT_CAN_ID));
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
	EndEffectorDropServo.reset(new Servo(ELEVATOR_DROP_END_EFFECTOR_SERVO_ID));

	// Confident it is stopped at the beginning.
	LimitSwitchTracker = 1;

	lumberJack->dLog("Assigning limit switches");
	try
	{
		HighLimitSwitch.reset(new DigitalInput(ELEVATOR_HIGH_LIMIT_SWITCH_ID));
	}
	catch(const std::exception& e)
	{
		lumberJack->eLog(std::string("HighLimitSwitch.reset() failed; ") + std::string(e.what()));
	}

	try
	{
		EjectCoreLimitSwitch.reset(new DigitalInput(ELEVATOR_EJECT_CORE_LIMIT_SWITCH_ID));
	}
	catch(const std::exception& e)
	{
		lumberJack->eLog(std::string("EjectCoreLimitSwitch.reset() failed; ") + std::string(e.what()));
	}

	try
	{
		MedLimitSwitch.reset(new DigitalInput(ELEVATOR_MED_LIMIT_SWITCH_ID));
	}
	catch(const std::exception& e)
	{
		lumberJack->eLog(std::string("MedLimitSwitch.reset() failed; ") + std::string(e.what()));
	}

	try
	{
		LowLimitSwitch.reset(new DigitalInput(ELEVATOR_LOW_LIMIT_SWITCH_ID));
	}
	catch(const std::exception& e)
	{
		lumberJack->eLog(std::string("LowLimitSwitch.reset() failed; ") + std::string(e.what()));
	}
}

void Elevator::InitDefaultCommand()
{
	EndEffectorDropServo->SetAngle(DropEndEffectorAngle);
}

void Elevator::RaiseElevator()
{
	// Indicates this direction of travel as just been enabled so start a grace period timer
	if(!IsElevatorOnTheMove)
	{
		ChangeDirectionTimekeeper->ResetClockStart();
		HighLowExemptionTimekeeper->ResetClockStart();
		RampingTimeoutTimekeeper->ResetClockStart();
	}

	// Elevator change direction detection
	if(!IsElevatorGoingUp && ChangeDirectionTimekeeper->GetElapsedTimeMilli() < ElapsedMillisTriggerDirectionChange)
	{
		HasElevatorDirectionChanged = true;
	}
	else if(HasElevatorDirectionChanged && ChangeDirectionTimekeeper->GetElapsedTimeMilli() > ElapsedMillisTriggerDirectionChange)
	{
		HasElevatorDirectionChanged = false;
	}

	IsElevatorGoingUp = true;
	DebugLog("RaiseElevator", 2000);

	IsElevatorOnTheMove = true;
	UpdateSoftSpeedChangeArray(RaiseSpeedMultiplier);
	double speed = 0.0;

	if(IsLifterSubsystemEnabled)
	{
		speed = ElevatorLifterTravelSpeed;
	}
	else if(TimeBasedRamping)
	{
		double TimeElapsed = RampingTimeoutTimekeeper->GetElapsedTimeMilli();

		if(TimeElapsed < TimeBasedRamping)
		{
			TimeBasedSpeed += TimeBasedSpeedChangeIteratorRaise;
			speed = TimeBasedSpeed; 
		}
		else
		{
			speed = ElevatorTravelSpeed * RaiseSpeedMultiplier;
			if(LimitSwitchTracker >= HIGH_LIMIT_SWITCH_NUMBER)
			{
				speed = speed / 2;
			}
		}
	}
	else
	{
		speed = SoftSpeedChange();
	}

	if(ElevatorRunHalfSpeed)
	{
		speed = speed/2;
	}

	LeftElevatorTalon->Set(speed);
	DebugLog(std::string("RaiseElevator: ") + std::string(std::to_string(speed)), 30);
	RightElevatorTalon->Set(-speed);
	DebugLog(std::string("RaiseElevator: ") + std::string(std::to_string(-speed)), 30);
	//TODO: Re-enable once this is actually installed
	UpdateLimitSwitchTracker();
}

void Elevator::LowerElevator()
{
	// Indicates this direction of travel as just been enabled so start a grace period timer
	if(!IsElevatorOnTheMove)
	{
		ChangeDirectionTimekeeper->ResetClockStart();
		HighLowExemptionTimekeeper->ResetClockStart();
		RampingTimeoutTimekeeper->ResetClockStart();
	}

	// Elevator change direction detection
	if(IsElevatorGoingUp && ChangeDirectionTimekeeper->GetElapsedTimeMilli() < ElapsedMillisTriggerDirectionChange)
	{
		HasElevatorDirectionChanged = true;
	}
	else if(HasElevatorDirectionChanged && ChangeDirectionTimekeeper->GetElapsedTimeMilli() > ElapsedMillisTriggerDirectionChange)
	{
		HasElevatorDirectionChanged = false;
	}

	IsElevatorGoingUp = false;

	DebugLog("LowerElevator", 2000);

	IsElevatorOnTheMove = true;
	UpdateSoftSpeedChangeArray(LowerSpeedMultiplier);
	double speed = SoftSpeedChange();

	if(IsLifterSubsystemEnabled)
	{
		speed = ElevatorLifterTravelSpeed / 5;
	}
	else if(TimeBasedRamping)
	{
		double TimeElapsed = RampingTimeoutTimekeeper->GetElapsedTimeMilli();

		if(TimeElapsed < TimeBasedRamping)
		{
			TimeBasedSpeed += TimeBasedSpeedChangeIteratorLower;
			speed = TimeBasedSpeed; 
		}
		else
		{
			speed = ElevatorTravelSpeed * LowerSpeedMultiplier;
			if(LimitSwitchTracker <= LOW_LIMIT_SWITCH_NUMBER)
			{
				speed = speed / 2;
			}
		}
	}
	else
	{
		speed = SoftSpeedChange();
	}

	if(ElevatorRunHalfSpeed)
	{
		speed = speed/2;
	}

	LeftElevatorTalon->Set(-speed);
	DebugLog(std::string("LowerElevator: ") + std::string(std::to_string(-speed)), 30);
	RightElevatorTalon->Set(speed);
	DebugLog(std::string("LowerElevator: ") + std::string(std::to_string(speed)), 30);

	UpdateLimitSwitchTracker();
}

void Elevator::UpdateLimitSwitchTracker()
{
	bool limitSwitchValueChanged = false;

	if(LeftElevatorTalon->GetSensorCollection().IsFwdLimitSwitchClosed())
	{
		LimitSwitchTracker = MAX_LIMIT_SWITCH_NUMBER;
	}
	else if(!HighLimitSwitch->Get())
	{
		LimitSwitchTracker = HIGH_LIMIT_SWITCH_NUMBER;
	}
	else if(!EjectCoreLimitSwitch->Get())
	{
		LimitSwitchTracker = EJECT_CORE_LIMIT_SWITCH_NUMBER;
	}
	else if(!MedLimitSwitch->Get())
	{
		LimitSwitchTracker = MED_LIMIT_SWITCH_NUMBER;
	}
	else if(!LowLimitSwitch->Get())
	{
		LimitSwitchTracker = LOW_LIMIT_SWITCH_NUMBER;
	}
	else if(LeftElevatorTalon->GetSensorCollection().IsRevLimitSwitchClosed())
	{
		LimitSwitchTracker = MIN_LIMIT_SWITCH_NUMBER;
	}
}

// Meant not to be used directly, but called by commands
bool Elevator::GoToSetPoint(int DesiredSetpoint)
{
	DebugLog("GoToSetPoint", 30);

	IsElevatorOnTheMove = true;

	bool isAtDesiredSetpoint = false;

	RequestedLimitSwitchLocation = DesiredSetpoint;

	UpdateLimitSwitchTracker();

	//lumberJack->eLog(std::string("DesiredSetpoint: ") + std::to_string(DesiredSetpoint) + std::string("LimitSwitchTracker: ") + std::to_string(LimitSwitchTracker));

	if(abs(DesiredSetpoint - LimitSwitchTracker) == 1)
	{
		ElevatorRunHalfSpeed = true;
	}
	else
	{
		ElevatorRunHalfSpeed = false;
	}

	//lumberJack->eLog(std::string("Desired: ") + std::to_string(DesiredSetpoint) + std::string(" Current: ") + std::to_string(LimitSwitchTracker));

	// Go up or go down?
	if(LimitSwitchTracker == DesiredSetpoint)
	{
		isAtDesiredSetpoint = true;
		lumberJack->iLog(std::string(__FILE__) + "; " + std::to_string(__LINE__) + std::string("; Elevator at desired setpoint: ") + std::to_string(DesiredSetpoint));
		StopElevator();
	}
	else if(DesiredSetpoint > LimitSwitchTracker)
	{
		RaiseElevator();
	}
	else if(DesiredSetpoint < LimitSwitchTracker)
	{
		LowerElevator();
	}

	return isAtDesiredSetpoint;
}

void Elevator::StopElevator()
{
	DebugLog("StopElevator");

	double CurrentSpeed = LeftElevatorTalon->Get();
	for(double i = CurrentSpeed; CurrentSpeed > 0; CurrentSpeed -= CurrentSpeed/10)
	{
		LeftElevatorTalon->Set(CurrentSpeed);
		RightElevatorTalon->Set(-CurrentSpeed);
		if(CurrentSpeed <= ElevatorHoldSpeed)
		{
			break;
		}
	}

	LeftElevatorTalon->Set(StopElevatorSpeed);
	RightElevatorTalon->Set(StopElevatorSpeed);
	IsElevatorOnTheMove = false;
	std::fill_n(SoftStartChangeArray, SoftSpeedUpChangeArraySize, ElevatorTravelSpeed);
	std::fill_n(SoftStopChangeArray, SoftSpeedDownChangeArraySize, ElevatorTravelSpeed);
	DebugLog(std::string("StopElevator: ") + std::string(std::to_string(StopElevatorSpeed)));
	DebugLog(std::string("StopElevator: ") + std::string(std::to_string(StopElevatorSpeed)));
	// reset
	TimeBasedSpeed = ElevatorTravelSpeed;
	ElevatorRunHalfSpeed = false;
}

void Elevator::UpdateSoftSpeedChangeArray(const double Multiplier)
{
	DebugLog("UpdateSoftSpeedChangeArray", 2000);

	double TempSpeed = 0.0;
	double TempSpeedChange = 0.0;
	double LocalMultiplier = Multiplier;

	if(IsElevatorGoingUp && IsElevatorManuallyControlled)
	{
		TempSpeedChange = ElevatorTravelSpeed * LocalMultiplier/15;
		TempSpeed = ElevatorTravelSpeed * LocalMultiplier;
	}
	else if(!IsElevatorGoingUp && IsElevatorManuallyControlled)
	{
		TempSpeedChange = -ElevatorTravelSpeed * 4;
		TempSpeed = ElevatorTravelSpeed * LocalMultiplier * 1.4;
	}
	else if(IsElevatorGoingUp && IsElevatorManuallyControlled == false)
	{
		TempSpeedChange = ElevatorTravelSpeed * LocalMultiplier/30;
		TempSpeed = ElevatorTravelSpeed * LocalMultiplier/2;
	}
	else if(!IsElevatorGoingUp && IsElevatorManuallyControlled == false)
	{
		TempSpeedChange = -ElevatorTravelSpeed * 1.5;
		TempSpeed = ElevatorTravelSpeed * LocalMultiplier * 0.25;
	}

	// Ramping is undesirable when the lifter is enabled and rising past midway
	if (IsLifterSubsystemEnabled && LimitSwitchTracker >= MED_LIMIT_SWITCH_NUMBER)
	{
		TempSpeed = ElevatorLifterTravelSpeed;
	}
	else if(HasElevatorDirectionChanged)
	{
		SoftStartChangeArray[SoftSpeedUpChangeArrayIterator] = TempSpeed/10;
		SoftStopChangeArray[SoftSpeedDownChangeArrayIterator] = TempSpeed/10;
	}
	else if(LimitSwitchTracker >= HIGH_LIMIT_SWITCH_NUMBER &&
			IsElevatorGoingUp &&
			HighLowExemptionTimekeeper->GetElapsedTimeMilli() > ElapsedMillisHighLowGracePeriod)
	{
		SoftStartChangeArray[SoftSpeedUpChangeArrayIterator] = TempSpeedChange;
	}
	else if(LimitSwitchTracker == LOW_LIMIT_SWITCH_NUMBER &&
			IsElevatorGoingUp == false &&
			HighLowExemptionTimekeeper->GetElapsedTimeMilli() > ElapsedMillisHighLowGracePeriod &&
			SoftSpeedChange() > 0)
	{
		SoftStopChangeArray[SoftSpeedDownChangeArrayIterator] = TempSpeedChange;
	}
	else
	{
		SoftStartChangeArray[SoftSpeedUpChangeArrayIterator] = TempSpeed;
		SoftStopChangeArray[SoftSpeedDownChangeArrayIterator] = TempSpeed;
	}

	if(IsElevatorGoingUp)
	{
		DebugLog(std::string("RaiseSpeedMultiplier: ") + std::to_string(RaiseSpeedMultiplier), 2000);
		DebugLog(std::string("Multiplier: ") + std::to_string(LocalMultiplier), 2000);
		DebugLog(std::string("ElevatorTravelSpeed: ") + std::to_string(ElevatorTravelSpeed), 2000);
		DebugLog(std::string("Start Array value: ") + std::to_string(SoftStartChangeArray[SoftSpeedUpChangeArrayIterator]), 2000);
		DebugLog(std::string("Iterator: ") + std::to_string(SoftSpeedUpChangeArrayIterator), 2000);
	}
	else
	{
		DebugLog(std::string("LowerSpeedMultiplier: ") + std::to_string(LowerSpeedMultiplier), 2000);
		DebugLog(std::string("Multiplier: ") + std::to_string(LocalMultiplier), 2000);
		DebugLog(std::string("ElevatorTravelSpeed: ") + std::to_string(ElevatorTravelSpeed), 2000);
		DebugLog(std::string("Stop Array value: ") + std::to_string(SoftStopChangeArray[SoftSpeedDownChangeArrayIterator]), 2000);
		DebugLog(std::string("Iterator: ") + std::to_string(SoftSpeedDownChangeArrayIterator), 2000);
	}

	if(++SoftSpeedUpChangeArrayIterator > SoftSpeedUpChangeArraySize)
	{
		SoftSpeedUpChangeArrayIterator = 0;
	}

	if(++SoftSpeedDownChangeArrayIterator > SoftSpeedDownChangeArraySize)
	{
		SoftSpeedDownChangeArrayIterator = 0;
	}
}

double Elevator::SoftSpeedChange()
{
	DebugLog("SoftSpeedUpChange", 2000);
	double sum = 0.0;
	double denominator = 1.0;

	if(IsElevatorGoingUp) 
	{
		for(int i = 0; i < SoftSpeedUpChangeArraySize; i++)
		{
			sum += SoftStartChangeArray[i];
			denominator = SoftSpeedUpChangeArraySize * 1.0;
		}
	}
	else 
	{
		for(int i = 0; i < SoftSpeedDownChangeArraySize; i++)
		{
			sum += SoftStopChangeArray[i];
			denominator = SoftSpeedDownChangeArraySize * 1.0;
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

void Elevator::ToggleInputControlMode()
{
	IsElevatorManuallyControlled = !IsElevatorManuallyControlled;
	lumberJack->iLog("Elevator Manual Mode: " + std::to_string(IsElevatorManuallyControlled));
}

bool Elevator::GetInputControlMode()
{
	return IsElevatorManuallyControlled;
}

void Elevator::SetIsLifterSubsystemEnabled(bool IsLifterSubsystemEnabled)
{
	this->IsLifterSubsystemEnabled = IsLifterSubsystemEnabled;
}

bool Elevator::IsElevatorAtDesiredSetpoint(int DesiredSetpoint)
{
	return DesiredSetpoint == LimitSwitchTracker;
}

void Elevator::SetAutonTimerStart()
{
	AutonTimekeeper->ResetClockStart();
}

double Elevator::GetAutonTimerCurrent()
{
	return AutonTimekeeper->GetElapsedTimeMilli();
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
