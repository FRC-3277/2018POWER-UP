#ifndef ToggleFinesseMode_H
#define ToggleFinesseMode_H

#include "LumberJack.h"

#include "Commands/Command.h"
#include "Robot.h"

class ToggleFinesseMode : public frc::Command {
private:
	std::shared_ptr<LumberJack> lumberJack;

public:
	ToggleFinesseMode();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // ToggleFinesseMode_H
