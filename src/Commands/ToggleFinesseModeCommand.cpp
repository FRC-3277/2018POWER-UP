#include <Commands/ToggleFinesseModeCommand.h>

ToggleFinesseModeCommand::ToggleFinesseModeCommand() {
	// No exclusive access required to drivetrain subsystem.
	lumberJack.reset(new LumberJack());
}

// Called just before this Command runs the first time
void ToggleFinesseModeCommand::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void ToggleFinesseModeCommand::Execute() {
	lumberJack->iLog("ToggleFinesseMode toggled");
	Robot::driveTrain->ToggleFinesseMode();
}

// Make this return true when this Command no longer needs to run execute()
bool ToggleFinesseModeCommand::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void ToggleFinesseModeCommand::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ToggleFinesseModeCommand::Interrupted() {

}
