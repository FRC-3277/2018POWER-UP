/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <Commands/Subsystem.h>
#include <string>
#include "LumberJack.h"

// http://wpilib.screenstepslive.com/s/currentCS/m/getting_started/l/826278-2018-game-data-details
class GameStates : public frc::Subsystem
{
private:
	std::shared_ptr<LumberJack> lumberJack;
	std::string GameData;
	std::string GameDataTemp;
	void GetGameDataFromField();
	bool GameDataFullyPopulated = false;
	bool GameDataChanged = false;

public:
	GameStates();
	std::string GetGameData();
	void InitDefaultCommand() override;
	// Game data is assumed to be ready when number of characters
	// available is greater or equal to 3
	// In summary, the number of the count shall be 3 https://www.youtube.com/watch?v=xOrgLj9lOwk
	bool IsGameDataReady();
};

