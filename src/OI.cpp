/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"
#include "WPILib.h"
#include "Commands/ToggleFinesseMode.h"
#include "Commands/AugmentorTiltDownCommand.h"
#include "Commands/AugmentorTiltUpCommand.h"
#include "Commands/EatCubeCommand.h"
#include "Commands/SpitCubeCommand.h"

#include <math.h>

#include <Commands/LowerElevatorCommand.h>
#include <Commands/RaiseElevatorCommand.h>
#include <Commands/GoToDesiredSetpointCommand.h>


OI::OI()
{
	controllerDriver.reset(new Joystick(DRIVER_CONTROLLER_ID));
	AirForceOneController.reset(new Joystick(ALTERNATE_CONTROLLER_ID));

	InjectionButton.reset(new JoystickButton(controllerDriver.get(), ChangeMeInjectionButton));
	EjectionButton.reset(new JoystickButton(controllerDriver.get(), ChangeMeEjectionButton));
	AugmentorTiltUpButton.reset(new JoystickButton(controllerDriver.get(), ChangeMeAugmentorTiltUpButton));
	AugmentorTiltDownButton.reset(new JoystickButton(controllerDriver.get(), ChangeMeAugmentorTiltDownButton));

	ElevatorUpButton.reset(new JoystickButton(controllerDriver.get(), ElevatorUpButtonNumber));
	ElevatorDownButton.reset(new JoystickButton(controllerDriver.get(), ElevatorDownButtonNumber));

	InjectionButton->WhenPressed(new EatCubeCommand());
	EjectionButton->WhenPressed(new SpitCubeCommand());
	AugmentorTiltUpButton->WhenPressed(new AugmentorTiltUpCommand());
	AugmentorTiltDownButton->WhenPressed(new AugmentorTiltDownCommand());

	// Button trigger and command mappings
	ElevatorUpButton->WhenPressed(new RaiseElevatorCommand());
	ElevatorDownButton->WhenPressed(new LowerElevatorCommand());
	GoToDesiredElevatorSetpointButton->WhenPressed(new GoToDesiredSetpointCommand());

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

std::shared_ptr<Joystick> OI::getXBoxController()
{
	return controllerDriver;
}

double OI::GetJoystickX()
{
	double x = 0.0;

	if(useJoystick)
	{
		//Adding deadzone for X axis
		if(controllerDriver->GetY() <= JoystickDeadzone
			 && controllerDriver->GetY() >= -JoystickDeadzone
			 && fabs(controllerDriver->GetY()) > fabs(controllerDriver->GetX()))
		{
				OverrideYDeadzone = true;
		}
		else
		{
				OverrideYDeadzone = false;
		}

		if(OverrideXDeadzone)
		{
			x = 0.0;
		}
		else
		{
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

			//Adding Xboxdeadzone for X axis
			if(controllerDriver->GetRawAxis(XBoxForwardReverse) <= XboxDeadzone
				 && controllerDriver->GetRawAxis(XBoxForwardReverse) >= -XboxDeadzone
				 && fabs(controllerDriver->GetRawAxis(XBoxForwardReverse)) > fabs(controllerDriver->GetRawAxis(XBoxLateral)))
			{
					OverrideXboxYDeadzone = true;
			}
			else
			{
					OverrideXboxYDeadzone = false;
			}

			if(OverrideXboxXDeadzone)
			{
				x = 0.0;
			}
			else
			{
				x = controllerDriver->GetRawAxis(XBoxLateral);
			}
		}
	}

	return Clamp(x);
}

double OI::GetJoystickY()
{
	double y = 0.0;

	if(useJoystick)
	{
		//Adding deadzone for Y axis
		if(controllerDriver->GetX() <= JoystickDeadzone
			&& controllerDriver->GetX() >= -JoystickDeadzone
			&& fabs(controllerDriver->GetX()) > fabs(controllerDriver->GetY()))
		{
			OverrideXDeadzone = true;
		}
		else
		{
			OverrideXDeadzone = false;
		}

		if(OverrideYDeadzone)
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
			//Adding Xboxdeadzone for Y axis
			if(controllerDriver->GetRawAxis(XBoxLateral) <= XboxDeadzone
				 && controllerDriver->GetRawAxis(XBoxLateral) >= -XboxDeadzone
				 && fabs(controllerDriver->GetRawAxis(XBoxLateral)) > fabs(controllerDriver->GetRawAxis(XBoxForwardReverse)))
			{
					OverrideXboxYDeadzone = true;
			}
			else
			{
					OverrideXboxYDeadzone = false;
			}

			if(OverrideXboxXDeadzone)
			{
				y = 0.0;
			}
			else
			{
				y = controllerDriver->GetRawAxis(XBoxForwardReverse);
			}
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

int OI::GetDesiredElevatorSetpoint()
{
	int DesiredSetpoint = 1;
	int NumberOfElevatorLimitSwitches = 5;
	double SetPointDelimiterValue = 0.99/NumberOfElevatorLimitSwitches;
	double CurrentActualElevatorSetpointControllerValue = AirForceOneController->GetRawAxis(DesiredElevatorSetpointAxis);

	DesiredSetpoint = round(CurrentActualElevatorSetpointControllerValue/SetPointDelimiterValue);

	if(DesiredSetpoint == 0)
	{
		DesiredSetpoint = 1;
	}

	return DesiredSetpoint;
}
