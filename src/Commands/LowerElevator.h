#ifndef LowerElevator_H
#define LowerElevator_H

#include <Commands/Command.h>

class LowerElevator : public frc::Command {
public:
	LowerElevator();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // LowerElevator_H
