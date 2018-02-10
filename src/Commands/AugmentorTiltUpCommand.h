#ifndef AugmentorTiltUpCommand_H
#define AugmentorTiltUpCommand_H

#include "LumberJack.h"

#include "Robot.h"
#include "Commands/Command.h"

class AugmentorTiltUpCommand : public frc::Command {
public:
	AugmentorTiltUpCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // AugmentorTiltUpCommand_H
