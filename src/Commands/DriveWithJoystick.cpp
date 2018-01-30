#include "DriveWithJoystick.h"

DriveWithJoystick::DriveWithJoystick() {
	// Use Requires() here to declare subsystem dependencies
	Requires(Robot::driveTrain.get());
}

// Called just before this Command runs the first time
void DriveWithJoystick::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void DriveWithJoystick::Execute()
{
	Robot::driveTrain.get()->SetDrive(Robot::oi->getXBoxController()->GetRawAxis(XBOX_LEFT_STICK_X_AXIS),
	Robot::oi.get()->getXBoxController()->GetRawAxis(XBOX_LEFT_STICK_Y_AXIS), Robot::oi.get()->getXBoxController()->GetRawAxis(XBOX_RIGHT_STICK_X_AXIS));
}

// Make this return true when this Command no longer needs to run execute()
bool DriveWithJoystick::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void DriveWithJoystick::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveWithJoystick::Interrupted() {

}
