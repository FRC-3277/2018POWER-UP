#include "AutonomousScenarios.h"

AutonomousScenarios::AutonomousScenarios()
{
}

// Called just before this Command runs the first time
void AutonomousScenarios::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void AutonomousScenarios::Execute() {

/** g-code language (Subject to change)
 * D(forward/backwards) = Drive forwards/backwards
 * T(rotation) = Turn; Positive for Right and Negative for Left
 * L(lateral) = Lateral; Positive for Right and Negative for Left
 * S = Stop Everything
 * ER = Raise Elevator
 * EL = Lower Elevator
 * E(setpoint) = Go to Elevator Preset
 * GE = Eat Cube
 * GS = Spit Cube
 */

}

// Make this return true when this Command no longer needs to run execute()
bool AutonomousScenarios::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void AutonomousScenarios::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutonomousScenarios::Interrupted() {

}
