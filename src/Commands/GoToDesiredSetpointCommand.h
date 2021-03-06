#ifndef ElevatorCommand_H
#define ElevatorCommand_H

#include "LumberJack.h"

#include "Robot.h"
#include <Commands/Command.h>

class GoToDesiredSetpointCommand : public frc::Command {
public:
	GoToDesiredSetpointCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	std::shared_ptr<LumberJack> lumberJack;

	bool IsAtDesiredSetpoint = false;
};

#endif  // ElevatorCommand_H
