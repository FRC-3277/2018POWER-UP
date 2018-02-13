/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include "I2C.h"
#include <Commands/Subsystem.h>

class ShowTimeRIOduino : public frc::Subsystem {
private:
	std::shared_ptr<I2C> I2C_Coms;

	int I2C_Channel = 4;

	void ShowTimeRIOduino::Alive();


public:
	ShowTimeRIOduino();
	void InitDefaultCommand() override;
};

