#include "AutonomousElevatorToSetpointCommand.h"

AutonomousElevatorToSetpointCommand::AutonomousElevatorToSetpointCommand(int DesiredSetpoint)
{
	Requires(Robot::elevator.get());
	this->DesiredSetpoint = DesiredSetpoint;
}

// Called just before this Command runs the first time
void AutonomousElevatorToSetpointCommand::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void AutonomousElevatorToSetpointCommand::Execute()
{
	Robot::elevator->GoToSetPoint(DesiredSetpoint);
}

// Make this return true when this Command no longer needs to run execute()
bool AutonomousElevatorToSetpointCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void AutonomousElevatorToSetpointCommand::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutonomousElevatorToSetpointCommand::Interrupted() {

}
