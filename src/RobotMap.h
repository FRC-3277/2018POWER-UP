/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */

// DriveTrain
static constexpr int FRONT_LEFT_MOTOR_CAN_ID = 1;
static constexpr int FRONT_RIGHT_MOTOR_CAN_ID = 2;
static constexpr int REAR_LEFT_MOTOR_CAN_ID = 3;
static constexpr int REAR_RIGHT_MOTOR_CAN_ID = 4;

// Grabber
static constexpr int TILT_MOTOR_CAN_ID = 5;
static constexpr int BLOCK_FEED_MOTOR_CAN_ID = 6;
