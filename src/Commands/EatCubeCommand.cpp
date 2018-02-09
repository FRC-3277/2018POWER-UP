#include "EatCubeCommand.h"

EatCubeCommand::EatCubeCommand() {
	Requires(Robot::grabber.get());
}

// Called just before this Command runs the first time
void EatCubeCommand::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void EatCubeCommand::Execute() {
	Robot::grabber->EatCube();
}

// Make this return true when this Command no longer needs to run execute()
bool EatCubeCommand::IsFinished() {
	return Robot::grabber->EndEatCommand;
}

// Called once after isFinished returns true
void EatCubeCommand::End() {
	Robot::grabber->EndEatCommand = false;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void EatCubeCommand::Interrupted() {
	Robot::grabber->EndEatCommand = false;
}
