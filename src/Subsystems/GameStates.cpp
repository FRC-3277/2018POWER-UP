/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "GameStates.h"
#include "../RobotMap.h"

GameStates::GameStates() : Subsystem("GameStates") {
	lumberJack.reset(new LumberJack());
}

void GameStates::InitDefaultCommand() {

}

void GameStates::GetGameDataFromField() {
	GameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
}

std::string GameStates::GetGameData() {
	if(GameData.size() >= 3)
	{
		GetGameDataFromField();
		lumberJack->iLog(std::string("GameData: ") + GameData);
	}

	return GameData;
}
