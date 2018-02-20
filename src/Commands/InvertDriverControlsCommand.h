#ifndef InvertDriverControlsCommand_H
#define InvertDriverControlsCommand_H

#include "LumberJack.h"

#include "Robot.h"
#include "Commands/Command.h"

class InvertDriverControlsCommand : public frc::Command {
private:
	std::shared_ptr<LumberJack> lumberJack;

public:
	InvertDriverControlsCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // InvertDriverControlsCommand_H
