#ifndef AugmentorTiltDownCommand_H
#define AugmentorTiltDownCommand_H

#include "LumberJack.h"

#include "Robot.h"
#include "Commands/Command.h"

class AugmentorTiltDownCommand : public frc::Command {
public:
	AugmentorTiltDownCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // AugmentorTiltDownCommand_H
