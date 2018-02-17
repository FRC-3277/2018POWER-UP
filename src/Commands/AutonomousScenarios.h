#ifndef AutonomousScenarios_H
#define AutonomousScenarios_H

#include "LumberJack.h"
#include "../Robot.h"
#include <Commands/Command.h>

#include "AutonomousDriveCommand.h"
#include "AutonomousEatCubeCommand.h"
#include "AutonomousElevatorToSetpointCommand.h"
#include "AutonomousSpitCubeCommand.h"

class AutonomousScenarios : public frc::Command
{
private:
	std::shared_ptr<LumberJack> lumberJack;

	bool AllDoneWithAutonomousCommands = false;
	bool UseTimeBasedMode = true;

	std::vector<std::string> Split(const std::string& s, char delimiter);
	void ParseDriveTrainBasedCommands(const std::string& CommandToParse, const char Command);
	void ParseElevatorBasedCommands(const std::string& CommandToParse);
	void ParseGrabberBasedCommands(const std::string& CommandToParse);
	void DebugLog(const std::string& msg);

public:
	AutonomousScenarios();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // AutonomousScenarios_H
