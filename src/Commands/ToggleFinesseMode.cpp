#include "ToggleFinesseMode.h"

ToggleFinesseMode::ToggleFinesseMode() {
	// No exclusive access required to drivetrain subsystem.
	lumberJack.reset(new LumberJack());
}

// Called just before this Command runs the first time
void ToggleFinesseMode::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void ToggleFinesseMode::Execute() {
	lumberJack->iLog("ToggleFinesseMode toggled");
	Robot::driveTrain.get()->ToggleFinesseMode();
}

// Make this return true when this Command no longer needs to run execute()
bool ToggleFinesseMode::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void ToggleFinesseMode::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ToggleFinesseMode::Interrupted() {

}
