#ifndef SRC_CONTROLLER_ASSIGNEDCONTROLLER_H_
#define SRC_CONTROLLER_ASSIGNEDCONTROLLER_H_

#include "LumberJack.h"
#include "CustomError.h"
#include <Joystick.h>
#include <Buttons/JoystickButton.h>

#include "Controller/AirForceOne.h"
#include "Controller/Extreme3DPro.h"
#include "Controller/XBox.h"

namespace UserDefinedController
{
	class AssignedController : public AirForceOne, public Extreme3D_Pro, public XBox
	{
	private:
		std::shared_ptr<LumberJack> lumberJack;

		// Since axis lookup is frequent it should be cached within this class to reduce overhead and cut down logging frequency
		struct ControllerAxisMapping
		{
			std::shared_ptr<frc::Joystick> controller;
			int axisNumber;
		};

		std::map<std::string, ControllerAxisMapping> userDefinedControllerAxisMapping;

		void CacheAxisNumber(const std::string& givenAxisName,
								std::shared_ptr<frc::Joystick> controller,
								int axisToAxisNumber);

		std::shared_ptr<frc::Joystick> GetCachedAxisController(const std::string& givenAxisName);
		int GetCachedAxisNumber(const std::string& givenAxisName);

	public:
		AssignedController();
		virtual ~AssignedController();
		// Parse the controllers to determine which button/axis number was assigned
		std::shared_ptr<frc::Joystick> GetAssignedController(const std::string& givenButtonOrAxisName);
		std::shared_ptr<frc::JoystickButton> GetAssignedButton(const std::string& givenButtonName);
		int GetAssignedButtonNumber(const std::string& givenButtonName);
		int GetAssignedAxisNumber(const std::string& givenAxisName);
};

} /* namespace UserDefinedController */

#endif /* SRC_CONTROLLER_ASSIGNEDCONTROLLER_H_ */
