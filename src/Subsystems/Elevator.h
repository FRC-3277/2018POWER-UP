#ifndef Elevator_H
#define Elevator_H

#include "LumberJack.h"

#include "../RobotMap.h"
#include "WPILib.h"
#include "ctre/Phoenix.h"
#include <Commands/Subsystem.h>

class Elevator : public frc::Subsystem {
private:
	std::shared_ptr<LumberJack> lumberJack;

	std::shared_ptr<WPI_TalonSRX> LeftElevatorTalon;
	std::shared_ptr<WPI_TalonSRX> RightElevatorTalon;

	std::shared_ptr<Servo> EndEffectorDropServo;

	// TODO: Disable Max and Min
	std::shared_ptr<DigitalInput> MaxHeightLimitSwitch;
	std::shared_ptr<DigitalInput> MinHeightLimitSwitch;

	std::shared_ptr<DigitalInput> HighLimitSwitch;
	std::shared_ptr<DigitalInput> MedLimitSwitch;
	std::shared_ptr<DigitalInput> LowLimitSwitch;

	static constexpr int HIGH_LIMIT_SWITCH_NUMBER = 4;
	static constexpr int MED_LIMIT_SWITCH_NUMBER = 3;
	static constexpr int LOW_LIMIT_SWITCH_NUMBER = 2;

	bool IsElevatorManuallyControlled = true;

	bool IsElevatorOnTheMove = false;
	// If it is going down then false
	bool IsElevatorGoingUp = true;

	// Track which limit switch has been recently visited.  Start with 1 from bottom until top limit switch
	int LimitSwitchTracker = 0;
	int RequestedLimitSwitchLocation = 0;

	static constexpr double ElevatorTravelSpeed = 0.25;
	const double StopElevatorSpeed = 0.0;

	int SoftSpeedUpChangeArrayIterator = 0;
	int SoftSpeedDownChangeArrayIterator = 0;

	static constexpr int SoftSpeedUpChangeArraySize = 100;
	static constexpr int SoftSpeedDownChangeArraySize = 75;

	double SoftStartChangeArray[SoftSpeedUpChangeArraySize];
	double SoftStopChangeArray[SoftSpeedDownChangeArraySize];
	static constexpr double ElevatorHoldSpeed = 0.15;

	static constexpr double RaiseSpeedMultiplier = 3.5;
	static constexpr double LowerSpeedMultiplier = 1.5;

	void UpdateSoftSpeedChangeArray(const double Multiplier);
	double SoftSpeedChange();
	void DebugLog(const string& msg);
	void DebugLog(const string& msg, int loggingEveryNth);

public:
	Elevator();
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
};

#endif  // Elevator_H
