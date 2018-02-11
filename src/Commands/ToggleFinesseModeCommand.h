#ifndef ToggleFinesseMode_H
#define ToggleFinesseMode_H

#include "LumberJack.h"

#include "Robot.h"
#include "Commands/Command.h"


class ToggleFinesseModeCommand : public frc::Command {
private:
	std::shared_ptr<LumberJack> lumberJack;

public:
	ToggleFinesseModeCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // ToggleFinesseMode_H
