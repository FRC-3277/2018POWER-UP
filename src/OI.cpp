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
	// TODO: Identify where the actual value will come from in the Driver Station.
	useJoystick = false;
	enableD_PadDebugging = false;

	controllerDriver.reset(new Joystick(DRIVER_CONTROLLER_ID));
	FinesseButton.reset(new JoystickButton(controllerDriver.get(), JoystickFinesseButton));


	FinesseButton->ToggleWhenPressed(new ToggleFinesseMode());
}

double OI::GetJoystickX()
{
	double x = 0.0;

	if(useJoystick)
	{
		x = controllerDriver->GetX();
	}
	else
	{
		if(enableD_PadDebugging)
		{
			if(controllerDriver->GetPOV() <= 90 + 15 && controllerDriver->GetPOV() >= 90 - 15)
			{
				x = 0.5;
			}
			else if(controllerDriver->GetPOV() <= 270 + 15 && controllerDriver->GetPOV() >= 270 - 15)
			{
				x = -0.5;
			}
		}
		else
		{
			//TODO: Actual xBox controller
		}
	}

	return x;
}

double OI::GetJoystickY()
{
	double y = 0.0;

	if(useJoystick)
	{
		y = controllerDriver->GetY();
	}
	else
	{
		if(enableD_PadDebugging)
		{
			if(controllerDriver->GetPOV() <= 0 + 15 && controllerDriver->GetPOV() >= 360 - 15)
			{
				y = -0.5;
			}
			else if(controllerDriver->GetPOV() <= 180 + 15 && controllerDriver->GetPOV() >= 180 - 15)
			{
				y = 0.5;
			}
		}
		else
		{
			//TODO: Actual xBox controller
		}
	}

	return y;
}

double OI::GetJoystickTwist()
{
	double rotation = 0.0;

	if(useJoystick)
	{
		// The direction turned is CW for negative and CCW for positive.
		rotation = controllerDriver->GetTwist() * -1.0;
	}
	else
	{
		//TODO: Actual xBox controller
	}

	return rotation;
}
