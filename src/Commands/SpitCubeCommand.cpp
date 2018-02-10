#include "SpitCubeCommand.h"

SpitCubeCommand::SpitCubeCommand() {
	Requires(Robot::grabber.get());
}

// Called just before this Command runs the first time
void SpitCubeCommand::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void SpitCubeCommand::Execute() {
	Robot::grabber->SpitCube();
}

// Make this return true when this Command no longer needs to run execute()
bool SpitCubeCommand::IsFinished() {
	return Robot::grabber->EndSpitCommand;
}

// Called once after isFinished returns true
void SpitCubeCommand::End() {
	Robot::grabber->EndSpitCommand = false;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SpitCubeCommand::Interrupted() {
	Robot::grabber->EndSpitCommand = false;
}
