#ifndef AutonomousScenarios_H
#define AutonomousScenarios_H

#include "LumberJack.h"
#include "Robot.h"
#include <Commands/Command.h>

#include "AutonomousDriveCommand.h"
#include "AutonomousEatCubeCommand.h"
#include "AutonomousElevatorToSetpointCommand.h"
#include "AutonomousSpitCubeCommand.h"

class AutonomousScenarios : public frc::Command
{
private:
	std::shared_ptr<LumberJack> lumberJack;

	std::vector<std::string> split(const std::string& s, char delimiter);
public:
	AutonomousScenarios();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // AutonomousScenarios_H
