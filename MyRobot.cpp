#include "WPILib.h"
#include "utils.h"
#define FLJAGUARID				4
#define FRJAGUARID				2
#define BLJAGUARID				12
#define BRJAGUARID				13




class RobotDemo : public SimpleRobot  // Jaguars and such go here
{
	Joystick stick; // only joystick
	
	CANJaguar frontLeft;
	CANJaguar frontRight;
	CANJaguar backLeft;
	CANJaguar backRight;


	
public:
	RobotDemo():
		stick(1), frontLeft(FLJaguarID), frontRight(FRJaguarID), backLeft(BLJaguarID), backRight(BRJaguarID)
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
			
			frontLeft.Set(stick.GetRawAxis(2));
			backLeft.Set(stick.GetRawAxis(2));


			frontRight.Set(stick.GetRawAxis(4));
			backRight.Set(stick.GetRawAxis(4));
			
		}
	}
	
	/**
	 * Runs during test mode
	 */
	void Test() {

	}
};

float DeadBand()


START_ROBOT_CLASS(RobotDemo);

