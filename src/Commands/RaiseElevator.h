#ifndef RaiseElevator_H
#define RaiseElevator_H

#include "Robot.h"
#include <Commands/Command.h>

class RaiseElevator : public frc::Command {

public:
	RaiseElevator();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // RaiseElevator_H
