#ifndef SRC_CONTROLLER_XBOX_H_
#define SRC_CONTROLLER_XBOX_H_

#include <map>
#include <string>
#include <iterator>

#include "LumberJack.h"
#include "CustomError.h"
#include <Joystick.h>
#include <Buttons/JoystickButton.h>

namespace UserDefinedController
{
	class XBox
	{
		// Placed in this order since required by both private and public methods
		public:
			XBox();
			virtual ~XBox();

			enum class XBOX_BUTTON : int
			{
				XBOX_A_BUTTON = 1,
				XBOX_B_BUTTON = 2,
				XBOX_X_BUTTON = 3,
				XBOX_Y_BUTTON = 4,
				XBOX_LEFT_SHOLDER_BUTTON = 5,
				XBOX_RIGHT_SHOLDER_BUTTON = 6,
				XBOX_BACK_BUTTON = 7,
				XBOX_START_BUTTON = 8,
				XBOX_LEFT_INDEX_TRIGGER = 9,
				XBOX_RIGHT_INDEX_TRIGGER = 10
			};

			enum class XBOX_AXIS : int
			{
				XBOX_LEFT_STICK_X_AXIS = 0,
				XBOX_LEFT_STICK_Y_AXIS = 1,
				XBOX_LEFT_TRIGGER_AXIS = 2,
				XBOX_RIGHT_TRIGGER_AXIS = 3,
				XBOX_RIGHT_STICK_X_AXIS = 4,
				XBOX_RIGHT_STICK_Y_AXIS = 5
			};

		void AssignButton(const std::string& givenButtonName,
							std::shared_ptr<frc::Joystick> controller,
							std::shared_ptr<frc::JoystickButton> controllerButton,
							XBox::XBOX_BUTTON buttonToButtonNumber);
		void AssignAxis(const std::string& givenAxisName,
						std::shared_ptr<frc::Joystick> controller,
						XBox::XBOX_AXIS axisToAxisNumber);

		protected:
			struct ControllerButtonMapping
			{
				std::shared_ptr<frc::Joystick> controller;
				std::shared_ptr<frc::JoystickButton> controllerButton;
				XBOX_BUTTON buttonNumber;
			};

			struct ControllerAxisMapping
			{
				std::shared_ptr<frc::Joystick> controller;
				XBOX_AXIS axisNumber;
			};

		private:
			std::shared_ptr<LumberJack> lumberJack;
			std::map<std::string, ControllerAxisMapping> userDefinedControllerAxisMapping;
			std::map<std::string, ControllerButtonMapping> userDefinedControllerButtonMapping;

			void DebugReportControllerUsage();

		protected:
			XBox::ControllerButtonMapping GetButtonMap(const std::string& givenButtonName);
			XBox::ControllerAxisMapping GetAxisMap(const std::string& givenAxisName);
			std::shared_ptr<frc::Joystick> GetController(const std::string& givenButtonOrAxisName);
			std::shared_ptr<frc::JoystickButton> GetButton(const std::string& givenButtonName);
			int GetButtonNumber(const std::string& givenButtonName);
			int GetAxisNumber(const std::string& givenAxisName);
	};
} /* namespace Controller */
#endif /* SRC_CONTROLLER_XBOX_H_ */
