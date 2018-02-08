#ifndef SpitCubeCommand_H
#define SpitCubeCommand_H

#include "WPILib.h"

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
