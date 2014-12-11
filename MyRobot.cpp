#include "utils.h"
#include <WPILib.h>
#include <math.h>
#define FLJAGUARID				4
#define FRJAGUARID				2
#define BLJAGUARID				12
#define BRJAGUARID				13
#define DEADBANDTHERESHOLD		.05


float DeadBand(float value)
{
	if (fabs(value) < DEADBANDTHERESHOLD)
	{
		return 0;
	}
	else
	{
		return value;
	}
}



class RobotDemo : public SimpleRobot  // Jaguars and such go here
{
	Joystick stick; // only joystick
	
	CANJaguar frontLeft;
	CANJaguar frontRight;
	CANJaguar backLeft;
	CANJaguar backRight;


	
public:
	RobotDemo():
		stick(1), frontLeft(FLJAGUARID), frontRight(FRJAGUARID), backLeft(BLJAGUARID), backRight(BRJAGUARID)
	{
		Watchdog().SetExpiration(1);
	}

	/**
	 * Drive left & right motors for 2 seconds then stop
	 */
	void Autonomous()
	{
		Watchdog().SetEnabled(true);
		
		while (IsAutonomous() && IsEnabled()) 
		{
			Watchdog().Feed();
		}
		
	}

	/**
	 * Runs the motors with arcade steering. 
	 */
	void OperatorControl()
	{
		
		Watchdog().SetEnabled(true);
		
		while (IsOperatorControl())
		{
			Watchdog().Feed();
			
			frontLeft.Set(DeadBand(stick.GetRawAxis(2)));
			backLeft.Set(DeadBand(stick.GetRawAxis(2)));


			frontRight.Set(DeadBand(stick.GetRawAxis(4)));
			backRight.Set(DeadBand(stick.GetRawAxis(4)));
			
		}
	}
	
	/**
	 * Runs during test mode
	 */
	void Test() {

	}
};




