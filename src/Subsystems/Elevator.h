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

	std::shared_ptr<DigitalInput> MaxHeightLimitSwitch;
	std::shared_ptr<DigitalInput> MinHeightLimitSwitch;

	std::shared_ptr<DigitalInput> HighLimitSwitch;
	std::shared_ptr<DigitalInput> MedLimitSwitch;
	std::shared_ptr<DigitalInput> LowLimitSwitch;

	// Track which limit switch has been recently visited.  Start with 1 from bottom until top limit switch
	int LimitSwitchTracker;

	const double ElevatorTravelSpeed = 0.25;
	const double StopElevatorSpeed = 0.0;

	void UpdateLimitSwitchTracker();

public:
	Elevator();
	void InitDefaultCommand();
	void RaiseElevator();
	void LowerElevator();
	bool GoToSetPoint(int DesiredSetpoint);
	void StopElevator();
};

#endif  // Elevator_H
