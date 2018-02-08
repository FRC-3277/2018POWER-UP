#include "Grabber.h"
#include "../RobotMap.h"
#include <Subsystems/Grabber.h>

Grabber::Grabber()
	: frc::Subsystem("Grabber") {
	//Talons.
	BlockFeedMotor.reset(new WPI_TalonSRX(BLOCK_FEED_MOTOR_CAN_ID));
	TiltMotor.reset(new WPI_TalonSRX(TILT_MOTOR_CAN_ID));

	//Limit Switch
	InjectionStopLimitSwitch.reset(new DigitalInput(BLOCK_INJECTION_STOP_LIMIT_SWITCH_ID));
	EjectionStopLimitSwitch.reset(new DigitalInput(BLOCK_EJECTION_STOP_LIMIT_SWITCH_ID));
	TiltUpStopLimitSwitch.reset(new DigitalInput(BLOCK_TILT_UP_STOP_LIMIT_SWITCH_ID));
	TiltDownStopLimitSwitch.reset(new DigitalInput(BLOCK_TILT_DOWN_STOP_LIMIT_SWITCH_ID));

	// Set every Talon to reset the motor safety timeout.
	BlockFeedMotor->Set(ControlMode::PercentOutput, 0);
	TiltMotor->Set(ControlMode::PercentOutput, 0);


}


void Grabber::InitDefaultCommand() {
}



// TODO: Add Cube Injection Button - Potentially limited by photo sensor to make sure cube in/out
// TODO: Add Cube Ejection Button - Ditto as above :)
// TODO: Add Cube Augmentor tilt up button - Limited by limit switch
// TODO: Add Cube Augmentor tilt down button - Limited by limit switch
