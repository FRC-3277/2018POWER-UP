#ifndef SRC_CONTROLLER_EXTREME3DPRO_H_
#define SRC_CONTROLLER_EXTREME3DPRO_H_

#include <map>
#include <string>
#include <iterator>

#include "LumberJack.h"
#include "CustomError.h"
#include <Joystick.h>
#include <Buttons/JoystickButton.h>

namespace UserDefinedController
{
	class Extreme3D_Pro
	{
		// Placed in this order since required by both private and public methods
		public:
			Extreme3D_Pro();
			virtual ~Extreme3D_Pro();
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
				JOYSTICK_BUTTON_TWELVE = 12
			};

			enum class LOGITECH_EXTREME3DPRO_AXIS : int
			{
				JOYSTICK_X_AXIS = 0,
				JOYSTICK_Y_AXIS = 1,
				JOYSTICK_Z_AXIS = 2,
				JOYSTICK_SLIDER = 3
			};
			void AssignButton(const std::string& givenButtonName,
								std::shared_ptr<frc::Joystick> controller,
								std::shared_ptr<frc::JoystickButton> controllerButton,
								Extreme3D_Pro::LOGITECH_EXTREME3DPRO_BUTTON buttonToButtonNumber);
			void AssignAxis(const std::string& givenAxisName,
								std::shared_ptr<frc::Joystick> controller,
								Extreme3D_Pro::LOGITECH_EXTREME3DPRO_AXIS axisToAxisNumber);

		protected:
			struct ControllerButtonMapping
			{
				std::shared_ptr<frc::Joystick> controller;
				std::shared_ptr<frc::JoystickButton> controllerButton;
				LOGITECH_EXTREME3DPRO_BUTTON buttonNumber;
			};

			struct ControllerAxisMapping
			{
				std::shared_ptr<frc::Joystick> controller;
				LOGITECH_EXTREME3DPRO_AXIS axisNumber;
			};

		private:
			std::shared_ptr<LumberJack> lumberJack;
			std::map<std::string, ControllerAxisMapping> userDefinedControllerAxisMapping;
			std::map<std::string, ControllerButtonMapping> userDefinedControllerButtonMapping;

			void DebugReportControllerUsage();

		protected:
			Extreme3D_Pro::ControllerButtonMapping GetButtonMap(const std::string& givenButtonName);
			Extreme3D_Pro::ControllerAxisMapping GetAxisMap(const std::string& givenAxisName);
			std::shared_ptr<frc::Joystick> GetController(const std::string& givenButtonOrAxisName);
			std::shared_ptr<frc::JoystickButton> GetButton(const std::string& givenButtonName);
			int GetButtonNumber(const std::string& givenButtonName);
			int GetAxisNumber(const std::string& givenAxisName);
	};
} /* namespace Controller */
#endif /* SRC_CONTROLLER_EXTREME3DPRO_H_ */
