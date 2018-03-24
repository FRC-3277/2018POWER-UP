#include "Commands/GoToDesiredPositionCommand.h"

GoToDesiredPositionCommand::GoToDesiredPositionCommand() {
	Requires(Robot::elevator.get());
}

// Called just before this Command runs the first time
void GoToDesiredPositionCommand::Initialize()
{
}

// Called repeatedly when this Command is scheduled to run
void GoToDesiredPositionCommand::Execute()
{
	Robot::elevator->GoToSetPosition(Robot::oi->GetDesiredElevatorPosition());
}

// Make this return true when this Command no longer needs to run execute()
bool GoToDesiredPositionCommand::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void GoToDesiredPositionCommand::End()
{
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void GoToDesiredPositionCommand::Interrupted()
{
}
