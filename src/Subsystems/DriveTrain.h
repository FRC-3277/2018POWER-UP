/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "WPILib.h"
#include <Drive/MecanumDrive.h>
#include <Commands/Subsystem.h>
#include "ctre/Phoenix.h"


class DriveTrain : public frc::Subsystem {
public:
	DriveTrain();
	void InitDefaultCommand() override;
	void SetDrive(double lateral, double forwardBackward, double rotation);

private:
	//Why shared pointers don't work this year?
	std::shared_ptr<WPI_TalonSRX> frontLeftTalon;
	std::shared_ptr<WPI_TalonSRX> frontRightTalon;
	std::shared_ptr<WPI_TalonSRX> rearLeftTalon;
	std::shared_ptr<WPI_TalonSRX> rearRightTalon;

	std::shared_ptr<MecanumDrive> robotDrive;
};
