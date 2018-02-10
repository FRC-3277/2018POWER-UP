#ifndef LowerElevator_H
#define LowerElevator_H

#include "LumberJack.h"

#include "Robot.h"
#include <Commands/Command.h>

class LowerElevatorCommand : public frc::Command {
public:
	LowerElevatorCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // LowerElevator_H
