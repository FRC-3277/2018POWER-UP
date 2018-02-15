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
	GameDataTemp = frc::DriverStation::GetInstance().GetGameSpecificMessage();
}

void GameStates::InitDefaultCommand() {

}

void GameStates::GetGameDataFromField() {
	if(GameDataTemp.compare(GameData) != 0)
	{
		GameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();

		if(GameDataFullyPopulated)
		{
			// Not sure if this could happen, but here just in case
			SmartDashboard::PutString("DB/String 9", GameData + std::string(" changed from ") + GameDataTemp);
			lumberJack->wLog(std::string("GameData: ") + GameData + std::string(" changed from ") + GameDataTemp);
			GameDataChanged = true;
		}
	}

	GameDataTemp = frc::DriverStation::GetInstance().GetGameSpecificMessage();
}

std::string GameStates::GetGameData()
{
	GetGameDataFromField();

	if(GameData.size() >= 3 && GameDataFullyPopulated == false)
	{
		lumberJack->iLog(std::string("GameData: ") + GameData);
		SmartDashboard::PutString("DB/String 9", GameData);
		GameDataFullyPopulated = true;
	}

	return GameData;
}

bool GameStates::IsGameDataReady()
{
	return GameDataFullyPopulated;
}
