/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <iostream>
#include <string>

#include "Subsystems/DriveTrain.h"
#include <Drive/MecanumDrive.h>
#include "../RobotMap.h"

#include "../Commands/DriveWithJoystick.h"

DriveTrain::DriveTrain() : frc::Subsystem("DriveTrain")
{
	lumberJack.reset(new LumberJack());

	// Talons
	try
	{
		frontLeftTalon.reset(new WPI_TalonSRX(FRONT_LEFT_MOTOR_CAN_ID));
	}
	catch(const std::exception& e)
	{
		lumberJack->eLog(std::string("frontLeftTalon.reset() failed; ") + std::string(e.what()));
	}

	try
	{
		frontRightTalon.reset(new WPI_TalonSRX(FRONT_RIGHT_MOTOR_CAN_ID));
	}
	catch(const std::exception& e)
	{
		lumberJack->eLog(std::string("frontRightTalon.reset() failed; ") + std::string(e.what()));
	}

	try
	{
		rearLeftTalon.reset(new WPI_TalonSRX(REAR_LEFT_MOTOR_CAN_ID));
	}
	catch(const std::exception& e)
	{
		lumberJack->eLog(std::string("rearLeftTalon.reset() failed; ") + std::string(e.what()));
	}

	try
	{
		rearRightTalon.reset(new WPI_TalonSRX(REAR_RIGHT_MOTOR_CAN_ID));
	}
	catch(const std::exception& e)
	{
		lumberJack->eLog(std::string("rearRightTalon.reset() failed; ") + std::string(e.what()));
	}


	// Set every Talon to reset the motor safety timeout.
	frontLeftTalon->Set(ControlMode::PercentOutput, 0);
	frontRightTalon->Set(ControlMode::PercentOutput, 0);
	rearLeftTalon->Set(ControlMode::PercentOutput, 0);
	rearRightTalon->Set(ControlMode::PercentOutput, 0);

	//Invert Rear Motors
	//Enable for PROD Bot
	rearLeftTalon->SetInverted(true);
	rearRightTalon->SetInverted(true);

	try
	{
		robotDrive.reset(new MecanumDrive(*frontLeftTalon, *rearLeftTalon, *frontRightTalon, *rearRightTalon));
	}
	catch(const std::exception& e)
	{
		lumberJack->eLog(std::string("robotDrive.reset() failed; ") + std::string(e.what()));
	}

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
		// Only need to adjust finesse and use the clock if not at max yet
		if(CurrentFinesseReduction <= MaxFinesseReduction)
		{
			TimerFinesseCurrent = std::chrono::system_clock::now();
			std::chrono::duration<double> elapsed_seconds = TimerFinesseCurrent - TimerFinesseBegin;
			int DurationMicroseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed_seconds).count();

			lumberJack->iLog(std::string("DurationMicroseconds: ") + std::to_string(DurationMicroseconds));
			if(FinesseReductionWaitPeriod <= DurationMicroseconds)
			{
				TimerFinesseBegin = std::chrono::system_clock::now();
				CurrentFinesseReduction += FinesseIncrementor;
				lumberJack->iLog(std::string("CurrentFinesseReduction: ") + std::to_string(CurrentFinesseReduction));
			}
		}

		// TODO: Add Accelerometer Logic
		lateral = lateral * CurrentFinesseReduction;
		forwardBackward = forwardBackward * CurrentFinesseReduction;
		rotation = rotation * CurrentFinesseReduction;
	}

	/* Use the joystick X axis for lateral movement,
	 * Y axis for forward movement,
	 * and Z axis for rotation.
	 */
	std::string driveTrainDebugInfo;
	driveTrainDebugInfo += std::string("Lateral: ") + std::to_string(lateral);
	driveTrainDebugInfo += std::string("ForwardBackward: ") + std::to_string(forwardBackward);
	driveTrainDebugInfo += std::string("Rotation: ") + std::to_string(rotation);
	DebugLog(driveTrainDebugInfo);


	// Last modification before interacting with the drivetrain
	if(InvertDriverControls)
	{
		lateral = -lateral;
		forwardBackward = -forwardBackward;
	}

	robotDrive->DriveCartesian(lateral, forwardBackward, rotation);
}

void DriveTrain::ToggleFinesseMode()
{
	IsFinesseModeEnabled = !IsFinesseModeEnabled;
	lumberJack->iLog(std::string("ToggleFinesseMode: ") + std::to_string(IsFinesseModeEnabled));
	CurrentFinesseReduction = MinFinesseReduction;
	TimerFinesseBegin = std::chrono::system_clock::now();
}

double DriveTrain::ApproxRollingAverage(double CurrentAverage, double CurrentValue)
{
    double NumberOfDataPoints = 100.0;

    CurrentAverage -= CurrentAverage / NumberOfDataPoints;
    CurrentAverage += CurrentValue / NumberOfDataPoints;

    return CurrentAverage;
}

double DriveTrain::ActualAverage(double *Array, int ArraySize)
{
    double sum = 0.0;
    // Maintain the decimal value
    double denominator = ArraySize * 1.0;

    for(int i = 0; i < ArraySize; i++)
    {
        sum += Array[i];
    }

    return sum/denominator;
}

bool DriveTrain::ToggleInvertDriverControls()
{
	InvertDriverControls = !InvertDriverControls;
	lumberJack->iLog(std::string("ToggleInvertDriverControls: ") + std::to_string(InvertDriverControls));
	return InvertDriverControls;
}

void DriveTrain::DebugLog(const std::string& msg)
{
	if(EnableDriveTrainDebugLogging)
	{
		lumberJack->dLog(msg, 20);
	}
}
