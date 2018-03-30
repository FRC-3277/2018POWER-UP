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
#include "Controller/AssignedController.h"

class OI {
	// TODO: Add Winch In Button - Add limit switch interlock for min
	// TODO: Add Winch Out Button - Add limit switch interlock for max
	// TODO: Add Deploy Mechanism

private:
	std::shared_ptr<LumberJack> lumberJack;
	std::shared_ptr<UserDefinedController::AssignedController> assignedController;
	std::shared_ptr<Joystick> firstPlayerController;
	std::shared_ptr<Joystick> secondPlayerController;
	std::shared_ptr<Joystick> thirdPlayerController;

	std::shared_ptr<JoystickButton> EjectionButton;
	std::shared_ptr<JoystickButton> ElevatorDownButton;
	std::shared_ptr<JoystickButton> ElevatorUpButton;
	std::shared_ptr<JoystickButton> FinesseButton;
	std::shared_ptr<JoystickButton> InjectionButton;
	std::shared_ptr<JoystickButton> InvertDriverControlsButton;
	std::shared_ptr<JoystickButton> LifterEjectCoreButton;
	std::shared_ptr<JoystickButton> LifterRunWinchButton;
	std::shared_ptr<JoystickButton> ToggleElevatorControlModeButton;
	std::shared_ptr<JoystickButton> FilterLateralButton;

	// Buttons and axis are mapped via a unique string
	// Axis
	std::string LateralAxisId = std::string("LateralAxisId");
	std::string TwistAxisId = std::string("TwistAxisId");
	std::string ForwardReverseAxisId = std::string("ForwardReverseAxisId");
	std::string GoToDesiredElevatorSetpointAxisId = std::string("GoToDesiredElevatorSetpointAxisId");
	std::string GrabberSpeedControlAxisId = std::string("GrabberSpeedControlAxisId");

	// Buttons
	std::string ElevatorDownButtonId = std::string("ElevatorDownButtonId");
	std::string ElevatorUpButtonId = std::string("ElevatorUpButtonId");
	std::string GrabberEjectionButtonId = std::string("GrabberEjectionButtonId");
	std::string GrabberInjectionButtonId = std::string("GrabberInjectionButtonId");
	std::string InvertDriverControlsButtonId = std::string("InvertDriverControlsButtonId");
	std::string JoystickFinesseButtonId = std::string("JoystickFinesseButtonId");
	std::string FilterLateralButtonId = std::string("FilterLateralButtonId");
	std::string LifterPrepareCoreEjectionButtonId = std::string("LifterPrepareCoreEjectionButtonId");
	std::string LifterRunWinchButtonId = std::string("LifterRunWinchButtonId");
	std::string ToggleElevatorControlModeId = std::string("ToggleElevatorControlModeId");

	/*
	 * To ensure consistency the controllers must be mapped to a slot in the driver station.
	 * If there was a way to inspect the controller type by USB device info this could be dynamic.
	 * //TODO: Possible feature request for wpilib?
	 */
	static constexpr int EXTREME3D_PRO_CONTROLLER_ID = 0;
	static constexpr int AIRFORCEONE_CONTROLLER_ID = 1;
	static constexpr int XBOX_CONTROLLER_ID = 2;

	/*
	 * Assigned controller configuration
	 * 0 - Just the Extreme3D_Pro joystick
	 * 1 - Just the XBox controller
	 * 2 - Extreme3D_Pro as firstPlayerController with main role of driver with AirforceOne as secondPlayerController playing support role //TODO: add additional info here
	 * 3 - Extreme3D_Pro as firstPlayerController with main role of driver with AirforceOne as secondPlayerController and XBox as thirdPlayerController playing support role //TODO: add additional info here
	 */
	static constexpr int PlayerControllerConfigurationMode = 2;

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

	double GetJoystickX();
	double GetJoystickY();
	double GetJoystickTwist();
	double GetAirForceOneXAxis();
	double ScaleAirForceOneAxis(double ValueToRescale);
	int GetDesiredElevatorSetpoint();
};
