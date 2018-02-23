/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#pragma once

#include "LumberJack.h"

#include "WPILib.h"
#include <Buttons/JoystickButton.h>
#include "Controller/Extreme3DPro.h"


#define DRIVER_CONTROLLER_ID 0
#define ALTERNATE_CONTROLLER_ID 1

class OI {
	// TODO: Add Winch In Button - Add limit switch interlock for min
	// TODO: Add Winch Out Button - Add limit switch interlock for max
	// TODO: Add Deploy Mechanism

private:
	std::shared_ptr<LumberJack> lumberJack;

	std::shared_ptr<Joystick> controllerDriver;
	std::shared_ptr<Joystick> AirForceOneController;

	std::shared_ptr<UserDefinedController::Extreme3D_Pro> extreme3dProController;

	std::shared_ptr<JoystickButton> InvertDriverControlsButton;
	std::shared_ptr<JoystickButton> FinesseButton;
	std::shared_ptr<JoystickButton> InjectionButton;
	std::shared_ptr<JoystickButton> EjectionButton;
	std::shared_ptr<JoystickButton> LifterEjectCoreButton;
	std::shared_ptr<JoystickButton> LifterRunWinchButton;
	std::shared_ptr<JoystickButton> ElevatorUpButton;
	std::shared_ptr<JoystickButton> ElevatorDownButton;
	std::shared_ptr<JoystickButton> GoToDesiredElevatorSetpointButton;

	// Use the Joystick when true, Use the xBox controller when false
	bool useJoystick = true;
	bool enableD_PadDebugging;

	// Prevent undesirable behavior in the drivetrain if values fall out of allowed/expected range
	double Clamp(double joystickAxis);

	// Joystick Deadzone
	static constexpr double JoystickDeadzone = 0.02;
	static constexpr double JoystickTwistDeadzone = 0.16;
	static constexpr double XboxTwistDeadzone = 0.135;

	// Deadzone bool values
	bool OverrideXDeadzone = false;
	bool OverrideYDeadzone = false;
	bool OverrideZDeadzone = false;

	// Xbox Deadzone
	static constexpr double XboxDeadzone = 0.13;
	static constexpr double XboxRestingDeadzone = 0.18;

	void CircleDeadZone();

public:
	OI();

	std::shared_ptr<Joystick> GetDriverController();
	double GetJoystickX();
	double GetJoystickY();
	double GetJoystickTwist();
	double GetAirForceOneXAxis();
	double ScaleAirForceOneAxis(double ValueToRescale);
	int GetDesiredElevatorSetpoint();
};
