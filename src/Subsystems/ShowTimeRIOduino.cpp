/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "ShowTimeRIOduino.h"
#include "../RobotMap.h"


ShowTimeRIOduino::ShowTimeRIOduino() : Subsystem("ShowTimeRIOduino") {
	// https://www.chiefdelphi.com/forums/showthread.php?t=132572

	I2C_Coms.reset(new I2C(I2C::Port::kMXP, I2C_Channel));

}

void ShowTimeRIOduino::InitDefaultCommand() {

}

void ShowTimeRIOduino::ShowTimeRIOduino::Alive()
{
	std::string WriteString = std::string("ok");
	uint8_t OutCharArr[] = WriteString.c_str() };
	uint8_t InCharArr[8] = { 0 };

	I2C_Coms->Transaction(OutCharArr, sizeof(OutCharArr), InCharArr, sizeof(InCharArr));
}
