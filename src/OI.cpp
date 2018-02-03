/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"
#include "Commands/LowerElevator.h"
#include "Commands/RaiseElevator.h"

OI::OI()
{
	xBoxControllerDriver.reset(new Joystick(DRIVER_CONTROLLER_ID));
	UpButton.reset(new JoystickButton(xBoxControllerDriver.get(), ChangeMeUpButton));
	DownButton.reset(new JoystickButton(xBoxControllerDriver.get(), ChangeMeDownButton));

	// Button trigger and command mappings
	UpButton->WhenPressed(new RaiseElevator());
	DownButton->WhenPressed(new LowerElevator());
}

std::shared_ptr<Joystick> OI::getXBoxController()
{
   return xBoxControllerDriver;
}
