#ifndef Elevator_H
#define Elevator_H

#include "WPILib.h"
#include "ctre/Phoenix.h"
#include <Commands/Subsystem.h>

class Elevator : public frc::Subsystem {
private:
	std::shared_ptr<WPI_TalonSRX> LeftElevatorTalon;
	std::shared_ptr<WPI_TalonSRX> RightElevatorTalon;

	std::shared_ptr<DigitalInput> MaxHeightLimitSwitch;
	std::shared_ptr<DigitalInput> MinHeightLimitSwitch;

	std::shared_ptr<DigitalInput> HighLimitSwitch;
	std::shared_ptr<DigitalInput> MedLimitSwitch;
	std::shared_ptr<DigitalInput> LowLimitSwitch;

	// Track which limit switch has been recently visited.  Start with 1 from bottom until top limit switch
	int LimitSwitchTracker;
	// Track which direction the elevator is traveling.  O for Stopped,  1 for Up, 2 for Down
	int DirectionTraveling;

	const double ElevatorTravelSpeed = 0.25;

	void RaiseElevator();
	void LowerElevator();
	int UpdateDirectionTravelling(int DirectionCurrentlyTravelling);
	int UpdateLimitSwitchTracker(int LimitSwitchTrackerCurrentValue);


public:
	Elevator();
	void InitDefaultCommand();
};

#endif  // Elevator_H
