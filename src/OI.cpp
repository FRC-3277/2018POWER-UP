/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#include <string>

#include <math.h>

#include "OI.h"
#include "WPILib.h"
#include "Commands/EatCubeCommand.h"
#include "Commands/SpitCubeCommand.h"
#include "Commands/StartLifterCommand.h"
#include "Commands/InvertDriverControlsCommand.h"
#include "Commands/LowerElevatorCommand.h"
#include "Commands/RaiseElevatorCommand.h"
#include "Commands/GoToDesiredSetpointCommand.h"
#include "Commands/ToggleFinesseModeCommand.h"

OI::OI()
{
	// Controllers
	lumberJack->dLog("Assigning controllers");
	try
	{
		controllerDriver.reset(new Joystick(DRIVER_CONTROLLER_ID));
	}
	catch(const std::exception& e)
	{
		lumberJack->eLog(std::string("controllerDriver.reset() failed; ") + std::string(e.what()));
	}

	try
	{
		AirForceOneController.reset(new Joystick(ALTERNATE_CONTROLLER_ID));
	}
	catch(const std::exception& e)
	{
		lumberJack->eLog(std::string("AirForceOneController.reset() failed; ") + std::string(e.what()));
	}

	// Buttons and commands
	lumberJack->dLog("Assigning buttons and commands");
	//	GRABBER
	if(Robot::EnableGrabber)
	{
		try
		{
			InjectionButton.reset(new JoystickButton(AirForceOneController.get(), GrabberInjectionButtonNumber));
			InjectionButton->WhileHeld(new EatCubeCommand());
		}
		catch(const std::exception& e)
		{
			lumberJack->eLog(std::string("InjectionButton.reset() failed; ") + std::string(e.what()));
		}

		try
		{
			EjectionButton.reset(new JoystickButton(AirForceOneController.get(), GrabberEjectionButtonNumber));
			EjectionButton->WhileHeld(new SpitCubeCommand());
		}
		catch(const std::exception& e)
		{
			lumberJack->eLog(std::string("EjectionButton.reset() failed; ") + std::string(e.what()));
		}
	}

	//	ELEVATOR
	if(Robot::EnableElevator)
	{
		try
		{
			ElevatorUpButton.reset(new JoystickButton(controllerDriver.get(), ElevatorUpButtonNumber));
			ElevatorUpButton->WhileHeld(new RaiseElevatorCommand());
		}
		catch(const std::exception& e)
		{
			lumberJack->eLog(std::string("ElevatorUpButton.reset() failed; ") + std::string(e.what()));
		}

		try
		{
			ElevatorDownButton.reset(new JoystickButton(controllerDriver.get(), ElevatorDownButtonNumber));
			ElevatorDownButton->WhileHeld(new LowerElevatorCommand());
		}
		catch(const std::exception& e)
		{
			lumberJack->eLog(std::string("ElevatorDownButton.reset() failed; ") + std::string(e.what()));
		}

		try
		{
			GoToDesiredElevatorSetpointButton.reset(new JoystickButton(AirForceOneController.get(), DesiredElevatorSetpointButtonNumber));
			GoToDesiredElevatorSetpointButton->WhenPressed(new GoToDesiredSetpointCommand());
		}
		catch(const std::exception& e)
		{
			lumberJack->eLog(std::string("GoToDesiredElevatorSetpointButton.reset() failed; ") + std::string(e.what()));
		}
	}

	// LIFTER
	if(Robot::EnableLifter)
	{
		try
		{
			LifterButton.reset(new JoystickButton(controllerDriver.get(), LifterPrepareToEjectCoreButtonNumber));
			LifterButton->WhenPressed(new StartLifterCommand());
		}
		catch(const std::exception& e)
		{
			lumberJack->eLog(std::string("LifterButton.reset() failed; ") + std::string(e.what()));
		}
	}

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

	useJoystick = true;

	// DRIVETRAIN
	if(Robot::EnableDriveTrain)
	{
		if(useJoystick)
		{
			try
			{
				FinesseButton.reset(new JoystickButton(controllerDriver.get(), JoystickFinesseButton));
				FinesseButton->ToggleWhenPressed(new ToggleFinesseModeCommand());
			}
			catch(const std::exception& e)
			{
				lumberJack->eLog(std::string("FinesseButton.reset() failed; ") + std::string(e.what()));
			}

			try
			{
				InvertDriverControlsButton.reset(new JoystickButton(controllerDriver.get(), InvertDriverControlsButtonNumber));
				InvertDriverControlsButton->WhenPressed(new InvertDriverControlsCommand());
			}
			catch(const std::exception& e)
			{
				lumberJack->eLog(std::string("InvertDriverControlsButton.reset() failed; ") + std::string(e.what()));
			}
		}
		else
		{
			try
			{
				FinesseButton.reset(new JoystickButton(controllerDriver.get(), XBoxFinnesseButtonNumber));
				FinesseButton->ToggleWhenPressed(new ToggleFinesseModeCommand());
			}
			catch(const std::exception& e)
			{
				lumberJack->eLog(std::string("FinesseButton.reset() failed; ") + std::string(e.what()));
			}
		}
	}
	//Controller Output
	SmartDashboard::PutString("DB/String 5", to_string(ExponentMaxValue));

}

std::shared_ptr<Joystick> OI::GetDriverController()
{
	return controllerDriver;
}

double OI::GetJoystickX()
{
	double x = 0.0;

	if(useJoystick)
	{
		// Deadzone for X axis
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
			// Inversed when driving normally
			x = -controllerDriver->GetX();
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
			// Xboxdeadzone for X axis
			if(controllerDriver->GetRawAxis(XBoxForwardReverseAxisNumber) <= XboxDeadzone
				 && controllerDriver->GetRawAxis(XBoxForwardReverseAxisNumber) >= -XboxDeadzone
				 && fabs(controllerDriver->GetRawAxis(XBoxForwardReverseAxisNumber)) > fabs(controllerDriver->GetRawAxis(XBoxLateralAxisNumber)))
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
				x = controllerDriver->GetRawAxis(XBoxLateralAxisNumber);
			}
		}
	}

	x += 0.0;

	return Clamp(x);
}

double OI::GetJoystickY()
{
	double y = 0.0;

	if(useJoystick)
	{
		// Joystick deadzone for Y axis
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
			// Xboxdeadzone for Y axis
			if(controllerDriver->GetRawAxis(XBoxLateralAxisNumber) <= XboxDeadzone
				 && controllerDriver->GetRawAxis(XBoxLateralAxisNumber) >= -XboxDeadzone
				 && fabs(controllerDriver->GetRawAxis(XBoxLateralAxisNumber)) > fabs(controllerDriver->GetRawAxis(XBoxForwardReverseAxisNumber)))
			{
					OverrideYDeadzone = true;
			}
			else
			{
					OverrideYDeadzone = false;
			}

			if(OverrideXDeadzone)
			{
				y = 0.0;
			}
			else
			{
				y = controllerDriver->GetRawAxis(XBoxForwardReverseAxisNumber);
			}
		}
	}

	y += 0.0;

	return Clamp(y);
}

double OI::GetJoystickTwist()
{
	double rotation = 0.0;

	if(useJoystick)
	{
		// The direction turned is CW for negative and CCW for positive.
		//Adding deadzone for Z axis
		if(fabs(controllerDriver->GetTwist()) <= JoystickTwistDeadzone)
		{
			OverrideZDeadzone = true;
			rotation += 0.0;
		}
		else
		{
			OverrideZDeadzone = false;
			rotation = controllerDriver->GetTwist() * -0.5;
		}

	}
	else
	{
		if(fabs(controllerDriver->GetRawAxis(XBoxTwistAxisNumber)) <= XboxTwistDeadzone)
		{
			rotation += 0.0;
		}
		else
		{
			rotation = controllerDriver->GetRawAxis(XBoxTwistAxisNumber);
		}
	}

	rotation += 0.0;

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
	double CurrentActualElevatorSetpointControllerValue = AirForceOneController->GetRawAxis(DesiredElevatorSetpointAxisNumber);

	DesiredSetpoint = round(CurrentActualElevatorSetpointControllerValue/SetPointDelimiterValue);

	if(DesiredSetpoint == 0)
	{
		DesiredSetpoint = 1;
	}

	return DesiredSetpoint;
}

double OI::GetAirForceOneXAxis() {
	return Clamp(AirForceOneController->GetRawAxis(GrabberSpitCubeLeverAxisNumber));
}

double OI::ScaleAirForceOneAxis(double ValueToRescale) {
	double Output = 0.0;

	if(ValueToRescale > 0.0)
	{
		double NewMax = 0.99;
		double NewMin = 0.500001;
		Output = (((NewMax - NewMin) * (ValueToRescale - 0.0)) / (0.99 - 0.0)) + NewMin;
	}
	else if(ValueToRescale == 0.0)
	{
		Output = 0.5;
	}
	else
	{
		Output = fabs((ValueToRescale + 0.99) / 2);
	}

	return Output;
}

void OI::GetExponentFromDashBoard()
{
	 //TODO: test
	ExponentMaxValue = std::stod(SmartDashboard::GetString("DB/String 5", to_string(ExponentMaxValue)));
}

double OI::GetExponent()
{
	return ExponentMaxValue;
}
