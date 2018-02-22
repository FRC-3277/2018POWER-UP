#include "Controller/Extreme3DPro.h"

namespace UserDefinedController {

	Extreme3D_Pro::Extreme3D_Pro()
	{

	}

	Extreme3D_Pro::~Extreme3D_Pro()
	{

	}

	void Extreme3D_Pro::AssignButton(const std::string& givenButtonName)
	{

		mapOfWords.insert(std::make_pair("earth", 1));
		mapOfWords.insert(std::make_pair("moon", 2));
		userDefinedControllerButtonMapping.insert(std::make_pair())
	}
	void Extreme3D_Pro::AssignAxis()
	{

	}

	Extreme3D_Pro::ButtonToButtonNumber Extreme3D_Pro::GetButton(const std::string& givenButtonName)
	{

	}

	int Extreme3D_Pro::GetAxis(const std::string& givenButtonName)
	{

	}

} /* namespace Controller */
