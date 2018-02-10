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

/* Xbox Controller Definitions */
#define XBOX_A_BUTTON 1
#define XBOX_B_BUTTON 2
#define XBOX_X_BUTTON 3
#define XBOX_Y_BUTTON 4
#define XBOX_LEFT_SHOLDER_BUTTON 5
#define XBOX_RIGHT_SHOLDER_BUTTON 6
#define XBOX_BACK_BUTTON 7
#define XBOX_START_BUTTON 8
#define XBOX_LEFT_INDEX_TRIGGER 9
#define XBOX_RIGHT_INDEX_TRIGGER 10

#define XBOX_LEFT_STICK_X_AXIS 0
#define XBOX_LEFT_STICK_Y_AXIS 1
#define XBOX_LEFT_TRIGGER_AXIS 2
#define XBOX_RIGHT_TRIGGER_AXIS 3
#define XBOX_RIGHT_STICK_X_AXIS 4
#define XBOX_RIGHT_STICK_Y_AXIS 5

#define DRIVER_CONTROLLER_ID 0
#define ALTERNATE_CONTROLLER_ID 1

/* Logitech EXTREME3DPRO Joystick Definitions */
//TODO: Find IDs for POV
#define JOYSTICK_X_AXIS 0
#define JOYSTICK_Y_AXIS 1
#define JOYSTICK_Z_AXIS 2

#define JOYSTICK_TRIGGER 1
#define JOYSTICK_SLIDER 3

#define JOYSTICK_BUTTON_TWO 2
#define JOYSTICK_BUTTON_THREE 3
#define JOYSTICK_BUTTON_FOUR 4
#define JOYSTICK_BUTTON_FIVE 5
#define JOYSTICK_BUTTON_SIX 6
#define JOYSTICK_BUTTON_SEVEN 7
#define JOYSTICK_BUTTON_EIGHT 8
#define JOYSTICK_BUTTON_NINE 9
#define JOYSTICK_BUTTON_TEN 10
#define JOYSTICK_BUTTON_ELEVEN 11
#define JOYSTICK_BUTTON_TWELVE 12

//Air Force Once
#define AIRFORCEONE_BUTTON_ONE 1
#define AIRFORCEONE_BUTTON_TWO 2
#define AIRFORCEONE_BUTTON_THREE 3
#define AIRFORCEONE_BUTTON_FOUR 4
#define AIRFORCEONE_BUTTON_FIVE 5
#define AIRFORCEONE_BUTTON_SIX 6
#define AIRFORCEONE_BUTTON_SEVEN 7
#define AIRFORCEONE_BUTTON_EIGHT 8
#define AIRFORCEONE_BUTTON_NINE 9
#define AIRFORCEONE_X_AXIS 0
#define AIRFORCEONE_Y_AXIS 1
#define AIRFORCEONE_Z_AXIS 2

// Elevator
#define ElevatorUpButtonNumber JOYSTICK_BUTTON_TWO
#define ElevatorDownButtonNumber JOYSTICK_BUTTON_THREE
#define DesiredElevatorSetpointAxis 4
#define DesiredElevatorSetpointButtonNumber 5

// Grabber
#define ChangeMeInjectionButton 5
#define ChangeMeEjectionButton 6
#define ChangeMeAugmentorTiltUpButton 7
#define ChangeMeAugmentorTiltDownButton 8

#define ChangeMeLifterButton 9

class OI {
	// TODO: Add Winch In Button - Add limit switch interlock for min
	// TODO: Add Winch Out Button - Add limit switch interlock for max
	// TODO: Add Deploy Mechanism


private:
	std::shared_ptr<LumberJack> lumberJack;

	std::shared_ptr<Joystick> controllerDriver;
	std::shared_ptr<Joystick> AirForceOneController;
	std::shared_ptr<JoystickButton> InjectionButton;
	std::shared_ptr<JoystickButton> EjectionButton;
	std::shared_ptr<JoystickButton> AugmentorTiltUpButton;
	std::shared_ptr<JoystickButton> AugmentorTiltDownButton;
	std::shared_ptr<JoystickButton> FinesseButton;
	std::shared_ptr<JoystickButton> LifterButton;
	std::shared_ptr<JoystickButton> ElevatorUpButton;
	std::shared_ptr<JoystickButton> ElevatorDownButton;
	std::shared_ptr<JoystickButton> GoToDesiredElevatorSetpointButton;

	// Joystick button role selection
	int JoystickFinesseButton = JOYSTICK_BUTTON_SEVEN;

	// xBox button role selection
	int XBoxFinnesseButton = XBOX_RIGHT_SHOLDER_BUTTON;
	int XBoxLateral  = XBOX_LEFT_STICK_X_AXIS;
	int XBoxForwardReverse = XBOX_LEFT_STICK_Y_AXIS;
	int XBoxTwist = XBOX_RIGHT_STICK_X_AXIS;

	// Use the Joystick when true, Use the xBox controller when false
	bool useJoystick;
	bool enableD_PadDebugging;

	// Prevent undesirable behavior in the drivetrain if values fall out of allowed/expected range
	double Clamp(double joystickAxis);

	// Joystick Deadzone
	const double JoystickDeadzone = 0.02;

	bool OverrideXDeadzone = false;
	bool OverrideYDeadzone = false;

	// Adding Xbox Deadzone
	const double XboxDeadzone = 0.02;

	bool OverrideXboxXDeadzone = false;
	bool OverrideXboxYDeadzone = false;

public:
	OI();

	std::shared_ptr<Joystick> getXBoxController();
	double GetJoystickX();
	double GetJoystickY();
	double GetJoystickTwist();
	int GetDesiredElevatorSetpoint();
};
