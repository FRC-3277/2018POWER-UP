#include "Elevator.h"
#include "../RobotMap.h"

Elevator::Elevator() : frc::Subsystem("Elevator")
{
	LeftElevatorTalon.reset(new WPI_TalonSRX(ELEVATOR_MOTOR_LEFT_CAN_ID));
	RightElevatorTalon.reset(new WPI_TalonSRX(ELEVATOR_MOTOR_RIGHT_CAN_ID));

	// Confident it is stopped at the beginning.
	LimitSwitchTracker = 1;
	DirectionTraveling = 0;

	MaxHeightLimitSwitch.reset(new DigitalInput(MAX_HEIGHT_LIMIT_SWITCH_ID));
	MinHeightLimitSwitch.reset(new DigitalInput(MAX_HEIGHT_LIMIT_SWITCH_ID));
	HighLimitSwitch.reset(new DigitalInput(HIGH_LIMIT_SWITCH_ID));
	MedLimitSwitch.reset(new DigitalInput(MED_LIMIT_SWITCH_ID));
	LowLimitSwitch.reset(new DigitalInput(LOW_LIMIT_SWITCH_ID));
}

void Elevator::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

void Elevator::RaiseElevator()
{

}
