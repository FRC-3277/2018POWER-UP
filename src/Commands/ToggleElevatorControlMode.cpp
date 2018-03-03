/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/ToggleElevatorControlMode.h"

ToggleElevatorControlMode::ToggleElevatorControlMode()
{
	Requires(Robot::elevator.get());
}

// Called just before this Command runs the first time
void ToggleElevatorControlMode::Initialize()
{
	printf("ToggleElevatorControlMode");
	Robot::elevator->ToggleInputControlMode();
}

// Called repeatedly when this Command is scheduled to run
void ToggleElevatorControlMode::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool ToggleElevatorControlMode::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void ToggleElevatorControlMode::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ToggleElevatorControlMode::Interrupted() {

}
