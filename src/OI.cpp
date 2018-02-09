/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"
#include "Commands/AugmentorTiltDownCommand.h"
#include "Commands/AugmentorTiltUpCommand.h"
#include "Commands/EatCubeCommand.h"
#include "Commands/SpitCubeCommand.h"

OI::OI()
{
	xBoxControllerDriver.reset(new Joystick(DRIVER_CONTROLLER_ID));

	InjectionButton.reset(new JoystickButton(xBoxControllerDriver.get(), ChangeMeInjectionButton));
	EjectionButton.reset(new JoystickButton(xBoxControllerDriver.get(), ChangeMeEjectionButton));
	AugmentorTiltUpButton.reset(new JoystickButton(xBoxControllerDriver.get(), ChangeMeAugmentorTiltUpButton));
	AugmentorTiltDownButton.reset(new JoystickButton(xBoxControllerDriver.get(), ChangeMeAugmentorTiltDownButton));

	InjectionButton->WhenPressed(new EatCubeCommand());
	EjectionButton->WhenPressed(new SpitCubeCommand());
	AugmentorTiltUpButton->WhenPressed(new AugmentorTiltUpCommand());
	AugmentorTiltDownButton->WhenPressed(new AugmentorTiltDownCommand());
}

std::shared_ptr<Joystick> OI::getXBoxController()
{
   return xBoxControllerDriver;
}
