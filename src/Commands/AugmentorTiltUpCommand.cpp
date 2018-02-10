#include "Commands/AugmentorTiltUpCommand.h"

AugmentorTiltUpCommand::AugmentorTiltUpCommand() {
	Requires(Robot::grabber.get());
}

// Called just before this Command runs the first time
void AugmentorTiltUpCommand::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void AugmentorTiltUpCommand::Execute() {
	Robot::grabber->AugmentorTiltUp();
}

// Make this return true when this Command no longer needs to run execute()
bool AugmentorTiltUpCommand::IsFinished() {
	return Robot::grabber->EndAugmentorTiltUpCommand;
}

// Called once after isFinished returns true
void AugmentorTiltUpCommand::End() {
	Robot::grabber->EndAugmentorTiltUpCommand = false;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AugmentorTiltUpCommand::Interrupted() {
	Robot::grabber->EndAugmentorTiltUpCommand = false;
}
