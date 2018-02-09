#include <Commands/RaiseElevatorCommand.h>

RaiseElevatorCommand::RaiseElevatorCommand() {
	Requires(Robot::elevator.get());
}

// Called just before this Command runs the first time
void RaiseElevatorCommand::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void RaiseElevatorCommand::Execute()
{
	Robot::elevator->RaiseElevator();
}

// Make this return true when this Command no longer needs to run execute()
bool RaiseElevatorCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void RaiseElevatorCommand::End()
{
	Robot::elevator->StopElevator();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RaiseElevatorCommand::Interrupted()
{
	Robot::elevator->StopElevator();
}
