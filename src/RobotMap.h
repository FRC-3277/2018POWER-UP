/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#pragma once

#include "LumberJack.h"

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */

// DriveTrain
static constexpr int FRONT_LEFT_MOTOR_CAN_ID = 2;
static constexpr int FRONT_RIGHT_MOTOR_CAN_ID = 3;
static constexpr int REAR_LEFT_MOTOR_CAN_ID = 4;
static constexpr int REAR_RIGHT_MOTOR_CAN_ID = 5;

// Elevator
static constexpr int ELEVATOR_MOTOR_LEFT_CAN_ID = 10;
static constexpr int ELEVATOR_MOTOR_RIGHT_CAN_ID = 11;
// TODO: Get from motor controller
static constexpr int DROP_END_EFFECTOR_SERVO_ID = 3;
static constexpr int HIGH_LIMIT_SWITCH_ID = 9;
static constexpr int MED_LIMIT_SWITCH_ID = 8;
static constexpr int LOW_LIMIT_SWITCH_ID = 7;

// Grabber
static constexpr int GRABBER_LEFT_MOTOR_CAN_ID = 20;
static constexpr int GRABBER_RIGHT_MOTOR_CAN_ID = 21;
static constexpr int BLOCK_INJECTION_STOP_LIMIT_SWITCH_ID = 0;
static constexpr int BLOCK_EJECTION_STOP_LIMIT_SWITCH_ID = 1;
static constexpr int BLOCK_TILT_UP_STOP_LIMIT_SWITCH_ID = 2;
static constexpr int BLOCK_TILT_DOWN_STOP_LIMIT_SWITCH_ID = 3;

// Lifter
static constexpr int LIFTER_MOTOR_CAN_ID = 22;
static constexpr int LIFTER_LEFT_EJECT_CORE_SERVO_ID = 0;
static constexpr int LIFTER_RIGHT_EJECT_CORE_SERVO_ID = 1;

// Camera
static constexpr int CAMERA_CONTROL_SERVO_ID = 2;

// Disable subsystems for debugging and testing
static constexpr bool EnableDriveTrain = true;
static constexpr bool EnableElevator = true;
static constexpr bool EnableGrabber = true;
static constexpr bool EnableLifter = true;
static constexpr bool EnableCamera = true;

// Enable subsystem or command area focused debug logging.  Requires debug logging severity enabled as well.
static constexpr bool EnableAutonomousDebugLogging = false;
static constexpr bool EnableDriveTrainDebugLogging = false;
static constexpr bool ElevatorDebugLoggingEnabled = false;
