#include "Commands/LowerElevatorCommand.h"

LowerElevatorCommand::LowerElevatorCommand() {
	Requires(Robot::elevator.get());
}

// Called just before this Command runs the first time
void LowerElevatorCommand::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void LowerElevatorCommand::Execute()
{
	if(Robot::elevator->GetInputControlMode())
	{
		Robot::elevator->LowerElevator();
	}
}

// Make this return true when this Command no longer needs to run execute()
bool LowerElevatorCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void LowerElevatorCommand::End()
{
	Robot::elevator->StopElevator();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LowerElevatorCommand::Interrupted()
{
	Robot::elevator->StopElevator();
}
