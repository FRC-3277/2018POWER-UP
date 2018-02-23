#ifndef SRC_CONTROLLER_EXTREME3DPRO_H_
#define SRC_CONTROLLER_EXTREME3DPRO_H_

#include <map>
#include <string>
#include <iterator>

#include "LumberJack.h"
#include <Buttons/JoystickButton.h>

namespace UserDefinedController {

class Extreme3D_Pro
{
	// Placed in this order since required by both private and public methods
public:
	struct ButtonToButtonNumber
	{
		std::shared_ptr<frc::JoystickButton> joystickButton;
		enum class LOGITECH_EXTREME3DPRO_BUTTON;
	};

private:
	std::shared_ptr<LumberJack> lumberJack;

	enum class LOGITECH_EXTREME3DPRO_BUTTON : int
	{
		JOYSTICK_TRIGGER = 1,
		JOYSTICK_BUTTON_TWO = 2,
		JOYSTICK_BUTTON_THREE = 3,
		JOYSTICK_BUTTON_FOUR = 4,
		JOYSTICK_BUTTON_FIVE = 5,
		JOYSTICK_BUTTON_SIX = 6,
		JOYSTICK_BUTTON_SEVEN = 7,
		JOYSTICK_BUTTON_EIGHT = 8,
		JOYSTICK_BUTTON_NINE = 9,
		JOYSTICK_BUTTON_TEN = 10,
		JOYSTICK_BUTTON_ELEVEN = 11,
		JOYSTICK_BUTTON_TWELVE = 12,
		// Meant to cause a problem
		INVALID_BUTTON_NUMBER = 999
	};

	enum class LOGITECH_EXTREME3DPRO_AXIS : int
	{
		JOYSTICK_X_AXIS = 0,
		JOYSTICK_Y_AXIS = 1,
		JOYSTICK_Z_AXIS = 2,
		JOYSTICK_SLIDER = 3,
		// Meant to cause a problem
		INVALID_AXIS_NUMBER = 999
	};

	std::map<std::string, LOGITECH_EXTREME3DPRO_AXIS> userDefinedControllerAxisMapping;
	std::map<std::string, ButtonToButtonNumber> userDefinedControllerButtonMapping;

	void DebugReportControllerUsage();


public:
	Extreme3D_Pro();
	virtual ~Extreme3D_Pro();
	void AssignButton(const std::string& givenButtonName,
					std::shared_ptr<frc::JoystickButton> joystickButton,
					Extreme3D_Pro::LOGITECH_EXTREME3DPRO_BUTTON buttonToButtonNumber);
	void AssignAxis(const std::string& givenAxisName, Extreme3D_Pro::LOGITECH_EXTREME3DPRO_AXIS givenAxisNumber);
	Extreme3D_Pro::ButtonToButtonNumber GetButton(const std::string& givenButtonName);
	int GetAxis(const std::string& givenButtonName);
};

} /* namespace Controller */

#endif /* SRC_CONTROLLER_EXTREME3DPRO_H_ */
