#include "Commands/AugmentorTiltDownCommand.h"

AugmentorTiltDownCommand::AugmentorTiltDownCommand() {
	Requires(Robot::grabber.get());
}

// Called just before this Command runs the first time
void AugmentorTiltDownCommand::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void AugmentorTiltDownCommand::Execute() {
	Robot::grabber->AugmentorTiltDown();
}

// Make this return true when this Command no longer needs to run execute()
bool AugmentorTiltDownCommand::IsFinished() {
	return Robot::grabber->EndAugmentorTiltDownCommand;
}

// Called once after isFinished returns true
void AugmentorTiltDownCommand::End() {
	Robot::grabber->EndAugmentorTiltDownCommand = false;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AugmentorTiltDownCommand::Interrupted() {
	Robot::grabber->EndAugmentorTiltDownCommand = false;
}
