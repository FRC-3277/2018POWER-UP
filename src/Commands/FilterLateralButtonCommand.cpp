/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/FilterLateralButtonCommand.h"

FilterLateralButtonCommand::FilterLateralButtonCommand()
{

	lumberJack.reset(new LumberJack());
}

// Called just before this Command runs the first time
void FilterLateralButtonCommand::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void FilterLateralButtonCommand::Execute() {
	lumberJack->iLog("FilterLateralButton toggled");
	//ignore Eclipse if this indicates an error in the IDE
	Robot::driveTrain->FilterLateral();
}

// Make this return true when this Command no longer needs to run execute()
bool FilterLateralButtonCommand::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void FilterLateralButtonCommand::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void FilterLateralButtonCommand::Interrupted() {

}
