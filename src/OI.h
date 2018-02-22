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

	std::shared_ptr<JoystickButton> InvertDriverControlsButton;
	std::shared_ptr<JoystickButton> FinesseButton;
	std::shared_ptr<JoystickButton> InjectionButton;
	std::shared_ptr<JoystickButton> EjectionButton;
	std::shared_ptr<JoystickButton> LifterEjectCoreButton;
	std::shared_ptr<JoystickButton> LifterRunWinchButton;
	std::shared_ptr<JoystickButton> ElevatorUpButton;
	std::shared_ptr<JoystickButton> ElevatorDownButton;
	std::shared_ptr<JoystickButton> GoToDesiredElevatorSetpointButton;

	// Joystick button role selection
	static constexpr int JoystickFinesseButton = JOYSTICK_BUTTON_SEVEN;
	// Drivetrain
	static constexpr int InvertDriverControlsButtonNumber = JOYSTICK_BUTTON_TWELVE;

	// Elevator
	static constexpr int ElevatorUpButtonNumber = JOYSTICK_BUTTON_TWO;
	static constexpr int ElevatorDownButtonNumber = JOYSTICK_BUTTON_THREE;
	static constexpr int ToggleElevatorControlMode = AIRFORCEONE_BUTTON_FIVE;
	static constexpr int DesiredElevatorSetpointAxisNumber = AIRFORCEONE_Z_AXIS;
	//static constexpr int DesiredElevatorSetpointButtonNumber = JOYSTICK_BUTTON_FOUR;

	// Grabber
	static constexpr int GrabberInjectionButtonNumber = AIRFORCEONE_BUTTON_ONE;
	static constexpr int GrabberEjectionButtonNumber = AIRFORCEONE_BUTTON_TWO;
	// Not actually mapped to Controller, but in use
	static constexpr int GrabberSpitCubeLeverAxisNumber = AIRFORCEONE_X_AXIS;

	// Lifter
	static constexpr int LifterPrepareCoreEjectionButtonNumber = JOYSTICK_BUTTON_TEN;
	static constexpr int LifterRunWinchButtonNumber = JOYSTICK_BUTTON_ELEVEN;

	// xBox button role selection
	static constexpr int XBoxFinnesseButtonNumber = XBOX_RIGHT_SHOLDER_BUTTON;
	static constexpr int XBoxLateralAxisNumber  = XBOX_LEFT_STICK_X_AXIS;
	static constexpr int XBoxForwardReverseAxisNumber = XBOX_LEFT_STICK_Y_AXIS;
	static constexpr int XBoxTwistAxisNumber = XBOX_RIGHT_STICK_X_AXIS;

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
