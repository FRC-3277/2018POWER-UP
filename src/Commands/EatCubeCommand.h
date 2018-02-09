#ifndef EatCubeCommand_H
#define EatCubeCommand_H

#include "Robot.h"
#include "Commands/Command.h"

class EatCubeCommand : public frc::Command {
public:
	EatCubeCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // EatCubeCommand_H
