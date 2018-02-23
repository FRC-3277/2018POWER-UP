#include "Controller/Extreme3DPro.h"

namespace UserDefinedController {

	Extreme3D_Pro::Extreme3D_Pro()
	{
		lumberJack.reset(new LumberJack());
	}

	Extreme3D_Pro::~Extreme3D_Pro()
	{

	}

	void Extreme3D_Pro::AssignButton(const std::string& givenButtonName,
									std::shared_ptr<frc::JoystickButton> joystickButton,
									Extreme3D_Pro::LOGITECH_EXTREME3DPRO_BUTTON buttonToButtonNumber)
	{
		ButtonToButtonNumber givenButtonMapping;
		givenButtonMapping.joystickButton = joystickButton;
		givenButtonMapping.LOGITECH_EXTREME3DPRO_BUTTON = buttonToButtonNumber;

		// TODO: prevent duplicate assignment to same button and/or same button mapping
		userDefinedControllerButtonMapping.insert(std::make_pair(givenButtonName, givenButtonMapping));
	}

	void Extreme3D_Pro::AssignAxis(const std::string& givenAxisName, Extreme3D_Pro::LOGITECH_EXTREME3DPRO_AXIS givenAxisNumber)
	{
		// TODO: prevent duplicate assignment to same axis mapping
		userDefinedControllerAxisMapping.insert(std::make_pair(givenAxisName, givenAxisNumber));
	}

	Extreme3D_Pro::ButtonToButtonNumber Extreme3D_Pro::GetButton(const std::string& givenButtonName)
	{
		std::map<std::string, ButtonToButtonNumber>::iterator iteratorPointer;
		Extreme3D_Pro::ButtonToButtonNumber controllerButtonMapping = { 0 };

		iteratorPointer = userDefinedControllerButtonMapping.find(givenButtonName);
		  if(iteratorPointer != userDefinedControllerButtonMapping.end())
			  controllerButtonMapping = iteratorPointer->second;
		  else
		    lumberJack->eLog("Requested button not found: " + givenButtonName);

		  return controllerButtonMapping;
	}

	int Extreme3D_Pro::GetAxis(const std::string& givenAxisName)
	{
		std::map<std::string, LOGITECH_EXTREME3DPRO_AXIS>::iterator iteratorPointer;
		LOGITECH_EXTREME3DPRO_AXIS axisNumber = LOGITECH_EXTREME3DPRO_AXIS::INVALID_AXIS_NUMBER;

		iteratorPointer = userDefinedControllerAxisMapping.find(givenAxisName);
		if(iteratorPointer != userDefinedControllerAxisMapping.end())
			axisNumber = iteratorPointer->second;
		else
			lumberJack->eLog("Requested axis not found: " + givenAxisName);

		return static_cast<int>(axisNumber);
	}

	void Extreme3D_Pro::DebugReportControllerUsage()
	{
		// First the buttons
		// Create a map iterator and point to beginning of map
		std::map<std::string, ButtonToButtonNumber>::iterator buttonBeginIterator = userDefinedControllerButtonMapping.begin();
		std::map<std::string, ButtonToButtonNumber>::iterator buttonEndIterator = userDefinedControllerButtonMapping.end();

		// Iterate over a map using std::for_each and Lambda function
		std::for_each(buttonBeginIterator, buttonEndIterator, [](std::pair<std::string, Extreme3D_Pro::LOGITECH_EXTREME3DPRO_BUTTON> element)
		{
			// Accessing KEY from element
			std::string givenButtonName = element.first;
			// Accessing VALUE from element.
			LOGITECH_EXTREME3DPRO_BUTTON buttonNumber= element.second;
			lumberJack->iLog("Extreme3D_Pro button name: " + givenButtonName + "; Button number: " + std::to_string(static_cast<int>(buttonNumber)));
		});

		// Last the axis
		// Create a map iterator and point to beginning of map
		std::map<std::string, int>::iterator axisBeginIterator = userDefinedControllerAxisMapping.begin();
		std::map<std::string, int>::iterator axisEndIterator = userDefinedControllerAxisMapping.begin();

		// Iterate over a map using std::for_each and Lambda function
		std::for_each(axisBeginIterator, axisEndIterator, [](std::pair<std::string, Extreme3D_Pro::LOGITECH_EXTREME3DPRO_AXIS> element)
		{
			// Accessing KEY from element
			std::string givenAxisName = element.first;
			// Accessing VALUE from element.
			LOGITECH_EXTREME3DPRO_AXIS axisNumber = element.second;
			lumberJack->iLog("Extreme3D_Pro axis name: " + givenAxisName + "; Axis number: " + std::to_string(static_cast<int>(axisNumber)));
		});
	}

} /* namespace Controller */
