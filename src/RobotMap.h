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
static constexpr int MAX_HEIGHT_LIMIT_SWITCH_ID = 10;
static constexpr int MIN_HEIGHT_LIMIT_SWITCH_ID = 11;
static constexpr int DROP_END_EFFECTOR_SERVO = 5;
static constexpr int HIGH_LIMIT_SWITCH_ID = 7;
static constexpr int MED_LIMIT_SWITCH_ID = 8;
static constexpr int LOW_LIMIT_SWITCH_ID = 9;


// Grabber
static constexpr int TILT_MOTOR_CAN_ID = 20;
static constexpr int BLOCK_FEED_MOTOR_CAN_ID = 21;
static constexpr int BLOCK_INJECTION_STOP_LIMIT_SWITCH_ID = 0;
static constexpr int BLOCK_EJECTION_STOP_LIMIT_SWITCH_ID = 1;
static constexpr int BLOCK_TILT_UP_STOP_LIMIT_SWITCH_ID = 2;
static constexpr int BLOCK_TILT_DOWN_STOP_LIMIT_SWITCH_ID = 3;

// Lifter
static constexpr int LIFTER_MOTOR_CAN_ID = 22;
