#include "SpitCubeCommand.h"

SpitCubeCommand::SpitCubeCommand() {
	Requires(Robot::grabber.get());
	lumberJack.reset(new LumberJack());
}

// Called just before this Command runs the first time
void SpitCubeCommand::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void SpitCubeCommand::Execute() {
	Robot::grabber->SetGrabberSpitSpeed(Robot::oi->ScaleAirForceOneAxis(-Robot::oi->GetAirForceOneXAxis()));
	Robot::grabber->SpitCube();
	lumberJack->iLog("SpitCubeCommand", 50);
}

// Make this return true when this Command no longer needs to run execute()
bool SpitCubeCommand::IsFinished() {
	lumberJack->iLog(std::to_string(Robot::grabber->EndSpitCommand));
	return Robot::grabber->EndSpitCommand;
}

// Called once after isFinished returns true
void SpitCubeCommand::End() {
	Robot::grabber->GrabberStop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SpitCubeCommand::Interrupted() {
	Robot::grabber->GrabberStop();
}
