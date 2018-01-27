/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "WPILib.h"
#include <Commands/Subsystem.h>
#include "ctre/Phoenix.h"


class DriveTrain : public frc::Subsystem {
public:
	DriveTrain();
	void InitDefaultCommand() override;

private:
	std::shared_ptr<TalonSRX> cANJaguarLeft;
	std::shared_ptr<TalonSRX> cANJaguarRight;
	std::shared_ptr<RobotDrive> robotDrive;

};
