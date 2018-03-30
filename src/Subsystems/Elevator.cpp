#include "Subsystems/Elevator.h"
#include "RobotMap.h"
#include "ctre/Phoenix.h"

#include "../Commands/GoToDesiredPositionCommand.h"

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
	RightElevatorTalon->Set(ControlMode::PercentOutput, 0);
	RightElevatorTalon->Follow(*LeftElevatorTalon);
	RightElevatorTalon->SetInverted(true);

	/* choose quadrature which has a faster update rate */
	LeftElevatorTalon->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, kTimeoutMs);
	LeftElevatorTalon->SetStatusFramePeriod(StatusFrame::Status_1_General_, 10, kTimeoutMs);
	LeftElevatorTalon->SetStatusFramePeriod(StatusFrameEnhanced::Status_3_Quadrature, 10, kTimeoutMs);

	LeftElevatorTalon->Config_kP(kPIDLoopIdx, kP, kTimeoutMs);
	LeftElevatorTalon->Config_kI(kPIDLoopIdx, kI, kTimeoutMs);
	LeftElevatorTalon->Config_kD(kPIDLoopIdx, kD, kTimeoutMs);
	LeftElevatorTalon->Config_kF(kPIDLoopIdx, kF, kTimeoutMs);

	/*
	SmartDashboard::PutString("DB/String 5", "0.1");
	SmartDashboard::PutString("DB/String 6", "0.0");
	SmartDashboard::PutString("DB/String 7", "0.0");
	SmartDashboard::PutString("DB/String 8", "0.0");
	*/

	/* Talon will send new frame every 5ms */
	//LeftElevatorTalon->SetStatusFramePeriod(StatusFrame::Status_1_General_, 5, 10);
	LeftElevatorTalon->SetSensorPhase(kSensorPhase);

	/* Talon is configured to ramp and followers are configured to 0*/
	//LeftElevatorTalon->ConfigClosedloopRamp(kRampSecondsFromNeutralToFull, kNoTimeoutMs);
	//LeftElevatorTalon->ConfigOpenloopRamp(kRampSecondsFromNeutralToFull, kNoTimeoutMs);
	/* no need since master ramps */
	//RightElevatorTalon->ConfigOpenloopRamp(0, kNoTimeoutMs);

	// Reset the encoder position as a precaution
	LeftElevatorTalon->GetSensorCollection().SetQuadraturePosition(0, kTimeoutMs);
	LeftElevatorTalon->GetSensorCollection().SetPulseWidthPosition(0, kTimeoutMs);
	//RightElevatorTalon->GetSensorCollection().SetQuadraturePosition(0, kTimeoutMs);
	//RightElevatorTalon->GetSensorCollection().SetPulseWidthPosition(0, kTimeoutMs);

	// Only the left since right is a follower
	LeftElevatorTalon->ConfigNominalOutputForward(0, kTimeoutMs);
	LeftElevatorTalon->ConfigNominalOutputReverse(0, kTimeoutMs);
	LeftElevatorTalon->ConfigPeakOutputForward(kMaxElevatorSpeed, kTimeoutMs);
	LeftElevatorTalon->ConfigPeakOutputReverse(-kMaxElevatorSpeed, kTimeoutMs);


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
	EndEffectorDropServo->SetAngle(25);
	SetDefaultCommand(new GoToDesiredPositionCommand());
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
	double speed = 0.0;

	if(IsLifterSubsystemEnabled)
	{
		speed = ElevatorLifterTravelSpeed;
	}
	else if(TimeBasedRamping)
	{
		double TimeElapsed = RampingTimeoutTimekeeper->GetElapsedTimeMilli();

		if(TimeElapsed < ElevatorMillisRamping)
		{
			TimeBasedSpeed += TimeBasedSpeedChangeIteratorRaise;
			speed = TimeBasedSpeed; 
		}
		else
		{
			speed = ElevatorTravelSpeed * RaiseSpeedMultiplier;
			/*
			if(LimitSwitchTracker >= HIGH_LIMIT_SWITCH_NUMBER)
			{
				speed = speed / 2;
			}
			*/
		}
	}
	else
	{
		UpdateSoftSpeedChangeArray(RaiseSpeedMultiplier);
		speed = SoftSpeedChange();
	}

	if(ElevatorRunHalfSpeed)
	{
		speed = speed/2;
	}

	if(ElevatorRunQuarterSpeed)
	{
		speed = speed/4;
	}

	LeftElevatorTalon->Set(speed);
	//DebugLog(std::string("RaiseElevator: ") + std::string(std::to_string(speed)), 30);
	//RightElevatorTalon->Set(-speed);
	//DebugLog(std::string("RaiseElevator: ") + std::string(std::to_string(-speed)), 30);
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
	double speed = 0.0;

	if(IsLifterSubsystemEnabled)
	{
		speed = ElevatorLifterTravelSpeed / 5;
	}
	else if(TimeBasedRamping)
	{
		double TimeElapsed = RampingTimeoutTimekeeper->GetElapsedTimeMilli();

		if(TimeElapsed < ElevatorMillisRamping)
		{
			TimeBasedSpeed += TimeBasedSpeedChangeIteratorLower;
			speed = TimeBasedSpeed; 
		}
		else
		{
			speed = ElevatorTravelSpeed * LowerSpeedMultiplier;
			/*
			 * //TODO: Is this needed with the encoder?

			if(LimitSwitchTracker <= LOW_LIMIT_SWITCH_NUMBER)
			{
				speed = speed / 2;
			}
			*/
		}
	}
	else
	{
		UpdateSoftSpeedChangeArray(LowerSpeedMultiplier);
		speed = SoftSpeedChange();
	}

	if(ElevatorRunHalfSpeed)
	{
		speed = speed/2;
	}

	if(ElevatorRunHalfSpeed)
	{
		speed = speed/4;
	}

	LeftElevatorTalon->Set(-speed);

	UpdateLimitSwitchTracker();
}

void Elevator::UpdateLimitSwitchTracker()
{
	bool limitSwitchValueChanged = false;

	if(LeftElevatorTalon->GetSensorCollection().IsFwdLimitSwitchClosed())
	{
		LimitSwitchTracker = MAX_LIMIT_SWITCH_NUMBER;
	}
	else if(LeftElevatorTalon->GetSensorCollection().IsRevLimitSwitchClosed())
	{
		LimitSwitchTracker = MIN_LIMIT_SWITCH_NUMBER;
		if(fabs(LeftElevatorTalon->GetSensorCollection().GetQuadraturePosition()) != 0)
		{
			// Reset the encoder position as a precaution
			LeftElevatorTalon->GetSensorCollection().SetQuadraturePosition(0, kTimeoutMs);
			LeftElevatorTalon->GetSensorCollection().SetPulseWidthPosition(0, kTimeoutMs);
			//RightElevatorTalon->GetSensorCollection().SetQuadraturePosition(0, kTimeoutMs);
			//RightElevatorTalon->GetSensorCollection().SetPulseWidthPosition(0, kTimeoutMs);
		}
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


void Elevator::GoToSetPosition(int DesiredPosition)
{
	double CurrentElevatorPosition = fabs(LeftElevatorTalon->GetSensorCollection().GetQuadraturePosition());
	if(++PrintFrequencyCount > PrintEveryFrequency)
	{
		PrintFrequencyCount = 0;
		lumberJack->iLog(std::string("CurrentElevatorPosition: ") + std::string(std::to_string(CurrentElevatorPosition)));
		lumberJack->iLog(std::string("DesiredPosition: ") + std::string(std::to_string(DesiredPosition)));
	}

	if(CurrentElevatorPosition + 200 >= DesiredPosition &&
		CurrentElevatorPosition - 200 <= DesiredPosition &&
		IsElevatorOnTheMove)
	{
		ElevatorRunHalfSpeed = true;
	}

	if(CurrentElevatorPosition + 150 >= DesiredPosition &&
		CurrentElevatorPosition - 150 <= DesiredPosition &&
		IsElevatorOnTheMove)
	{
		ElevatorRunQuarterSpeed = true;
	}

	if((CurrentElevatorPosition + 100 >= DesiredPosition &&
		CurrentElevatorPosition - 100 <= DesiredPosition) ||
		DesiredPosition == CurrentElevatorPosition)
	{
		if(IsElevatorOnTheMove)
		{
			StopElevator();
		}

		HoldElevator();
	}
	else if(DesiredPosition > CurrentElevatorPosition)
	{
		RaiseElevator();
		lumberJack->iLog(std::string("LeftElevatorTalon->Get(): ") + std::to_string(LeftElevatorTalon->Get()));
	}
	else if(DesiredPosition < CurrentElevatorPosition)
	{
		LowerElevator();
	}
	/*
	lumberJack->iLog(std::string("DesiredPosition: ") + std::string(std::to_string(DesiredPosition)));

	LeftElevatorTalon->Set(ControlMode::Position, DesiredPosition);
	*/
}

void Elevator::StopElevator()
{
	DebugLog("StopElevator");

	double CurrentSpeed = LeftElevatorTalon->Get();
	for(double i = CurrentSpeed; CurrentSpeed > 0; CurrentSpeed -= CurrentSpeed/10)
	{
		LeftElevatorTalon->Set(CurrentSpeed);
		if(CurrentSpeed <= ElevatorHoldSpeed)
		{
			break;
		}
	}

	LeftElevatorTalon->Set(StopElevatorSpeed);
	IsElevatorOnTheMove = false;
	std::fill_n(SoftStartChangeArray, SoftSpeedUpChangeArraySize, ElevatorTravelSpeed);
	std::fill_n(SoftStopChangeArray, SoftSpeedDownChangeArraySize, ElevatorTravelSpeed);
	DebugLog(std::string("StopElevator: ") + std::string(std::to_string(StopElevatorSpeed)));
	DebugLog(std::string("StopElevator: ") + std::string(std::to_string(StopElevatorSpeed)));
	// reset
	TimeBasedSpeed = ElevatorTravelSpeed;
	ElevatorRunHalfSpeed = false;
	ElevatorRunQuarterSpeed = false;
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
	//TODO: Is this needed with the encoder?
	/*
	if (IsLifterSubsystemEnabled && LimitSwitchTracker >= MED_LIMIT_SWITCH_NUMBER)
	{
		TempSpeed = ElevatorLifterTravelSpeed;
	}
	else */
	if(HasElevatorDirectionChanged)
	{
		SoftStartChangeArray[SoftSpeedUpChangeArrayIterator] = TempSpeed/10;
		SoftStopChangeArray[SoftSpeedDownChangeArrayIterator] = TempSpeed/10;
	}
	else if(//TODO: Is this needed with the encoder?
			IsElevatorGoingUp &&
			HighLowExemptionTimekeeper->GetElapsedTimeMilli() > ElapsedMillisHighLowGracePeriod)
	{
		SoftStartChangeArray[SoftSpeedUpChangeArrayIterator] = TempSpeedChange;
	}
	else if(//TODO: Is this needed with the encoder?
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
		LeftElevatorTalon->Set(ControlMode::PercentOutput, ElevatorHoldSpeed);
		DebugLog(std::string("HoldElevator: ") + std::string(std::to_string(ElevatorHoldSpeed)), 2000);
		//RightElevatorTalon->Set(-ElevatorHoldSpeed);
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

double Elevator::GetCurrentElevatorPosition()
{
	return fabs(LeftElevatorTalon->GetSensorCollection().GetQuadraturePosition());
}

double Elevator::IsElevatorAtDesiredPosition(int DesiredPosition)
{
	int CurrentElevatorPosition = GetCurrentElevatorPosition();
	bool IsElevatorAtDesiredPosition = false;
	if(CurrentElevatorPosition + 200 >= DesiredPosition &&
		CurrentElevatorPosition - 200 <= DesiredPosition &&
		IsElevatorOnTheMove)
	{
		ElevatorRunHalfSpeed = true;
	}

	if(CurrentElevatorPosition + 150 >= DesiredPosition &&
		CurrentElevatorPosition - 150 <= DesiredPosition &&
		IsElevatorOnTheMove)
	{
		ElevatorRunQuarterSpeed = true;
	}

	if((CurrentElevatorPosition + 100 >= DesiredPosition &&
		CurrentElevatorPosition - 100 <= DesiredPosition) ||
		DesiredPosition == CurrentElevatorPosition)
	{
		IsElevatorAtDesiredPosition = true;
	}
	else
	{
		IsElevatorAtDesiredPosition = false;
	}

	return IsElevatorAtDesiredPosition;
}

bool Elevator::IsElevatorMoving()
{
	return IsElevatorOnTheMove;
}
