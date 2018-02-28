#ifndef Camera_H
#define Camera_H

#include "LumberJack.h"

#include <Commands/Subsystem.h>

class Camera : public frc::Subsystem {
private:
	std::shared_ptr<LumberJack> lumberJack;
	std::shared_ptr<Servo> CameraControllerServo;

	static constexpr int DegreesServoCameraFaceForward = 0;
	static constexpr int DegreesServoCameraFaceRear = 180;

public:
	Camera();
	void InitDefaultCommand();
	void CameraReverse();
	void CameraForward();
};

#endif  // Camera_H
