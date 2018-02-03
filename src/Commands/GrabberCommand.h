#ifndef GrabberCommand_H
#define GrabberCommand_H

#include "Robot.h"
#include <Commands/Command.h>

class GrabberCommand : public frc::Command {
public:
	GrabberCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // GrabberCommand_H
