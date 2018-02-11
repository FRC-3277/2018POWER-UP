/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "LumberJack.h"

#include "WPILib.h"
#include <Drive/MecanumDrive.h>
#include <Commands/Subsystem.h>
#include "ctre/Phoenix.h"
#include <chrono>
#include <ctime>


class DriveTrain : public frc::Subsystem {
public:
	DriveTrain();
	void InitDefaultCommand() override;
	void SetDrive(double lateral, double forwardBackward, double rotation);
	void ToggleFinesseMode();

private:
	std::shared_ptr<LumberJack> lumberJack;

	std::shared_ptr<WPI_TalonSRX> frontLeftTalon;
	std::shared_ptr<WPI_TalonSRX> frontRightTalon;
	std::shared_ptr<WPI_TalonSRX> rearLeftTalon;
	std::shared_ptr<WPI_TalonSRX> rearRightTalon;

	std::shared_ptr<MecanumDrive> robotDrive;

	bool IsFinesseModeEnabled = false;
	double MaxFinesseReduction = 0.5;
	double CurrentFinesseReduction = 0.0;
	double MinFinesseReduction = 0.01;

	std::chrono::system_clock::time_point TimerFinesseBegin;
	std::chrono::system_clock::time_point TimerFinesseCurrent;
	const int	FinesseReductionWaitPeriod = 500;
	const double FinesseIncrementor = 0.05;
};
