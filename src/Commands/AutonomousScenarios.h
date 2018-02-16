#ifndef AutonomousScenarios_H
#define AutonomousScenarios_H

#include "../CommandBase.h"

class AutonomousScenarios : public CommandBase {
public:
	AutonomousScenarios();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // AutonomousScenarios_H
