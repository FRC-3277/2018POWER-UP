#ifndef SRC_CONTROLLER_ASSIGNEDCONTROLLER_H_
#define SRC_CONTROLLER_ASSIGNEDCONTROLLER_H_

#include "LumberJack.h"
#include "CustomError.h"
#include <Joystick.h>
#include <Buttons/JoystickButton.h>

#include "Controller/AirForceOne.h"
#include "Controller/Extreme3DPro.h"
#include "Controller/XBox.h"

namespace UserDefinedController {

class AssignedController : public AirForceOne, public Extreme3D_Pro, public XBox
{
public:
	AssignedController();
	virtual ~AssignedController();
	// Parse the controllers to determine which button/axis number was assigned
	std::shared_ptr<frc::Joystick> GetAssignedController(const std::string& givenButtonOrAxisName);
	std::shared_ptr<frc::JoystickButton> GetAssignedButton(const std::string& givenButtonName);
	int GetAssignedButtonNumber(const std::string& givenButtonName);
	int GetAssignedAxisNumber(const std::string& givenAxisName);

private:
	std::shared_ptr<LumberJack> lumberJack;
};

} /* namespace UserDefinedController */

#endif /* SRC_CONTROLLER_ASSIGNEDCONTROLLER_H_ */
