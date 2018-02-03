#include "RaiseElevator.h"

RaiseElevator::RaiseElevator() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void RaiseElevator::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void RaiseElevator::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool RaiseElevator::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void RaiseElevator::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RaiseElevator::Interrupted() {

}
