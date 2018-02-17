/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "LumberJack.h"

#include "WPILib.h"
#include <Commands/Subsystem.h>
#include "ctre/Phoenix.h"

class Lifter : public frc::Subsystem {
private:
	std::shared_ptr<LumberJack> lumberJack;

	// Lifter Motor
	std::shared_ptr<WPI_TalonSRX> LifterMotor;

	std::shared_ptr<Servo> LifterLeftEjectCoreServo;
	std::shared_ptr<Servo> LifterRightEjectCoreServo;

	// When the time comes to launch the lifter it will be the 180 degree opposite of the value of the default
	static constexpr int LeftEjectCoreServoAngleDefault = 180;
	static constexpr int RightEjectCoreServoAngleDefault = 0;

	static constexpr double WinchDefaultSpeed = 0.5;

	bool IsCorePreparedToBeEjected = false;

public:
	Lifter();
	void InitDefaultCommand() override;
	void PrepareLifterCoreForEject();
	void RunTheWinch();
	void StopTheWinch();
};

