#ifndef SpitCubeCommand_H
#define SpitCubeCommand_H

#include "LumberJack.h"

#include "Robot.h"
#include "Commands/Command.h"

class SpitCubeCommand : public frc::Command {
public:
	SpitCubeCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // SpitCubeCommand_H
