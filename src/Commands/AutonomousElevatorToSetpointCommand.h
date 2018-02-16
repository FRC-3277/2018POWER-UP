#ifndef AutonomousElevatorToSetpointCommand_H
#define AutonomousElevatorToSetpointCommand_H

#include "LumberJack.h"
#include "Robot.h"
#include <Commands/Command.h>

class AutonomousElevatorToSetpointCommand : public frc::Command
{
private:
	int DesiredSetpoint;
public:
	// Provide the setpoint where the elevator is desired to go to.  0 is bottom floor.
	AutonomousElevatorToSetpointCommand(int DesiredSetpoint);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // AutonomousElevatorToSetpointCommand_H
