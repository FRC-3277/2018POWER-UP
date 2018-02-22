#include "Camera.h"
#include "../RobotMap.h"

Camera::Camera() : Subsystem("Camera") {

	lumberJack.reset (new LumberJack());

	try
	{
		CameraControllerServo.reset (new Servo(CAMERA_CONTROL_SERVO_ID));
	}
	catch(const std::exception& e)
	{
		lumberJack->eLog(std::string("Servo.reset() failed; ") + std::string(e.what()));
	}

	CameraServer::GetInstance()->StartAutomaticCapture();

	CameraControllerServo->SetAngle(DegreesServoCameraFaceForward);

}

void Camera::InitDefaultCommand()
{

}

void Camera::CameraReverse()
{
	CameraControllerServo->SetAngle(DegreesServoCameraFaceRear);
}

void Camera::CameraForward()
{
	CameraControllerServo->SetAngle(DegreesServoCameraFaceForward);
}
