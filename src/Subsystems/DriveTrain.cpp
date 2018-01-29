/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Subsystems/DriveTrain.h>
#include "../RobotMap.h"

DriveTrain::DriveTrain()
    : frc::Subsystem("DriveTrain") {
	// Talons
	frontLeftTalon.reset(new WPI_TalonSRX(FRONT_LEFT_MOTOR_CAN_ID));
	frontRightTalon.reset(new WPI_TalonSRX(FRONT_RIGHT_MOTOR_CAN_ID));
	rearLeftTalon.reset(new WPI_TalonSRX(REAR_LEFT_MOTOR_CAN_ID));
	rearRightTalon.reset(new WPI_TalonSRX(REAR_RIGHT_MOTOR_CAN_ID));

	// Set every Talon to reset the motor safety timeout.
	frontLeftTalon->Set(ControlMode::PercentOutput, 0);
	frontRightTalon->Set(ControlMode::PercentOutput, 0);
	rearLeftTalon->Set(ControlMode::PercentOutput, 0);
	rearRightTalon->Set(ControlMode::PercentOutput, 0);

	// Invert Right Side
	frontRightTalon->SetInverted(true);
	rearRightTalon->SetInverted(true);

	// Create a RobotDrive object using PWMS 1, 2, 3, and 4
	robotDrive.reset(new MecanumDrive(*frontLeftTalon, *rearLeftTalon, *frontRightTalon, *rearRightTalon));
	robotDrive->SetExpiration(0.5);
	robotDrive->SetSafetyEnabled(false);
}

void DriveTrain::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
