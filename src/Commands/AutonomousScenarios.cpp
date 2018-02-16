#include "AutonomousScenarios.h"
#include <vector>
#include <iostream>     // std::cout
#include <sstream>      // std::istringstream
#include <string>       // std::string

//TODO: Create validation checks and also default failover scenarios should there be a typo
AutonomousScenarios::AutonomousScenarios()
{
	lumberJack.reset(new LumberJack());
}

void AutonomousScenarios::Initialize()
{

}

void AutonomousScenarios::Execute()
{

/** g-code language (Subject to change)
 * D(forward/backwards) = Drive forwards/backwards
 * T(rotation) = Turn; Positive for Right and Negative for Left
 * L(lateral) = Lateral; Positive for Right and Negative for Left
 * S = Stop Everything
 * ER = Raise Elevator
 * EL = Lower Elevator
 * E(setpoint) = Go to Elevator Preset
 * GE = Eat Cube
 * GS = Spit Cube
 */

	std::vector<std::string> listOfCommands = split("EU;ED;D15;T2;D10;", ';');

	for(auto eachCommand : listOfCommands)
	{
		if(eachCommand[0] == 'D')
		{

		}
		else if(eachCommand[0] == 'T')
		{

		}
		else if(eachCommand[0] == 'L')
		{

		}
		else if(eachCommand[0] == 'S')
		{

		}
		else if(eachCommand[0] == 'E')
		{

		}
		else if(eachCommand[0] == 'G')
		{

		}

	}
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

// Shameless borrowing from https://www.fluentcpp.com/2017/04/21/how-to-split-a-string-in-c/
std::vector<std::string> AutonomousScenarios::split(const std::string& s, char delimiter)
{
   std::vector<std::string> tokens;
   std::string token;
   std::istringstream tokenStream(s);
   while (std::getline(tokenStream, token, delimiter))
   {
      tokens.push_back(token);
   }
   return tokens;
}
