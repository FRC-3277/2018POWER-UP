/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"
#include "WPILib.h"
#include "Commands/ToggleFinesseMode.h"

OI::OI()
{
	xBoxControllerDriver.reset(new Joystick(DRIVER_CONTROLLER_ID));
	FinesseButton.reset(new JoystickButton(xBoxControllerDriver.get(), JoystickFinesseButton));


	FinesseButton->ToggleWhenPressed(new ToggleFinesseMode());
}

double OI::GetJoystickX()
{
	return xBoxControllerDriver->GetX();
}

double OI::GetJoystickY()
{
	return xBoxControllerDriver->GetY();
}

double OI::GetJoystickTwist()
{
	// The direction turned is CW for negative and CCW for positive.
	double rotation = xBoxControllerDriver->GetTwist() * -1.0;
	return rotation;
}
