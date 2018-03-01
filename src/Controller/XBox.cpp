#include "Controller/XBox.h"

namespace UserDefinedController
{
	XBox::XBox()
	{
		lumberJack.reset(new LumberJack());
	}

	XBox::~XBox()
	{
	}

	void XBox::AssignButton(const std::string& givenButtonName,
							std::shared_ptr<frc::Joystick> controller,
							std::shared_ptr<frc::JoystickButton> controllerButton,
							XBOX_BUTTON buttonToButtonNumber)
	{
		std::shared_ptr<JoystickButton> button;

		// Doing this step here assigns a memory address to the button.  Without it storing a null pointer is fairly useless
		button.reset(new JoystickButton(controller.get(), static_cast<int>(buttonToButtonNumber)));

		ControllerButtonMapping buttonMapping;
		buttonMapping.controller = controller;
		//TODO: cleanup unecessary param
		buttonMapping.controllerButton = button;
		buttonMapping.buttonNumber = buttonToButtonNumber;

		// TODO: prevent duplicate assignment to same button and/or same button mapping
		userDefinedControllerButtonMapping.insert(std::make_pair(givenButtonName, buttonMapping));
	}

	void XBox::AssignAxis(const std::string& givenAxisName,
							std::shared_ptr<frc::Joystick> controller,
							XBox::XBOX_AXIS axisToAxisNumber)
	{
		ControllerAxisMapping axisMapping;
		axisMapping.controller = controller;
		axisMapping.axisNumber = axisToAxisNumber;
		// TODO: prevent duplicate assignment to same axis mapping
		userDefinedControllerAxisMapping.insert(std::make_pair(givenAxisName, axisMapping));
	}

	XBox::ControllerButtonMapping XBox::GetButtonMap(const std::string& givenButtonName)
	{
		std::map<std::string, ControllerButtonMapping>::iterator iteratorPointer;
		ControllerButtonMapping controllerButtonMapping;

		iteratorPointer = userDefinedControllerButtonMapping.find(givenButtonName);
		if(iteratorPointer != userDefinedControllerButtonMapping.end())
		{
		  controllerButtonMapping = iteratorPointer->second;
		}
		else
		{
			lumberJack->eLog(std::string(__FILE__) + "; Requested button map XBox not found: " + givenButtonName);
			throw ERR::CustomError(std::string(__FILE__) + "; Requested button map XBox not found; " + givenButtonName);
		}

		return controllerButtonMapping;
	}

	XBox::ControllerAxisMapping XBox::GetAxisMap(const std::string& givenAxisName)
	{
		std::map<std::string, ControllerAxisMapping>::iterator iteratorPointer;
		ControllerAxisMapping controllerAxisMapping;

		iteratorPointer = userDefinedControllerAxisMapping.find(givenAxisName);
		if(iteratorPointer != userDefinedControllerAxisMapping.end())
		{
			controllerAxisMapping = iteratorPointer->second;
		}
		else
		{
			lumberJack->eLog(std::string(__FILE__) + "; Requested axis map not found: " + givenAxisName);
			throw ERR::CustomError(std::string(__FILE__) + "; Requested axis map not found; " + givenAxisName);
		}

		return controllerAxisMapping;
	}

	std::shared_ptr<frc::Joystick> XBox::GetController(const std::string& givenButtonOrAxisName)
	{
		std::shared_ptr<frc::Joystick> controller;

		try
		{
			controller = GetButtonMap(givenButtonOrAxisName).controller;
		}
		catch(ERR::CustomError& e)
		{
			// If not mapped to button then check for axis
			try
			{
				controller = GetAxisMap(givenButtonOrAxisName).controller;
			}
			catch(ERR::CustomError& e)
			{
				lumberJack->eLog(std::string(__FILE__) + "; Requested controller not found: " + givenButtonOrAxisName);
				throw ERR::CustomError(std::string(__FILE__) + "; Requested controller not found; " + givenButtonOrAxisName);
			}
		}

		return controller;
	}

	std::shared_ptr<frc::JoystickButton> XBox::GetButton(const std::string& givenButtonName)
	{
		std::shared_ptr<frc::JoystickButton> controllerButton;

		try
		{
			controllerButton = GetButtonMap(givenButtonName).controllerButton;
		}
		catch(ERR::CustomError& e)
		{
			throw ERR::CustomError(std::string(__FILE__) + "; Requested button not found; " + givenButtonName);
		}

		return controllerButton;
	}

	int XBox::GetButtonNumber(const std::string& givenButtonName)
	{
		XBOX_BUTTON buttonNumber;

		try
		{
			buttonNumber = GetButtonMap(givenButtonName).buttonNumber;
		}
		catch(ERR::CustomError& e)
		{
			throw ERR::CustomError(std::string(__FILE__) + "; Requested button number not found; " + givenButtonName);
		}

		return static_cast<int>(buttonNumber);
	}

	int XBox::GetAxisNumber(const std::string& givenAxisName)
	{
		std::map<std::string, ControllerAxisMapping>::iterator iteratorPointer;
		XBOX_AXIS axisNumber;

		iteratorPointer = userDefinedControllerAxisMapping.find(givenAxisName);
		if(iteratorPointer != userDefinedControllerAxisMapping.end())
		{
			axisNumber = iteratorPointer->second.axisNumber;
		}
		else
		{
			lumberJack->eLog("Requested axis not found: " + givenAxisName);
			throw ERR::CustomError(std::string(__FILE__) + "; Requested axis not found; " + givenAxisName);
		}

		return static_cast<int>(axisNumber);
	}

	void XBox::DebugReportControllerUsage()
	{
		// First the buttons
		// Create a map iterator and point to beginning of map
		std::map<std::string, ControllerButtonMapping>::iterator buttonBeginIterator = userDefinedControllerButtonMapping.begin();
		std::map<std::string, ControllerButtonMapping>::iterator buttonEndIterator = userDefinedControllerButtonMapping.end();

		// Iterate over a map using std::for_each and Lambda function
		std::for_each(buttonBeginIterator, buttonEndIterator, [](std::pair<std::string, ControllerButtonMapping> element)
		{
			// Accessing KEY from element
			std::string givenButtonName = element.first;
			// Accessing VALUE from element.
			ControllerButtonMapping buttonMapping= element.second;
			//lumberJack->iLog("Extreme3D_Pro button name: " + givenButtonName + "; Button number: " + std::to_string(static_cast<int>(buttonMapping.buttonNumber)));
		});

		// Last the axis
		// Create a map iterator and point to beginning of map
		std::map<std::string, ControllerAxisMapping>::iterator axisBeginIterator = userDefinedControllerAxisMapping.begin();
		std::map<std::string, ControllerAxisMapping>::iterator axisEndIterator = userDefinedControllerAxisMapping.begin();

		// Iterate over a map using std::for_each and Lambda function
		std::for_each(axisBeginIterator, axisEndIterator, [](std::pair<std::string, ControllerAxisMapping> element)
		{
			// Accessing KEY from element
			std::string givenAxisName = element.first;
			// Accessing VALUE from element.
			XBOX_AXIS axisNumber = element.second.axisNumber;
			//lumberJack->iLog("Extreme3D_Pro axis name: " + givenAxisName + "; Axis number: " + std::to_string(static_cast<int>(axisNumber)));
		});
	}
} /* namespace Controller */
