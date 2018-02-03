/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#pragma once

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


#define ChangeMeFinesseButton 4

class OI {

private:
	std::shared_ptr<Joystick> xBoxControllerDriver;
	std::shared_ptr<JoystickButton> FinesseButton;

public:
	OI();

	std::shared_ptr<Joystick> getXBoxController();
};
