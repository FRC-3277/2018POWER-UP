/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Subsystems/Lifter.h"
#include "../RobotMap.h"
#include "ctre/Phoenix.h"

Lifter::Lifter() : frc::Subsystem("Lifter") {
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

	// TODO: If this works then must move to method, create button, and map PWM to robotmap.
	LifterLeftEjectCoreServo.reset(new Servo(LIFTER_LEFT_EJECT_CORE_SERVO_ID));
	LifterRightEjectCoreServo.reset(new Servo(LIFTER_RIGHT_EJECT_CORE_SERVO_ID));

	// Force the servos to set angle to their necessary home when this subsystem initializes
	LifterLeftEjectCoreServo->SetAngle(LeftEjectCoreServoAngleDefault);
	LifterRightEjectCoreServo->SetAngle(RightEjectCoreServoAngleDefault);


	// Set every Talon to reset the motor safety timeout.
	LifterMotor->Set(ControlMode::PercentOutput, 0);
}

void Lifter::InitDefaultCommand() {

}

// This method is timer protected so that it is only available during the last 30 seconds of the match
// Matches are 2 minutes and 15 seconds long.
void Lifter::PrepareLifterCoreForEject()
{
	// TODO: push the elevator down to ground zero prior to running this
	LifterLeftEjectCoreServo->SetAngle(LeftEjectCoreServoAngleDefault - 180);
	LifterRightEjectCoreServo->SetAngle(RightEjectCoreServoAngleDefault + 180);
	IsCorePreparedToBeEjected = true;
}

void Lifter::RunTheWinch()
{
	if(IsCorePreparedToBeEjected)
	{
		LifterMotor->Set(WinchDefaultSpeed);
	}
}

void Lifter::StopTheWinch()
{
	LifterMotor->Set(0.0);
}
