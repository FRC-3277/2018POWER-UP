/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Subsystems/DriveTrain.h>
#include <Drive/MecanumDrive.h>
#include "../RobotMap.h"

#include "../Commands/DriveWithJoystick.h"

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

	// Create a RobotDrive object using PWMS 1, 2, 3, and 4
	robotDrive.reset(new MecanumDrive(*frontLeftTalon, *rearLeftTalon, *frontRightTalon, *rearRightTalon));
	robotDrive->SetExpiration(0.5);
	robotDrive->SetSafetyEnabled(false);

	TimerFinesseBegin = std::chrono::system_clock::now();
	TimerFinesseCurrent = std::chrono::system_clock::now();
}

void DriveTrain::InitDefaultCommand()
{
	SetDefaultCommand(new DriveWithJoystick());
}

void DriveTrain::SetDrive(double lateral, double forwardBackward, double rotation)
{
	if(IsFinesseModeEnabled)
	{
		std::chrono::duration<double> elapsed_seconds = TimerFinesseCurrent - TimerFinesseBegin;
		int DurationMicroseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed_seconds).count();

		if(FinesseReductionWaitPeriod <= DurationMicroseconds)
		{
			TimerFinesseCurrent = std::chrono::system_clock::now();
			CurrentFinesseReduction += FinesseIncrementor;
		}
// TODO: Add Accelerometer Logic
		lateral = lateral * CurrentFinesseReduction;
		forwardBackward = forwardBackward * CurrentFinesseReduction;
		rotation = rotation * CurrentFinesseReduction;
	}

	/* Use the joystick X axis for lateral movement, Y axis for
	 * forward
	 * movement, and Z axis for rotation.
	 */
	robotDrive->DriveCartesian(lateral, forwardBackward, rotation);
}

void DriveTrain::ToggleFinesseMode()
{
	IsFinesseModeEnabled = !IsFinesseModeEnabled;
	CurrentFinesseReduction = MinFinesseReduction;
	TimerFinesseBegin = std::chrono::system_clock::now();

}


