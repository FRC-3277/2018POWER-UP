#ifndef RaiseElevator_H
#define RaiseElevator_H

#include <Commands/Command.h>

class RaiseElevator : public frc::Command {
	// TODO: Add preset lift heights (potentially break sensor) - Air Force One Controller
	// TODO: Add limit switches on min/max height
public:
	RaiseElevator();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // RaiseElevator_H
