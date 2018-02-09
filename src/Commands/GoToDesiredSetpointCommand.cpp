#include <Commands/GoToDesiredSetpointCommand.h>

GoToDesiredSetpointCommand::GoToDesiredSetpointCommand() {
	Requires(Robot::elevator.get());
}

// Called just before this Command runs the first time
void GoToDesiredSetpointCommand::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void GoToDesiredSetpointCommand::Execute()
{
	IsAtDesiredSetpoint = Robot::elevator->GoToSetPoint(Robot::oi->GetDesiredElevatorSetpoint());
}

// Make this return true when this Command no longer needs to run execute()
bool GoToDesiredSetpointCommand::IsFinished()
{
	return IsAtDesiredSetpoint;
}

// Called once after isFinished returns true
void GoToDesiredSetpointCommand::End()
{
	Robot::elevator->StopElevator();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void GoToDesiredSetpointCommand::Interrupted()
{
	Robot::elevator->StopElevator();
}
