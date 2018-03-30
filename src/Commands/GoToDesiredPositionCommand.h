#ifndef ElevatorCommand_H
#define ElevatorCommand_H

#include "LumberJack.h"

#include "Robot.h"
#include <Commands/Command.h>

class GoToDesiredPositionCommand : public frc::Command {
public:
	GoToDesiredPositionCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	std::shared_ptr<LumberJack> lumberJack;

	int PrintFrequencyCount = 0;
	static constexpr int PrintEveryFrequency = 20;
	double PreviousDesiredPosition = 0.0;
	bool IsElevatorHolding = false;
};

#endif  // ElevatorCommand_H
