/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "AutonomousSpitCubeCommand.h"

AutonomousSpitCubeCommand::AutonomousSpitCubeCommand() {
	Requires(Robot::grabber.get());
}

// Called just before this Command runs the first time
void AutonomousSpitCubeCommand::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void AutonomousSpitCubeCommand::Execute() {
	Robot::grabber->SpitCube();
}

// Make this return true when this Command no longer needs to run execute()
bool AutonomousSpitCubeCommand::IsFinished() {
	return Robot::grabber->EndSpitCommand;;
}

// Called once after isFinished returns true
void AutonomousSpitCubeCommand::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutonomousSpitCubeCommand::Interrupted() {

}
