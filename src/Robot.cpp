/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#include "Robot.h"

std::shared_ptr<DriveTrain> Robot::driveTrain;
std::shared_ptr<Elevator> Robot::elevator;
std::shared_ptr<Grabber> Robot::grabber;
std::shared_ptr<Lifter> Robot::lifter;
std::shared_ptr<GameStates> Robot::gamestates;
std::unique_ptr<OI> Robot::oi;

void Robot::RobotInit()
{
	//m_chooser.AddDefault("Default Auto", &m_defaultAuto);
	//m_chooser.AddObject("My Auto", &m_myAuto);

	// Smart Dashboard
	frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
	SmartDashboard::PutBoolean("Drive With Joystick? 0", true);
	SmartDashboard::PutBoolean("Drive With XBox Controller? 1", false);

	try
	{
		if(EnableDriveTrain)
		{
			lumberJack->dLog("DriveTrain Subsystem Started");
			driveTrain.reset(new DriveTrain());
		}
	}
	catch(const std::exception& e)
	{
		lumberJack->eLog(std::string("driveTrain.reset() failed; ") + std::string(e.what()));
	}

	try
	{
		if(EnableGrabber)
		{
			lumberJack->dLog("Grabber Subsystem Started");
			grabber.reset(new Grabber());
		}
	}
	catch(const std::exception& e)
	{
		lumberJack->eLog(std::string("grabber.reset() failed; ") + std::string(e.what()));
	}

	try
	{
		if(EnableElevator)
		{
			lumberJack->dLog("Elevator Subsystem Started");
			elevator.reset(new Elevator());
		}
	}
	catch(const std::exception& e)
	{
		lumberJack->eLog(std::string("elevator.reset() failed; ") + std::string(e.what()));
	}

	try
	{
		if(EnableLifter)
		{
			lumberJack->dLog("Lifter Subsystem Started");
			lifter.reset(new Lifter());
		}
	}
	catch(const std::exception& e)
	{
		lumberJack->eLog(std::string("lifter.reset() failed; ") + std::string(e.what()));
	}

	try
	{
		lumberJack->dLog("GameStates Started");
		gamestates.reset(new GameStates());
	}
	catch(const std::exception& e)
	{
		lumberJack->eLog(std::string("gamestates.reset() failed; ") + std::string(e.what()));
	}

	// This MUST be here. If the OI creates Commands (which it very likely
	// will), constructing it during the construction of CommandBase (from
	// which commands extend), subsystems are not guaranteed to be
	// yet. Thus, their requires() statements may grab null pointers. Bad
	// news. Don't move it.
	try
	{
		lumberJack->dLog("OI Started");
		oi.reset(new OI());
	}
	catch(const std::exception& e)
	{
		lumberJack->eLog(std::string("oi.reset() failed; ") + std::string(e.what()));
	}
}

/**
 * This function is called once each time the robot enters Disabled
 * mode.
 * You can use it to reset any subsystem information you want to clear
 * when
 * the robot is disabled.
 */
void Robot::DisabledInit() {}

void Robot::DisabledPeriodic()
{
	frc::Scheduler::GetInstance()->Run();
}

/**
 * This autonomous (along with the chooser code above) shows how to
 * select
 * between different autonomous modes using the dashboard. The sendable
 * chooser code works with the Java SmartDashboard. If you prefer the
 * LabVIEW Dashboard, remove all of the chooser code and uncomment the
 * GetString code to get the auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional commands to
 * the
 * chooser code above (like the commented example) or additional
 * comparisons
 * to the if-else structure below with additional strings & commands.
 */
void Robot::AutonomousInit()
{
	std::string autoSelected = frc::SmartDashboard::GetString(
			"Auto Selector", "Default");
	if (autoSelected == "My Auto") {
		//m_autonomousCommand = &m_myAuto;
	} else {
		//m_autonomousCommand = &m_defaultAuto;
	}

	m_autonomousCommand = m_chooser.GetSelected();

	if (m_autonomousCommand != nullptr) {
		m_autonomousCommand->Start();
	}
}

void Robot::AutonomousPeriodic()
{
	gamestates->GetGameData();
	if(EnableElevator)
	{
		elevator->UpdateLimitSwitchTracker();
	}
	frc::Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit()
{
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to
	// continue until interrupted by another command, remove
	// this line or comment it out.
	if (m_autonomousCommand != nullptr)
	{
		m_autonomousCommand->Cancel();
		m_autonomousCommand = nullptr;
	}
}

void Robot::TeleopPeriodic()
{
	if(EnableElevator)
	{
		elevator->HoldElevator();
		elevator->UpdateLimitSwitchTracker();
	}
	frc::Scheduler::GetInstance()->Run();
}

void Robot::TestPeriodic() {}

START_ROBOT_CLASS(Robot)
