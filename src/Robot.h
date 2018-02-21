/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <chrono>
#include <iostream>

#include "LumberJack.h"

#include <Commands/Command.h>
#include <Commands/Scheduler.h>
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SmartDashboard.h>
#include <SmartDashboard/SendableChooser.h>
#include <TimedRobot.h>

#include "OI.h"
// Subsystems
#include "Subsystems/DriveTrain.h"
#include "Subsystems/Elevator.h"
#include "Subsystems/Grabber.h"
#include "Subsystems/Lifter.h"
#include "Subsystems/GameStates.h"
#include "Subsystems/TimeKeeper.h"

// Commands
//#include "Commands/Autonomous.h"
#include "Commands/DriveWithJoystick.h"

class Robot : public frc::TimedRobot
{
public:
	static std::shared_ptr<DriveTrain> driveTrain;
	static std::shared_ptr<Elevator> elevator;
	static std::shared_ptr<Grabber> grabber;
	static std::shared_ptr<Lifter> lifter;
	static std::shared_ptr<GameStates> gamestates;
	static std::shared_ptr<TimeKeeper> timekeeper;
	static std::unique_ptr<OI> oi;

	// Disable subsystems for debugging and testing
	static constexpr bool EnableDriveTrain = true;
	static constexpr bool EnableElevator = true;
	static constexpr bool EnableGrabber = true;
	static constexpr bool EnableLifter = true;

private:
	std::shared_ptr<LumberJack> lumberJack;

	//Autonomous m_autonomousCommand;
	frc::LiveWindow& m_lw = *frc::LiveWindow::GetInstance();

	void RobotInit() override;
	void AutonomousInit() override;
	void AutonomousPeriodic() override;
	void TeleopInit() override;
	void TeleopPeriodic() override;
	void TestPeriodic() override;
	void DisabledInit() override;
	void DisabledPeriodic() override;

	static constexpr int ElapsedSecondsBeforeEnableLifter = 135 - 30;

	// Have it null by default so that if testing teleop it
	// doesn't have undefined behavior and potentially crash.
	frc::Command* m_autonomousCommand = nullptr;
	//ExampleCommand m_defaultAuto;
	//MyAutoCommand m_myAuto;
	frc::SendableChooser<frc::Command*> m_chooser;
};
