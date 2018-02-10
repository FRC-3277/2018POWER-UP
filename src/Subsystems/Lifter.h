/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <Commands/Subsystem.h>
#include "ctre/Phoenix.h"

class Lifter : public frc::Subsystem {
private:
	// Lifter Motor
	std::shared_ptr<WPI_TalonSRX> LifterMotor;

public:
	Lifter();
	void InitDefaultCommand() override;
	void StartLifter();
};

