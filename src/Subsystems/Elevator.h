#ifndef Elevator_H
#define Elevator_H

#include "LumberJack.h"

#include "Class/TimeKeeper.h"
#include "../RobotMap.h"
#include "WPILib.h"
#include "ctre/Phoenix.h"
#include <Commands/Subsystem.h>

class Elevator : public frc::Subsystem
{
private:
	std::shared_ptr<LumberJack> lumberJack;
	// Timers
	// Dual purpose timer.  Stopwatch when button released and one when button pressed before grace period expired
	std::shared_ptr<Kronos::TimeKeeper> ChangeDirectionTimekeeper;
	std::shared_ptr<Kronos::TimeKeeper> HighLowExemptionTimekeeper;
	std::shared_ptr<Kronos::TimeKeeper> RampingTimeoutTimekeeper;

	std::shared_ptr<WPI_TalonSRX> LeftElevatorTalon;
	std::shared_ptr<WPI_TalonSRX> RightElevatorTalon;

	std::shared_ptr<Servo> EndEffectorDropServo;

	std::shared_ptr<DigitalInput> HighLimitSwitch;
	std::shared_ptr<DigitalInput>  EjectCoreLimitSwitch;
	std::shared_ptr<DigitalInput> MedLimitSwitch;
	std::shared_ptr<DigitalInput> LowLimitSwitch;

	bool IsElevatorManuallyControlled = true;

	bool IsElevatorOnTheMove = false;
	// If it is going down then false
	bool IsElevatorGoingUp = true;
	// When the lifter subsystem is enabled this is used in combination with location of elevator to determine speed reduction
	bool IsLifterSubsystemEnabled = false;
	// When this is triggered a timer is kicked off and the speed ramp is reduced
	bool HasElevatorDirectionChanged = false;
	// Run the elevator at half the prescribed speed
	bool ElevatorRunHalfSpeed = false;

	// Time period where if the opposite direction button is pressed will trigger elevator direction has changed
	static constexpr int ElapsedMillisTriggerDirectionChange = 500;
	// Grace period where the upper and lower zones are not speed ramp restricted
	static constexpr int ElapsedMillisHighLowGracePeriod = 1000;
	// Elevator ramping
	static constexpr int ElevatorMillisRamping = 1000;
	bool TimeBasedRamping = true;

	// Track which limit switch has been recently visited.  Start with 1 from bottom until top limit switch
	int LimitSwitchTracker = 0;
	int RequestedLimitSwitchLocation = 0;

	static constexpr double ElevatorTravelSpeed = 0.25;
	static constexpr double ElevatorLifterTravelSpeed = 0.70;
	const double StopElevatorSpeed = 0.0;

	int SoftSpeedUpChangeArrayIterator = 0;
	int SoftSpeedDownChangeArrayIterator = 0;

	double TimeBasedSpeedChangeIteratorRaise = 0.0;
	double TimeBasedSpeedChangeIteratorLower = 0.0;
	double TimeBasedSpeed = ElevatorTravelSpeed;

	static constexpr int SoftSpeedUpChangeArraySize = 10;
	static constexpr int SoftSpeedDownChangeArraySize = 40;

	double SoftStartChangeArray[SoftSpeedUpChangeArraySize];
	double SoftStopChangeArray[SoftSpeedDownChangeArraySize];
	static constexpr double ElevatorHoldSpeed = 0.15;

	static constexpr double RaiseSpeedMultiplier = 4;
	static constexpr double LowerSpeedMultiplier = 1.5;

	void UpdateSoftSpeedChangeArray(const double Multiplier);
	double SoftSpeedChange();
	void DebugLog(const string& msg);
	void DebugLog(const string& msg, int loggingEveryNth);

public:
	Elevator();

	static constexpr int MAX_LIMIT_SWITCH_NUMBER = 5;
	static constexpr int HIGH_LIMIT_SWITCH_NUMBER = 4;
	static constexpr int EJECT_CORE_LIMIT_SWITCH_NUMBER = 3;
	static constexpr int MED_LIMIT_SWITCH_NUMBER = 2;
	static constexpr int LOW_LIMIT_SWITCH_NUMBER = 1;
	static constexpr int MIN_LIMIT_SWITCH_NUMBER = 0;

	void InitDefaultCommand();
	void RaiseElevator();
	void LowerElevator();
	bool GoToSetPoint(int DesiredSetpoint);
	void StopElevator();
	void UpdateLimitSwitchTracker();
	int GetLimitSwitchTracker();
	void HoldElevator();
	void ToggleInputControlMode();
	bool GetInputControlMode();
	void SetIsLifterSubsystemEnabled(bool IsLifterSubsystemEnabled);
	bool IsElevatorAtDesiredSetpoint(int DesiredSetpoint);
};

#endif  // Elevator_H
