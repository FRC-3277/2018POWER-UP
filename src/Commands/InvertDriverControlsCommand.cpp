#include "InvertDriverControlsCommand.h"

InvertDriverControlsCommand::InvertDriverControlsCommand() {
	// No exclusive access required to drivetrain subsystem.
	lumberJack.reset(new LumberJack());
}

// Called just before this Command runs the first time
void InvertDriverControlsCommand::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void InvertDriverControlsCommand::Execute() {
	lumberJack->iLog("InvertDriverControlsCommand toggled");

	if(Robot::driveTrain->ToggleInvertDriverControls())
	{
		lumberJack->iLog("Camera Reverse");
		Robot::camera->CameraReverse();
	}
	else
	{
		lumberJack->iLog("Camera Forward");
		Robot::camera->CameraForward();
	}
}

// Make this return true when this Command no longer needs to run execute()
bool InvertDriverControlsCommand::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void InvertDriverControlsCommand::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void InvertDriverControlsCommand::Interrupted() {

}
