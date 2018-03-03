/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "LifterRunWinchCommand.h"

LifterRunWinchCommand::LifterRunWinchCommand()
{
	Requires(Robot::lifter.get());
}

// Called just before this Command runs the first time
void LifterRunWinchCommand::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void LifterRunWinchCommand::Execute() {
	Robot::lifter->RunTheWinch();
}

// Make this return true when this Command no longer needs to run execute()
bool LifterRunWinchCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void LifterRunWinchCommand::End() {
	Robot::lifter->StopTheWinch();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LifterRunWinchCommand::Interrupted() {
	Robot::lifter->StopTheWinch();
}
