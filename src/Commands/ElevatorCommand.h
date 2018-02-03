#ifndef ElevatorCommand_H
#define ElevatorCommand_H

#include <Commands/Command.h>

class ElevatorCommand : public frc::Command {
public:
	ElevatorCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // ElevatorCommand_H
