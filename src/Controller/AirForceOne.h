#ifndef SRC_CONTROLLER_AIRFORCEONE_H_
#define SRC_CONTROLLER_AIRFORCEONE_H_

#include <map>
#include <string>
#include <iterator>

#include "LumberJack.h"
#include "CustomError.h"
#include <Joystick.h>
#include <Buttons/JoystickButton.h>

namespace UserDefinedController
{
	class AirForceOne
	{
		// Placed in this order since required by both private and public methods
	public:
		AirForceOne();
		virtual ~AirForceOne();
		enum class AIRFORCEONE_BUTTON : int
		{
			AIRFORCEONE_BUTTON_ONE = 1,
			AIRFORCEONE_BUTTON_TWO = 2,
			AIRFORCEONE_BUTTON_THREE = 3,
			AIRFORCEONE_BUTTON_FOUR = 4,
			AIRFORCEONE_BUTTON_FIVE = 5,
			AIRFORCEONE_BUTTON_SIX = 6,
			AIRFORCEONE_BUTTON_SEVEN = 7,
			AIRFORCEONE_BUTTON_EIGHT = 8,
			AIRFORCEONE_BUTTON_NINE = 9
		};

		enum class AIRFORCEONE_AXIS : int
		{
			AIRFORCEONE_X_AXIS = 0,
			AIRFORCEONE_Y_AXIS = 1,
			AIRFORCEONE_Z_AXIS = 2
		};

		void AssignButton(const std::string& givenButtonName,
							std::shared_ptr<frc::Joystick> controller,
							std::shared_ptr<frc::JoystickButton> controllerButton,
							AirForceOne::AIRFORCEONE_BUTTON buttonToButtonNumber);
		void AssignAxis(const std::string& givenAxisName,
						std::shared_ptr<frc::Joystick> controller,
						AirForceOne::AIRFORCEONE_AXIS axisToAxisNumber);

		protected:
			struct ControllerButtonMapping
			{
				std::shared_ptr<frc::Joystick> controller;
				std::shared_ptr<frc::JoystickButton> controllerButton;
				AIRFORCEONE_BUTTON buttonNumber;
			};

			struct ControllerAxisMapping
			{
				std::shared_ptr<frc::Joystick> controller;
				AIRFORCEONE_AXIS axisNumber;
			};

		private:
			std::shared_ptr<LumberJack> lumberJack;
			std::map<std::string, ControllerAxisMapping> userDefinedControllerAxisMapping;
			std::map<std::string, ControllerButtonMapping> userDefinedControllerButtonMapping;

			void DebugReportControllerUsage();

		protected:
			AirForceOne::ControllerButtonMapping GetButtonMap(const std::string& givenButtonName);
			AirForceOne::ControllerAxisMapping GetAxisMap(const std::string& givenAxisName);
			std::shared_ptr<frc::Joystick> GetController(const std::string& givenButtonOrAxisName);
			std::shared_ptr<frc::JoystickButton> GetButton(const std::string& givenButtonName);
			int GetButtonNumber(const std::string& givenButtonName);
			int GetAxisNumber(const std::string& givenAxisName);
	};
} /* namespace Controller */

#endif /* SRC_CONTROLLER_AIRFORCEONE_H_ */
