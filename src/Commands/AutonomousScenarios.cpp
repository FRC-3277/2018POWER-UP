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
	/** R.O.B. (Robotic Operating Buddy)-code language (Subject to change)
	* D(forwards/backwards) = Drive forwards/backwards speed; Modifiers - (t=time;d=distance)
	* T(rotation) = Turn; Positive for Right and Negative for Left speed; Modifiers - (t=time;d=degrees)
	* L(lateral) = Lateral; Positive for Right and Negative for Left speed; Modifiers - (t=time;d=distance)
	* S = Stop Everything
	* ER = Raise Elevator Up One Level
	* EL = Lower Elevator Down One Level
	* E(setpoint) = Go to Elevator Numbered Setpoint - 0 for floor up to 4
	* GE = Eat Cube
	* GS = Spit Cube
	* Z = Group Command selector (Numberical selection) - //TODO: create groups
	*/

	std::vector<std::string> listOfCommands;

	// Testing command string
	listOfCommands = Split("EU;ED;D15|t12;GE;T2|t5;D10|t6;E3;GS", ';');
	// Distance modes area in feet
	// R1
	// Distance: D0.5|d11;T-0.3|d-90;D0.5|d4.5;ER;GS;S;
	// Time: D0.5|t500;T-0.3|t0.5;D0.5|t200;ER;GS;S;
	// R2
	// Distance: D0.50|d24;E4;GS;D-0.50|d7;T-0.3|d-90.0;D0.50|d1.5;S;
	// Time: D0.50|t2400;E4;GS;D-0.50|t700;T-0.3|t90.0;D0.50|t100.5;S;
	// R3
	// Distance: D0.5|d19.5;ER;GS;D-0.5|d7;T-0.3|d-90;D0.5|d1.5;S;
	// Time: D0.5|t800;ER;GS;D-0.5|t300;T-0.3|d-90;D0.5|d1.5;S;
	// R4

	for (auto eachCommand : listOfCommands)
	{
		DebugLog(eachCommand);
		if(eachCommand[0] == 'D' || eachCommand[0] == 'T' || eachCommand[0] == 'L')
		{
		   ParseDriveTrainBasedCommands(eachCommand, eachCommand[0]);
		}
		else if(eachCommand[0] == 'S')
		{
			// TODO: Create a method for stopping of all the things
			//AutonomousDriveCommand(0.0, 0.0, 0.0, 0.0);
		}
		else if(eachCommand[0] == 'E')
		{
			ParseElevatorBasedCommands(eachCommand);
		}
		else if(eachCommand[0] == 'G')
		{
			ParseGrabberBasedCommands(eachCommand);
		}
	}

	// Once all the commands are issued then its time to report completed
	AllDoneWithAutonomousCommands = true;
}

bool AutonomousScenarios::IsFinished()
{
	return AllDoneWithAutonomousCommands;
}

// Called once after isFinished returns true
void AutonomousScenarios::End()
{
	// TODO: Call the all stop
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutonomousScenarios::Interrupted()
{
	// TODO: Call the all stop
}

// Shameless borrowing from https://www.fluentcpp.com/2017/04/21/how-to-split-a-string-in-c/
std::vector<std::string> AutonomousScenarios::Split(const std::string& s, char delimiter)
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

// TODO: Create a means of providing a command that provides the ability to specify all 3 at one time
// This includes drive forward, reverse, turn, and lateral movements
void AutonomousScenarios::ParseDriveTrainBasedCommands(const std::string& CommandToParse, const char Command)
{
    // Based on which command is provided one of these will be populated
    double forwardBackward = 0.0;
    double rotation = 0.0;
    double lateral = 0.0;
    double AutonomousDriveWaitPeriod = 0.0;
    double Distance = 0.0;
    bool useDistanceMode = true;

    std::vector<std::string> listOfParams;

    listOfParams = Split(CommandToParse, '|');
    for (auto eachParam : listOfParams)
    {
        if(eachParam[0] == 'D')
        {
            forwardBackward = std::stod(eachParam.substr(1, eachParam.size() - 1));
            DebugLog(std::string("Drive speed: ") + eachParam.substr(1, eachParam.size() - 1).c_str());
        }
        if(eachParam[0] == 'T')
        {
            rotation = std::stod(eachParam.substr(1, eachParam.size() - 1));
            DebugLog(std::string("Turn speed: ") + eachParam.substr(1, eachParam.size() - 1).c_str());
        }
        if(eachParam[0] == 'L')
        {
            lateral = std::stod(eachParam.substr(1, eachParam.size() - 1));
            DebugLog(std::string("Lateral speed: ") + eachParam.substr(1, eachParam.size() - 1).c_str());
        }
        if(eachParam[0] == 't')
        {
            useDistanceMode = false;
            AutonomousDriveWaitPeriod = std::stod(eachParam.substr(1, eachParam.size() - 1));
            DebugLog(std::string("Time: ") + eachParam.substr(1, eachParam.size() - 1).c_str());
        }
        if(eachParam[0] == 'd')
        {
            //TODO: Create distance method.  Requires encoders
        	// If rotation, then distance is a measure of degrees
            Distance = std::stod(eachParam.substr(1, eachParam.size() - 1));
            DebugLog(std::string("Distance: ") + eachParam.substr(1, eachParam.size() - 1).c_str());
        }
    }

	if(useDistanceMode)
	{
		// When using distance mode the time period value will override distance traveled as a means of timeout
		//AutonomousDriveCommand(lateral, forwardBackward, rotation, AutonomousDriveWaitPeriod, Distance);
	}
	else
	{
		AutonomousDriveCommand(lateral, forwardBackward, rotation, AutonomousDriveWaitPeriod);
	}
}

// This includes all elevator commands which can be up, down, or to a specified floor setpoint
void AutonomousScenarios::ParseElevatorBasedCommands(const std::string& CommandToParse)
{
    // Safest default value.  No tippy bot.
    int DesiredSetpoint = 0;

    if(CommandToParse[1] == 'U')
    {
        DebugLog("Elevator Up\n");
        // Get current setpoint and add one
        DesiredSetpoint = Robot::elevator->GetLimitSwitchTracker() + 1;
    }
    else if(CommandToParse[1] == 'L')
    {
        DebugLog("Elevator Down\n");
        // Get current setpoint and subtract one
        DesiredSetpoint = Robot::elevator->GetLimitSwitchTracker() - 1;
    }
    else
    {
        DebugLog(std::string("Elevator Setpoint: ") + CommandToParse.substr(1, CommandToParse.size() - 1));
        // Since neither up nor down then setpoint
        DesiredSetpoint = std::stoi(CommandToParse.substr(1, CommandToParse.size() - 1));
    }

    AutonomousElevatorToSetpointCommand GoElevator { DesiredSetpoint };
}

// This includes all grabber commands which can be eat or spit
void AutonomousScenarios::ParseGrabberBasedCommands(const std::string& CommandToParse)
{
    if(CommandToParse[1] == 'E')
    {
        DebugLog("Grabber Eat\n");
        AutonomousEatCubeCommand();
    }
    else if(CommandToParse[1] == 'S')
    {
        DebugLog("Grabber Spit\n");
        AutonomousSpitCubeCommand();
    }
}

void AutonomousScenarios::DebugLog(const std::string& msg)
{
	if(Robot::EnableAutonomousDebugLogging)
	{
		lumberJack->dLog(msg);
	}
}
