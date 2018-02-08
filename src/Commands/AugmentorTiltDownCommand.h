#ifndef AugmentorTiltDownCommand_H
#define AugmentorTiltDownCommand_H

#include "WPILib.h"

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
