/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Subsystems/Lifter.h"
#include "../RobotMap.h"
#include "ctre/Phoenix.h"

Lifter::Lifter()
	: frc::Subsystem("Lifter") {
	lumberJack.reset(new LumberJack());

	//Lifter
	try
	{
		LifterMotor.reset(new WPI_TalonSRX(LIFTER_MOTOR_CAN_ID));
	}
	catch(const std::exception& e)
	{
		lumberJack->eLog(std::string("LifterMotor.reset() failed; ") + std::string(e.what()));
	}


	// Set every Talon to reset the motor safety timeout.
	LifterMotor->Set(ControlMode::PercentOutput, 0);
}

void Lifter::InitDefaultCommand() {

}

void Lifter::StartLifter() {
	LifterMotor->Set(1.0);
}
