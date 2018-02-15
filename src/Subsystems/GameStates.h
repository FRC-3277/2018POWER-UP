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

class GameStates : public frc::Subsystem {
private:
	std::shared_ptr<LumberJack> lumberJack;
	std::string GameData;
	void GetGameDataFromField();


public:
	GameStates();
	std::string GetGameData();
	void InitDefaultCommand() override;
};

