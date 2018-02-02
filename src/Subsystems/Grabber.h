#ifndef Grabber_H
#define Grabber_H

#include "WPILib.h"
#include <Commands/Subsystem.h>

class Grabber : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

public:
	Grabber();
	void InitDefaultCommand();
};

#endif  // Grabber_H
