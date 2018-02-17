#ifndef Elevator_H
#define Elevator_H

#include "LumberJack.h"

#include "WPILib.h"
#include "ctre/Phoenix.h"
#include <Commands/Subsystem.h>

class Elevator : public frc::Subsystem {
private:
	std::shared_ptr<LumberJack> lumberJack;

	std::shared_ptr<WPI_TalonSRX> LeftElevatorTalon;
	std::shared_ptr<WPI_TalonSRX> RightElevatorTalon;

	// Junk that doesn't work
	//WPI_TalonSRX *LeftElevatorTalon;
	//WPI_TalonSRX *RightElevatorTalon;

	std::shared_ptr<Servo> EndEffectorDropServo;

	// TODO: Disable Max and Min
	std::shared_ptr<DigitalInput> MaxHeightLimitSwitch;
	std::shared_ptr<DigitalInput> MinHeightLimitSwitch;

	std::shared_ptr<DigitalInput> HighLimitSwitch;
	std::shared_ptr<DigitalInput> MedLimitSwitch;
	std::shared_ptr<DigitalInput> LowLimitSwitch;

	// Track which limit switch has been recently visited.  Start with 1 from bottom until top limit switch
	int LimitSwitchTracker;

	static constexpr double ElevatorTravelSpeed = 0.20;
	const double StopElevatorSpeed = 0.0;

	int SoftSpeedChangeArrayIterator = 0;

	static const int SoftSpeedChangeArraySize = 75;

	double SoftSpeedChangeArray[SoftSpeedChangeArraySize];

	static constexpr double RaiseSpeedMultiplier = 3.5;
	static constexpr double LowerSpeedMultiplier = 1.0;

	void UpdateSoftSpeedChangeArray(const double Multiplier);
	double SoftStart();
	double SoftStop();

public:
	Elevator();
	void InitDefaultCommand();
	void RaiseElevator();
	void LowerElevator();
	bool GoToSetPoint(int DesiredSetpoint);
	void StopElevator();
	void UpdateLimitSwitchTracker();
};

#endif  // Elevator_H
