/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "AutonomousDriveCommand.h"
#include "Subsystems/DriveTrain.h"

AutonomousDriveCommand::AutonomousDriveCommand(double lateral, double forwardBackward, double rotation, double AutonomousDriveWaitPeriod) {
	lumberJack.reset(new LumberJack());

	lumberJack->dLog("AutonomousDriveCommand::Initialize");

	Requires(Robot::driveTrain.get());
	this->lateral = lateral;
	this->forwardBackward = forwardBackward;
	this->rotation = rotation;
	this->AutonomousDriveWaitPeriod = AutonomousDriveWaitPeriod;

	AutonomousDriveBegin = std::chrono::system_clock::now();
	AutonomousDriveCurrent = std::chrono::system_clock::now();
}

// Called just before this Command runs the first time
void AutonomousDriveCommand::Initialize() {
	lumberJack->dLog("AutonomousDriveCommand::Initialize");
}

// Called repeatedly when this Command is scheduled to run
void AutonomousDriveCommand::Execute()
{
	AutonomousDriveCurrent = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = AutonomousDriveCurrent - AutonomousDriveBegin;
	int DurationMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_seconds).count();

	while(DurationMilliseconds < AutonomousDriveWaitPeriod)
	{
		AutonomousDriveCurrent = std::chrono::system_clock::now();
		elapsed_seconds = AutonomousDriveCurrent - AutonomousDriveBegin;
		DurationMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_seconds).count();

		lumberJack->dLog("AutonomousDriveCommand elapsed millis: " + std::to_string(DurationMilliseconds) + " : " + std::to_string(AutonomousDriveWaitPeriod));
		if(DurationMilliseconds >= AutonomousDriveWaitPeriod)
		{
			EndAutonomousDriveCommand = true;
			lateral = 0.0;
			forwardBackward = 0.0;
			rotation = 0.0;
		}

		Robot::driveTrain->SetDrive(lateral, forwardBackward, rotation);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool AutonomousDriveCommand::IsFinished() {
	return EndAutonomousDriveCommand;
}

// Called once after isFinished returns true
void AutonomousDriveCommand::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutonomousDriveCommand::Interrupted() {

}
