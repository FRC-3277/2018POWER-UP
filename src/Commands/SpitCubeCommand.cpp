#include "SpitCubeCommand.h"

SpitCubeCommand::SpitCubeCommand() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void SpitCubeCommand::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void SpitCubeCommand::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool SpitCubeCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void SpitCubeCommand::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SpitCubeCommand::Interrupted() {

}
