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
	// Selecting Joystick overrides xBox in case both are found enabled
	useJoystick = SmartDashboard::GetBoolean("Drive With Joystick? 0", false);
	if(useJoystick == false)
	{
		// Force useJoystick true if use xBox not set to true
		if(SmartDashboard::GetBoolean("Drive With XBox Controller? 1", false) == false)
		{
			useJoystick = true;
		}
	}

	enableD_PadDebugging = false;

	controllerDriver.reset(new Joystick(DRIVER_CONTROLLER_ID));

	if(useJoystick)
	{
		FinesseButton.reset(new JoystickButton(controllerDriver.get(), JoystickFinesseButton));
	}
	else
	{
		FinesseButton.reset(new JoystickButton(controllerDriver.get(), XBoxFinnesseButton));
	}

	FinesseButton->ToggleWhenPressed(new ToggleFinesseMode());
}

double OI::GetJoystickX()
{
	double x = 0.0;

	if(useJoystick)
	{
		x = controllerDriver->GetX();

		//Adding deadzone for X axis
		if(fabs(controllerDriver->GetX() <= 2 && controllerDriver->GetY() > controllerDriver->GetX()))
		{
				x = 0.0;
		}
		else{
			x = controllerDriver->GetX();
		}
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
			controllerDriver->GetRawAxis(XBoxLateral);
		}
	}

	return Clamp(x);
}

double OI::GetJoystickY()
{
	double y = 0.0;

	if(useJoystick)
	{
		y = controllerDriver->GetY();

		//Adding deadzone for Y axis
		if(fabs(controllerDriver->GetY() <= 2 && controllerDriver->GetX() > controllerDriver->GetY()))
		{
			y = 0.0;
		}
		else
		{
			y = controllerDriver->GetY();
		}
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
			controllerDriver->GetRawAxis(XBoxForwardReverse);
		}
	}

	return Clamp(y);
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
		controllerDriver->GetRawAxis(XBoxTwist);
	}

	return Clamp(rotation);
}

double OI::Clamp(double joystickAxis)
{
	if(joystickAxis <= -1)
	{
		joystickAxis = -0.999;
	}
	else if(joystickAxis >= 1)
	{
		joystickAxis = 0.999;
	}

	return joystickAxis;
}
