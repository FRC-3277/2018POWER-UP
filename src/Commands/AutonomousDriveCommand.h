/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <Commands/Command.h>
#include "Robot.h"
#include "LumberJack.h"
#include <chrono>
#include <ctime>

class AutonomousDriveCommand : public frc::Command {

private:
	std::shared_ptr<LumberJack> lumberJack;

	double lateral;
	double forwardBackward;
	double rotation;
	double AutonomousDriveWaitPeriod;

	bool EndAutonomousDriveCommand = false;

	std::chrono::system_clock::time_point AutonomousDriveBegin;
	std::chrono::system_clock::time_point AutonomousDriveCurrent;

public:
	AutonomousDriveCommand(double lateral, double forwardBackward, double rotation, double AutonomousDriveWaitPeriod);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};

