/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <math.h>

#include "OI.h"
#include "WPILib.h"
#include "Commands/EatCubeCommand.h"
#include "Commands/SpitCubeCommand.h"
#include "Commands/InvertDriverControlsCommand.h"
#include "Commands/LowerElevatorCommand.h"
#include "Commands/RaiseElevatorCommand.h"
#include "Commands/GoToDesiredSetpointCommand.h"
#include "Commands/ToggleFinesseModeCommand.h"
#include "Commands/LifterRunWinchCommand.h"
#include "Commands/PrepareLifterCoreForEjectCommand.h"

namespace UDC = UserDefinedController;

OI::OI()
{
	try
	{
		// Controllers
		lumberJack->dLog("Assigning controllers");
		assignedController.reset(new UserDefinedController::AssignedController());

		switch(PlayerControllerConfigurationMode)
		{
			case 0:
			{
				firstPlayerController.reset(new Joystick(EXTREME3D_PRO_CONTROLLER_ID));
				break;
			}
			case 1:
			{
				firstPlayerController.reset(new Joystick(XBOX_CONTROLLER_ID));
				break;
			}
			case 2:
			{
				firstPlayerController.reset(new Joystick(EXTREME3D_PRO_CONTROLLER_ID));
				secondPlayerController.reset(new Joystick(AIRFORCEONE_CONTROLLER_ID));
				break;
			}
			case 3:
			{
				firstPlayerController.reset(new Joystick(EXTREME3D_PRO_CONTROLLER_ID));
				secondPlayerController.reset(new Joystick(AIRFORCEONE_CONTROLLER_ID));
				thirdPlayerController.reset(new Joystick(XBOX_CONTROLLER_ID));
				break;
			}
		}
	}
	catch(const std::exception& e)
	{
		lumberJack->eLog(std::string("Controller reset operation failed; ") + std::string(e.what()));
	}

	try
	{
		// Mapping buttons to controllers
		lumberJack->dLog("Mapping buttons to controllers");
		switch(PlayerControllerConfigurationMode)
		{
			case 0:
			{
				assignedController->Extreme3D_Pro::AssignAxis(LateralAxisId, firstPlayerController, UDC::Extreme3D_Pro::LOGITECH_EXTREME3DPRO_AXIS::JOYSTICK_X_AXIS);
				assignedController->Extreme3D_Pro::AssignAxis(ForwardReverseAxisId, firstPlayerController, UDC::Extreme3D_Pro::LOGITECH_EXTREME3DPRO_AXIS::JOYSTICK_Y_AXIS);
				assignedController->Extreme3D_Pro::AssignAxis(TwistAxisId, firstPlayerController, UDC::Extreme3D_Pro::LOGITECH_EXTREME3DPRO_AXIS::JOYSTICK_Z_AXIS);

				// Due to only one axis ToggleElevatorControlModeId and GoToDesiredElevatorSetpointAxisId unavailable in single controller mode
				assignedController->Extreme3D_Pro::AssignButton(JoystickFinesseButtonId, firstPlayerController, FinesseButton, UDC::Extreme3D_Pro::LOGITECH_EXTREME3DPRO_BUTTON::JOYSTICK_BUTTON_SEVEN);
				assignedController->Extreme3D_Pro::AssignButton(InvertDriverControlsButtonId, firstPlayerController, InvertDriverControlsButton, UDC::Extreme3D_Pro::LOGITECH_EXTREME3DPRO_BUTTON::JOYSTICK_BUTTON_TWELVE);

				assignedController->Extreme3D_Pro::AssignButton(ElevatorUpButtonId, firstPlayerController, ElevatorUpButton, UDC::Extreme3D_Pro::LOGITECH_EXTREME3DPRO_BUTTON::JOYSTICK_BUTTON_TWO);
				assignedController->Extreme3D_Pro::AssignButton(ElevatorDownButtonId, firstPlayerController, ElevatorDownButton, UDC::Extreme3D_Pro::LOGITECH_EXTREME3DPRO_BUTTON::JOYSTICK_BUTTON_THREE);

				// Grabber
				assignedController->Extreme3D_Pro::AssignButton(GrabberInjectionButtonId, firstPlayerController, InjectionButton, UDC::Extreme3D_Pro::LOGITECH_EXTREME3DPRO_BUTTON::JOYSTICK_BUTTON_FOUR);
				assignedController->Extreme3D_Pro::AssignButton(GrabberEjectionButtonId, firstPlayerController, EjectionButton, UDC::Extreme3D_Pro::LOGITECH_EXTREME3DPRO_BUTTON::JOYSTICK_BUTTON_FIVE);
				assignedController->Extreme3D_Pro::AssignAxis(GrabberSpeedControlAxisId, firstPlayerController, UDC::Extreme3D_Pro::LOGITECH_EXTREME3DPRO_AXIS::JOYSTICK_SLIDER);

				// Lifter
				assignedController->Extreme3D_Pro::AssignButton(LifterPrepareCoreEjectionButtonId, firstPlayerController, LifterEjectCoreButton, UDC::Extreme3D_Pro::LOGITECH_EXTREME3DPRO_BUTTON::JOYSTICK_BUTTON_TEN);
				assignedController->Extreme3D_Pro::AssignButton(LifterRunWinchButtonId, firstPlayerController, LifterRunWinchButton, UDC::Extreme3D_Pro::LOGITECH_EXTREME3DPRO_BUTTON::JOYSTICK_BUTTON_ELEVEN);
				break;
			}
			case 1:
			{
				assignedController->XBox::AssignAxis(LateralAxisId, firstPlayerController, UDC::XBox::XBOX_AXIS::XBOX_LEFT_STICK_X_AXIS);
				assignedController->XBox::AssignAxis(ForwardReverseAxisId, firstPlayerController, UDC::XBox::XBOX_AXIS::XBOX_LEFT_STICK_Y_AXIS);
				assignedController->XBox::AssignAxis(TwistAxisId, firstPlayerController, UDC::XBox::XBOX_AXIS::XBOX_RIGHT_STICK_X_AXIS);

				assignedController->XBox::AssignButton(JoystickFinesseButtonId, firstPlayerController, FinesseButton, UDC::XBox::XBOX_BUTTON::XBOX_LEFT_SHOLDER_BUTTON);
				break;
			}
			case 2:
			{
				assignedController->Extreme3D_Pro::AssignAxis(LateralAxisId, firstPlayerController, UDC::Extreme3D_Pro::LOGITECH_EXTREME3DPRO_AXIS::JOYSTICK_X_AXIS);
				assignedController->Extreme3D_Pro::AssignAxis(ForwardReverseAxisId, firstPlayerController, UDC::Extreme3D_Pro::LOGITECH_EXTREME3DPRO_AXIS::JOYSTICK_Y_AXIS);
				assignedController->Extreme3D_Pro::AssignAxis(TwistAxisId, firstPlayerController, UDC::Extreme3D_Pro::LOGITECH_EXTREME3DPRO_AXIS::JOYSTICK_Z_AXIS);
				// This allows the control of the elevator to switch between player one and player two.  
				// Player one is limited to direct up and own where player one can set and forget desired position.
				assignedController->AirForceOne::AssignButton(ToggleElevatorControlModeId, secondPlayerController, ToggleElevatorControlModeButton, UDC::AirForceOne::AIRFORCEONE_BUTTON::AIRFORCEONE_BUTTON_FIVE);
				assignedController->AirForceOne::AssignAxis(GoToDesiredElevatorSetpointAxisId, secondPlayerController, UDC::AirForceOne::AIRFORCEONE_AXIS::AIRFORCEONE_Z_AXIS);
				break;
			}
			case 3:
			{
				break;
			}
		}
	}
	catch(const std::exception& e)
	{
		lumberJack->eLog(std::string("Mapping buttons to controllers operation failed; ") + std::string(e.what()));
	}

	// Mapping Buttons To Commands
	lumberJack->dLog("Assigning buttons and commands");
	//	GRABBER
	if(EnableGrabber)
	{
		try
		{
			MapButtonToController(GrabberInjectionButtonId);
			assignedController->GetAssignedButton(GrabberInjectionButtonId)->WhileHeld(new EatCubeCommand());
		}
		catch(const std::exception& e)
		{
			lumberJack->eLog(std::string("InjectionButton.reset() failed; EatCubeCommand() will not be available; ") + std::string(e.what()));
		}

		try
		{
			MapButtonToController(GrabberEjectionButtonId);
			assignedController->GetAssignedButton(GrabberEjectionButtonId)->WhileHeld(new SpitCubeCommand());
		}
		catch(const std::exception& e)
		{
			lumberJack->eLog(std::string("EjectionButton.reset() failed; SpitCubeCommand() will not be available; ") + std::string(e.what()));
		}
	}

	//	ELEVATOR
	if(EnableElevator)
	{
		try
		{
			MapButtonToController(ElevatorUpButtonId);
			assignedController->GetAssignedButton(ElevatorUpButtonId)->WhileHeld(new RaiseElevatorCommand());
		}
		catch(const std::exception& e)
		{
			lumberJack->eLog(std::string("ElevatorUpButton.reset() failed; RaiseElevatorCommand() will not be available; ") + std::string(e.what()));
		}

		try
		{
			MapButtonToController(ElevatorDownButtonId);
			assignedController->GetAssignedButton(ElevatorDownButtonId)->WhileHeld(new LowerElevatorCommand());
		}
		catch(const std::exception& e)
		{
			lumberJack->eLog(std::string("ElevatorDownButton.reset() failed; LowerElevatorCommand() will not be available; ") + std::string(e.what()));
		}

		try
		{
			MapButtonToController(ToggleElevatorControlModeId);
			// This command doesn't follow the norm.  It
			assignedController->GetAssignedButton(ToggleElevatorControlModeId)->WhenPressed(new GoToDesiredSetpointCommand());
		}
		catch(const std::exception& e)
		{
			lumberJack->eLog(std::string("GoToDesiredElevatorSetpointButton.reset() failed; GoToDesiredSetpointCommand() will not be available manually; ") + std::string(e.what()));
		}
	}

	// LIFTER
	if(EnableLifter)
	{
		try
		{
			MapButtonToController(LifterPrepareCoreEjectionButtonId);
			assignedController->GetAssignedButton(LifterPrepareCoreEjectionButtonId)->WhenPressed(new PrepareLifterCoreForEjectCommand());
		}
		catch(const std::exception& e)
		{
			lumberJack->eLog(std::string("LifterEjectCoreButton.reset() failed; PrepareLifterCoreForEjectCommand() will not be available; ") + std::string(e.what()));
		}

		try
		{
			MapButtonToController(LifterRunWinchButtonId);
			assignedController->GetAssignedButton(LifterRunWinchButtonId)->WhileHeld(new LifterRunWinchCommand());
		}
		catch(const std::exception& e)
		{
			lumberJack->eLog(std::string("LifterRunWinchButtonNumber.reset() failed; LifterRunWinchCommand() will not be available; ") + std::string(e.what()));
		}
	}

	enableD_PadDebugging = false;

	// DRIVETRAIN
	if(EnableDriveTrain)
	{
		try
		{
			MapButtonToController(JoystickFinesseButtonId);
			assignedController->GetAssignedButton(JoystickFinesseButtonId)->ToggleWhenPressed(new ToggleFinesseModeCommand());
		}
		catch(const std::exception& e)
		{
			lumberJack->eLog(std::string("FinesseButton.reset() failed;  will not be available; ") + std::string(e.what()));
		}

		try
		{
			MapButtonToController(InvertDriverControlsButtonId);
			assignedController->GetAssignedButton(InvertDriverControlsButtonId)->WhenPressed(new InvertDriverControlsCommand());
		}
		catch(const std::exception& e)
		{
			lumberJack->eLog(std::string("InvertDriverControlsButton.reset() failed;  will not be available; ") + std::string(e.what()));
		}
	}
}

void OI::MapButtonToController(const std::string& givenButtonName)
{
	assignedController->GetAssignedButton(givenButtonName).reset(new JoystickButton(assignedController->GetAssignedController(givenButtonName).get(), assignedController->GetAssignedButtonNumber(givenButtonName)));
}

double OI::GetJoystickX()
{
	double x = 0.0;

	if(useJoystick)
	{
		// Deadzone for X axis
		if(assignedController->GetAssignedController(ForwardReverseAxisId)->GetY() <= JoystickDeadzone
			 && assignedController->GetAssignedController(ForwardReverseAxisId)->GetY() >= -JoystickDeadzone
			 && fabs(assignedController->GetAssignedController(ForwardReverseAxisId)->GetY()) > fabs(assignedController->GetAssignedController(LateralAxisId)->GetX()))
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
			x = -assignedController->GetAssignedController(LateralAxisId)->GetX();
		}

	}
	else
	{
		if(enableD_PadDebugging)
		{
			if(firstPlayerController->GetPOV() <= 90 + 15 && firstPlayerController->GetPOV() >= 90 - 15)
			{
				x = 0.5;
			}
			else if(firstPlayerController->GetPOV() <= 270 + 15 && firstPlayerController->GetPOV() >= 270 - 15)
			{
				x = -0.5;
			}
		}
		else
		{
			// Xboxdeadzone for X axis
			if(assignedController->GetAssignedController(ForwardReverseAxisId)->GetRawAxis(assignedController->GetAssignedAxisNumber(ForwardReverseAxisId)) <= XboxDeadzone
				 && assignedController->GetAssignedController(ForwardReverseAxisId)->GetRawAxis(assignedController->GetAssignedAxisNumber(ForwardReverseAxisId)) >= -XboxDeadzone
				 && fabs(assignedController->GetAssignedController(ForwardReverseAxisId)->GetRawAxis(assignedController->GetAssignedAxisNumber(ForwardReverseAxisId))) > fabs(assignedController->GetAssignedController(LateralAxisId)->GetRawAxis(assignedController->GetAssignedAxisNumber(LateralAxisId))))
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
				x = -assignedController->GetAssignedController(LateralAxisId)->GetRawAxis(assignedController->GetAssignedAxisNumber(LateralAxisId));
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
		if(assignedController->GetAssignedController(LateralAxisId)->GetX() <= JoystickDeadzone
			&& assignedController->GetAssignedController(LateralAxisId)->GetX() >= -JoystickDeadzone
			&& fabs(assignedController->GetAssignedController(LateralAxisId)->GetX()) > fabs(assignedController->GetAssignedController(ForwardReverseAxisId)->GetY()))
		{
			OverrideXDeadzone = true;
		}
		else
		{
			OverrideXDeadzone = false;
		}

		CircleDeadZone();

		if(OverrideYDeadzone)
		{
			y = 0.0;
		}
		else
		{
			y = assignedController->GetAssignedController(ForwardReverseAxisId)->GetY();
		}
	}
	else
	{
		if(enableD_PadDebugging)
		{
			if(firstPlayerController->GetPOV() <= 0 + 15 && firstPlayerController->GetPOV() >= 360 - 15)
			{
				y = -0.5;
			}
			else if(firstPlayerController->GetPOV() <= 180 + 15 && firstPlayerController->GetPOV() >= 180 - 15)
			{
				y = 0.5;
			}
		}
		else
		{
			// Xboxdeadzone for Y axis
			if(assignedController->GetAssignedController(LateralAxisId)->GetRawAxis(assignedController->GetAssignedAxisNumber(LateralAxisId)) <= XboxDeadzone
				 && assignedController->GetAssignedController(LateralAxisId)->GetRawAxis(assignedController->GetAssignedAxisNumber(LateralAxisId)) >= -XboxDeadzone
				 && fabs(assignedController->GetAssignedController(LateralAxisId)->GetRawAxis(assignedController->GetAssignedAxisNumber(LateralAxisId))) > fabs(assignedController->GetAssignedController(ForwardReverseAxisId)->GetRawAxis(assignedController->GetAssignedAxisNumber(ForwardReverseAxisId))))
			{
					OverrideYDeadzone = true;
			}
			else
			{
					OverrideYDeadzone = false;
			}

			CircleDeadZone();

			if(OverrideXDeadzone)
			{
				y = 0.0;
			}
			else
			{
				y = assignedController->GetAssignedController(ForwardReverseAxisId)->GetRawAxis(assignedController->GetAssignedAxisNumber(ForwardReverseAxisId));
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
		if(fabs(assignedController->GetAssignedController(TwistAxisId)->GetTwist()) <= JoystickTwistDeadzone)
		{
			OverrideZDeadzone = true;
			rotation += 0.0;
		}
		else
		{
			OverrideZDeadzone = false;
			rotation = assignedController->GetAssignedController(TwistAxisId)->GetTwist() * -0.5;
		}

	}
	else
	{
		if(fabs(assignedController->GetAssignedController(TwistAxisId)->GetRawAxis(assignedController->GetAssignedAxisNumber(TwistAxisId))) <= XboxTwistDeadzone)
		{
			rotation += 0.0;
		}
		else
		{
			rotation = assignedController->GetAssignedController(TwistAxisId)->GetRawAxis(assignedController->GetAssignedAxisNumber(TwistAxisId)) * -1.0;
		}
	}

	rotation += 0.0;

	return Clamp(rotation);
}

void OI::CircleDeadZone()
{
	if(useJoystick == false)
	{
		if(pow((assignedController->GetAssignedController(LateralAxisId)->GetRawAxis(assignedController->GetAssignedAxisNumber(LateralAxisId)) - 0.0), 2) +
				pow((assignedController->GetAssignedController(ForwardReverseAxisId)->GetRawAxis(assignedController->GetAssignedAxisNumber(ForwardReverseAxisId)) - 0.0), 2) < pow(XboxRestingDeadzone, 2))
		{
			OverrideYDeadzone = true;
			OverrideXDeadzone = true;
		}
		else
		{
			OverrideYDeadzone = false;
			OverrideXDeadzone = false;
		}
	}
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
	double CurrentActualElevatorSetpointControllerValue = ScaleAirForceOneAxis(-assignedController->GetAssignedController(GoToDesiredElevatorSetpointAxisId)->GetRawAxis(assignedController->GetAssignedAxisNumber(GoToDesiredElevatorSetpointAxisId)));
	DesiredSetpoint = round(CurrentActualElevatorSetpointControllerValue/SetPointDelimiterValue);

	lumberJack->iLog("DesiredSetpoint: " + std::to_string(DesiredSetpoint));
	// TODO: Disabled currently due to elevator bucking which has caused camera damage due to reversals.
	return 0;
}

double OI::GetAirForceOneXAxis() {
	return Clamp(assignedController->GetAssignedController(GrabberEjectionButtonId)->GetRawAxis(assignedController->GetAssignedAxisNumber(GrabberEjectionButtonId)));
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
