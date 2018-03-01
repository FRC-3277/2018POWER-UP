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
	std::string GameData = Robot::gamestates->GetGameData();

	// Get Switch or Scale from Driver Station
	std::string DecideSwitchOrScale = SmartDashboard::GetString("DB/String 1", "SC");
	std::transform(DecideSwitchOrScale.begin(), DecideSwitchOrScale.end(), DecideSwitchOrScale.begin(), ::toupper);

	// TODO: Handle "E" scenario
	std::string LocationOfRobot = SmartDashboard::GetString("DB/String 0", "E");

	//Do or Do not
	std::string DoAuto = SmartDashboard::GetString("DB/String 3", "");
	DebugLog("D0.5|t500;T-0.3|t0.5;D0.5|t200;ER;GS;S;");

	// TODO: Use the flag to enable/disable time/distance modes.

	//Do or do not
	if (DoAuto.size() != 0)
	{
		switch(LocationOfRobot[0])
		{
			// case 'R' and case 'r' to make Driver Station accept Lowercase or Uppercase characters
			case 'R':
			case 'r':
			{
				if(DecideSwitchOrScale.compare(0, 2, "SC"))
				{
					if(GameData.compare(0, 2, "LR") == 0)
					{
						DebugLog(GameData);
						//LR
						// R2 for Scale
						// Distance: D0.50|d24;E4;GS;D-0.50|d7;T-0.3|d-90.0;D0.50|d1.5;S;
						DebugLog("D0.50|t1100;E4;GS;D-0.50|t700;T-0.3|t500;D0.50|t100.5;S;");
						listOfCommands = Split("D0.50|t1100;E4;GS;D-0.50|t700;T-0.3|t500;D0.50|t100.5;S;", ';');
					}
					if(GameData.compare(0, 2, "LL") == 0)
					{
						//Decide depending on team
						// R4 for Scale
						// Distance: D0.5|d19.5;T-0.3|d-90;D0.5|d15;T0.3|d90;T-0.3|t-90;D0.5|d4;ER;GS;D-0.5|d-6.5;S;
						 listOfCommands = Split("D0.5|t900;T-0.3|t500;D0.5|t700;T0.3|t90;T-0.3|t500;D0.5|t300;ER;GS;D-0.5|t400;S;", ';');
					}
				}
				else
				{
					if(GameData.compare(0, 2, "RR") == 0 || GameData.compare(0, 2, "RL") == 0)
					{
						DebugLog(GameData);
						// Distance modes area in feet
						// Time modes are in milliseconds

						// RR or RL
						// R1 for Switch
						// Distance: D0.5|d11;T-0.3|d-90;D0.5|d4.5;ER;GS;S;
						DebugLog("D0.25|t3000;");//T-0.3|t1000;D-0.5|1000;ER;GS;S;");
						//TODO: Fix this... butchered for testing
						listOfCommands = Split("D0.25|t2000;D0.0|t2000;T-0.3|t1500;D0.25|t2000", ';');//T-0.3|t0.5;D-0.5|t300;ER;GS;S;", ';');
					}
					if(GameData.compare(0, 2, "LL") == 0)
					{
						DebugLog(GameData);
						//LL
						// R3 for Switch
						// Distance: D0.5|d19.5;T-0.3|d-90;D0.5|d15;T0.3|d90;T-0.3|d-90;D0.5|d1;T0.3|d90;D-0.5|d-4;ER;GS;S;
						DebugLog("D0.5|t800;T-0.3|t-90;D0.5|t600;T0.3|t90;T-0.3|t500;D0.5|d1;T0.3|t500;D-0.5|t200;ER;GS;S;");
						listOfCommands = Split("D0.5|t800;T-0.3|t-90;D0.5|t600;T0.3|t90;T-0.3|t500;D0.5|d1;T0.3|t500;D-0.5|t200;ER;GS;S;", ';');
					}
				}
				break;
			}
			case 'L':
			case 'l':
			{
				if(DecideSwitchOrScale.compare(0, 2, "SC"))
				{
					if(GameData.compare(0, 2, "RL") == 0)
					{
						DebugLog(GameData);
						//RL
						// L2 for Scale
						// Distance: D0.5|d24;ER;GS;D-0.5|d-8;T0.3|d90;D0.5|d1;S;
						DebugLog("D0.5|t900;ER;GS;D-0.5|t600;T0.3|t500;D0.5|t0.3;S;");
						listOfCommands = Split("D0.5|t900;ER;GS;D-0.5|t600;T0.3|t500;D0.5|t0.3;S;", ';');
					}
					else
					{
					// TODO: Do this
					// L4 for Scale
					listOfCommands = Split("D0.5|t800;T0.3|t1500;D0.5|d15;T-0.3|t1500;T0.3|t1500;D0.5;D0.5|t1500;ER;GS;D-0.5|t300;S;", ';');
					// Distance: D0.5|d19.5;T0.3|d90;D0.5|d15;T-0.3|d-90;T0.3|d90;D0.5;D0.5|d4;ER;GS;D-0.5|6.5;S;
					}
				}
				else
				{
					if (GameData.compare(0, 2, "LL") == 0 || GameData.compare(0, 2,"LR") == 0)
					{
						//LL or LR
						// L1 for Switch
						// Distance: D0.5|d11;ER;GS;T0.3|d90;D0.5|d3.5;S;
						DebugLog("D0.5|t400;ER;GS;T0.3|t500;D0.5|t250;S;");
						listOfCommands = Split("D0.5|t400;ER;GS;T0.3|t500;D0.5|t250;S;", ';');
					}
					else if(GameData.compare(0, 2, "RR") == 0)
					{
						DebugLog(GameData);
						//RR
						// L3 for Switch
						// Distance: D0.5|19.5;T0.3|d90;D0.5|d15;T-0.3|d-90;T0.3|d90;D0.5|d1;T-0.3|d-90;D-0.5|d-4;ER;GS;S;
						DebugLog("D0.5|t900;T0.3|t500;D0.5|t800;T-0.3|t500;T0.3|t500;D0.5|t0.300;T-0.3|t500;D-0.5|t200;ER;GS;S;");
						listOfCommands = Split("D0.5|t900;T0.3|t500;D0.5|t800;T-0.3|t500;T0.3|t500;D0.5|t0.300;T-0.3|t500;D-0.5|t200;ER;GS;S;", ';');
					}
				}
				break;
			}
			case 'M':
			case 'm':
			{
				if(DecideSwitchOrScale.compare(0, 2, "SC"))
				{
					if(GameData.compare(0, 2, "LR") == 0 || GameData.compare(0, 2, "LL") == 0)
					{
						DebugLog(GameData);
						//LR Or LL
						// M2 for Scale
						// Distance: D0.5|d6;T-0.3|d-90;D0.5|d7;T0.3|d90;D0.5;d6.5;ER;GS;T-0.3|d-90;D0.5|d2;S;
						DebugLog("D0.5|t300;T-0.3|t500;D0.5|t400;T0.3|500;D0.5;t350;ER;GS;T-0.3|t500;D0.5|t100;S;");
						listOfCommands = Split("D0.5|t300;T-0.3|t500;D0.5|t400;T0.3|500;D0.5;t350;ER;GS;T-0.3|t500;D0.5|t100;S;", ';');
					}
				}
				else
				{
					if(GameData.compare(0, 2, "RL") == 0 || GameData.compare(0, 2, "RR") == 0)
					{
						DebugLog(GameData);
						// RL Or RR
						// M1 for Switch
						// Distance: D0.5|d11;ER;GS;S;
						DebugLog("D0.3|t800;ER;GS;S;");
						listOfCommands = Split("D0.5|t3000;ER;GS;S;", ';');
					}
				}
				break;
			}
		}
	}
	else
	{
		listOfCommands = Split("D0.5|t300;", ';');
	}

	for (auto eachCommand : listOfCommands)
	{
		DebugLog("eachCommand: " + eachCommand);
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
	DebugLog("AutonomousScenarios Completed");
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
	DebugLog("ParseDriveTrainBasedCommands");
    // Based on which command is provided one of these will be populated
    double forwardBackward = 0.0;
    double rotation = 0.0;
    double lateral = 0.0;
    double AutonomousDriveWaitPeriod = 0.0;
    double Distance = 0.0;

    std::vector<std::string> listOfParams;

    listOfParams = Split(CommandToParse, '|');
    for (auto eachParam : listOfParams)
    {
    	DebugLog("eachParam: " + eachParam);
        if(eachParam[0] == 'D')
        {
            forwardBackward = -std::stod(eachParam.substr(1, eachParam.size() - 1));
            DebugLog(std::string("Drive speed: ") + eachParam.substr(1, eachParam.size() - 1).c_str());
        }
        if(eachParam[0] == 'T')
        {
            rotation = -std::stod(eachParam.substr(1, eachParam.size() - 1));
            DebugLog(std::string("Turn speed: ") + eachParam.substr(1, eachParam.size() - 1).c_str());
        }
        if(eachParam[0] == 'L')
        {
            lateral = -std::stod(eachParam.substr(1, eachParam.size() - 1));
            DebugLog(std::string("Lateral speed: ") + eachParam.substr(1, eachParam.size() - 1).c_str());
        }
        if(eachParam[0] == 't')
        {
            UseTimeBasedMode = true;
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

    if(EnableDriveTrain)
    {
		if(UseTimeBasedMode)
		{
			std::shared_ptr<AutonomousDriveCommand> autonomousDriveCommand;
			autonomousDriveCommand.reset(new AutonomousDriveCommand(lateral, forwardBackward, rotation, AutonomousDriveWaitPeriod));
			autonomousDriveCommand->Execute();
		}
		else
		{
			// When using distance mode the time period value will override distance traveled as a means of timeout
			//AutonomousDriveCommand(lateral, forwardBackward, rotation, AutonomousDriveWaitPeriod, Distance);
		}
    }
}

// This includes all elevator commands which can be up, down, or to a specified floor setpoint
void AutonomousScenarios::ParseElevatorBasedCommands(const std::string& CommandToParse)
{
	DebugLog("ParseElevatorBasedCommands");
	if(EnableElevator)
	{
		// Safest default value.  No tippy bot.
		int DesiredSetpoint = 0;

		if(CommandToParse[1] == 'R')
		{
			DebugLog("Elevator Up");
			// Get current setpoint and add one
			DesiredSetpoint = Robot::elevator->GetLimitSwitchTracker() + 1;
		}
		else if(CommandToParse[1] == 'L')
		{
			DebugLog("Elevator Down");
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
}

// This includes all grabber commands which can be eat or spit
void AutonomousScenarios::ParseGrabberBasedCommands(const std::string& CommandToParse)
{
	DebugLog("ParseGrabberBasedCommands");
   if(EnableGrabber)
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
}

void AutonomousScenarios::DebugLog(const std::string& msg)
{
	if(EnableAutonomousDebugLogging)
	{
		lumberJack->dLog(msg);
	}
}
