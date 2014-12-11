#include "WPILib.h"
#define FLJaguarID				4
#define FRJaguarID				2
#define BLJaguarID				12
#define BRJaguarID				13


/**
 * This is a demo program showing the use of the RobotBase class.
 * The SimpleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 */ 
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
			
			throttleAxis = stick.GetRawAxis(2);
			turningAxis = stick.GetRawAxis(3);
			
			frontLeft.Set(throttleAxis);
			frontRight.Set(throttleAxis);
			backLeft.Set(throttleAxis);
			backRight.Set(throttleAxis);
			
		}
	}
	
	/**
	 * Runs during test mode
	 */
	void Test() {

	}
};

START_ROBOT_CLASS(RobotDemo);

