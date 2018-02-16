#include "AutonomousScenarios.h"

AutonomousScenarios::AutonomousScenarios()
{
	lumberJack.reset(new LumberJack());
}

void AutonomousScenarios::Initialize()
{

}

void AutonomousScenarios::Execute()
{

}

bool AutonomousScenarios::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void AutonomousScenarios::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutonomousScenarios::Interrupted()
{

}
