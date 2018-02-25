#include "Controller/AssignedController.h"

namespace UserDefinedController {

	AssignedController::AssignedController()
	{
		lumberJack.reset(new LumberJack());
	}

	AssignedController::~AssignedController()
	{
	}

	std::shared_ptr<frc::Joystick> AssignedController::GetAssignedController(const std::string& givenButtonOrAxisName)
	{
		std::shared_ptr<frc::Joystick> joystick = nullptr;
		int numberOfMappingsFound = 0;

		try
		{
			if(joystick == nullptr)
			{
				joystick = AirForceOne::GetController(givenButtonOrAxisName);
				numberOfMappingsFound += 1;
			}
		}
		catch(ERR::CustomError& e)
		{
			//do nothing, here to prevent failure
		}

		try
		{
			if(joystick == nullptr)
			{
				joystick = Extreme3D_Pro::GetController(givenButtonOrAxisName);
				numberOfMappingsFound += 1;
			}
		}
		catch(ERR::CustomError& e)
		{
			//do nothing, here to prevent failure
		}

		try
		{
			if(joystick == nullptr)
			{
				joystick = XBox::GetController(givenButtonOrAxisName);
				numberOfMappingsFound += 1;
			}
		}
		catch(ERR::CustomError& e)
		{
			//do nothing, here to prevent failure
		}

		// If zero or more than one controller is mapped then boom!
		if(numberOfMappingsFound == 0 || numberOfMappingsFound > 1)
		{
			std::string errMsg;

			if(numberOfMappingsFound == 0)
			{
				errMsg = "; No controller mapped; ";
			}
			else if(numberOfMappingsFound > 1)
			{
				errMsg = "; More than one controller mapped; ";
			}

			throw ERR::CustomError(std::string(__FILE__) + errMsg + givenButtonOrAxisName);
		}

		return joystick;
	}

	std::shared_ptr<frc::JoystickButton> AssignedController::GetAssignedButton(const std::string& givenButtonName)
	{
		std::shared_ptr<frc::JoystickButton> joystickButton = nullptr;
		int numberOfMappingsFound = 0;

		try
		{
			if(joystickButton == nullptr)
			{
				joystickButton = AirForceOne::GetButton(givenButtonName);
				numberOfMappingsFound += 1;
			}
		}
		catch(ERR::CustomError& e)
		{
			//do nothing, here to prevent failure
		}

		try
		{
			if(joystickButton == nullptr)
			{
				joystickButton = Extreme3D_Pro::GetButton(givenButtonName);
				numberOfMappingsFound += 1;
			}
		}
		catch(ERR::CustomError& e)
		{
			//do nothing, here to prevent failure
		}

		try
		{
			if(joystickButton == nullptr)
			{
				joystickButton = XBox::GetButton(givenButtonName);
				numberOfMappingsFound += 1;
			}
		}
		catch(ERR::CustomError& e)
		{
			//do nothing, here to prevent failure
		}

		// If zero or more than one controller is mapped then boom!
		if(numberOfMappingsFound == 0 || numberOfMappingsFound > 1)
		{
			std::string errMsg;

			if(numberOfMappingsFound == 0)
			{
				errMsg = "; No controller button mapped; ";
			}
			else if(numberOfMappingsFound > 1)
			{
				errMsg = "; More than one controller button mapped; ";
			}

			throw ERR::CustomError(std::string(__FILE__) + errMsg + givenButtonName);
		}

		return joystickButton;
	}

	int AssignedController::GetAssignedButtonNumber(const std::string& givenButtonName)
	{
		int assignedButtonNumber;
		int numberOfMappingsFound = 0;

		try
		{
			assignedButtonNumber = AirForceOne::GetButtonNumber(givenButtonName);
			numberOfMappingsFound += 1;
		}
		catch(ERR::CustomError& e)
		{
			//do nothing, here to prevent failure
		}

		try
		{
			assignedButtonNumber = Extreme3D_Pro::GetButtonNumber(givenButtonName);
			numberOfMappingsFound += 1;
		}
		catch(ERR::CustomError& e)
		{
			//do nothing, here to prevent failure
		}

		try
		{
			assignedButtonNumber = XBox::GetButtonNumber(givenButtonName);
			numberOfMappingsFound += 1;
		}
		catch(ERR::CustomError& e)
		{
			//do nothing, here to prevent failure
		}

		// If zero or more than one controller is mapped then boom!
		if(numberOfMappingsFound == 0 || numberOfMappingsFound > 1)
		{
			std::string errMsg;

			if(numberOfMappingsFound == 0)
			{
				errMsg = "; No button number mapped; ";
			}
			else if(numberOfMappingsFound > 1)
			{
				errMsg = "; More than one button number mapped; ";
			}

			throw ERR::CustomError(std::string(__FILE__) + errMsg + givenButtonName);
		}

		return assignedButtonNumber;
	}

	int AssignedController::GetAssignedAxisNumber(const std::string& givenButtonName)
	{
		int assignedAxisNumber;
		int numberOfMappingsFound = 0;

		try
		{
			assignedAxisNumber = AirForceOne::GetAxisNumber(givenButtonName);
			numberOfMappingsFound += 1;
		}
		catch(ERR::CustomError& e)
		{
			//do nothing, here to prevent failure
		}

		try
		{
			assignedAxisNumber = Extreme3D_Pro::GetAxisNumber(givenButtonName);
			numberOfMappingsFound += 1;
		}
		catch(ERR::CustomError& e)
		{
			//do nothing, here to prevent failure
		}

		try
		{
			assignedAxisNumber = XBox::GetAxisNumber(givenButtonName);
			numberOfMappingsFound += 1;
		}
		catch(ERR::CustomError& e)
		{
			//do nothing, here to prevent failure
		}

		// If zero or more than one controller is mapped then boom!
		if(numberOfMappingsFound == 0 || numberOfMappingsFound > 1)
		{
			std::string errMsg;

			if(numberOfMappingsFound == 0)
			{
				errMsg = "; No axis number mapped; ";
			}
			else if(numberOfMappingsFound > 1)
			{
				errMsg = "; More than one axis number mapped; ";
			}

			throw ERR::CustomError(std::string(__FILE__) + errMsg + givenButtonName);
		}

		return assignedAxisNumber;
	}
}/* namespace UserDefinedController */
