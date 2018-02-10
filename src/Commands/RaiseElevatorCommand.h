#ifndef RaiseElevator_H
#define RaiseElevator_H

#include "LumberJack.h"

#include "Robot.h"
#include <Commands/Command.h>

class RaiseElevatorCommand : public frc::Command {

public:
	RaiseElevatorCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // RaiseElevator_H
