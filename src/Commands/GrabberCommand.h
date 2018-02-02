#ifndef Grabber_H
#define Grabber_H

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

#endif  // Grabber_H
