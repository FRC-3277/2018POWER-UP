#ifndef DriveWithJoystick_H
#define DriveWithJoystick_H

#include "LumberJack.h"
#include "Robot.h"
#include <Commands/Command.h>

class DriveWithJoystick : public frc::Command
{
public:
	DriveWithJoystick();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // DriveWithJoystick_H
