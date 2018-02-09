/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"

#include <math.h>

#include <Commands/LowerElevatorCommand.h>
#include <Commands/RaiseElevatorCommand.h>
#include <Commands/GoToDesiredSetpointCommand.h>


OI::OI()
{
	xBoxControllerDriver.reset(new Joystick(DRIVER_CONTROLLER_ID));
	AirForceOneController.reset(new Joystick(ALTERNATE_CONTROLLER_ID));

	ElevatorUpButton.reset(new JoystickButton(xBoxControllerDriver.get(), ElevatorUpButtonNumber));
	ElevatorDownButton.reset(new JoystickButton(xBoxControllerDriver.get(), ElevatorDownButtonNumber));

	// Button trigger and command mappings
	ElevatorUpButton->WhenPressed(new RaiseElevatorCommand());
	ElevatorDownButton->WhenPressed(new LowerElevatorCommand());
	GoToDesiredElevatorSetpointButton->WhenPressed(new GoToDesiredSetpointCommand());
}

std::shared_ptr<Joystick> OI::getXBoxController()
{
   return xBoxControllerDriver;
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
