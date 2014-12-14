#include <WPILib.h>
#include <math.h>
#include "utils.h"
#include "controller.h"
#define FLJAGUARID									4
#define FRJAGUARID									2
#define BLJAGUARID									12
#define BRJAGUARID									13
#define DEADBANDTHERESHOLD							.05
#define COMPRESSORSWITCH							14							
#define COMPRESSORRELAY								1
#define LEFTRAMPSOLENOID							8 //Update
#define RIGHTRAMPSOLENOID							9 //Update
#define PNEUMODETIMER								.25

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
	Compressor compressor;
	Solenoid leftRampSolenoid;
	Solenoid rightRampSolenoid;
	Timer pneuModeTimer;
	
public:
	RobotDemo():
		stick(1), frontLeft(FLJAGUARID), frontRight(FRJAGUARID), backLeft(BLJAGUARID), backRight(BRJAGUARID),
		compressor(COMPRESSORSWITCH, COMPRESSORRELAY), leftRampSolenoid(LEFTRAMPSOLENOID),
		rightRampSolenoid(RIGHTRAMPSOLENOID)
	{
		Watchdog().SetExpiration(1);
		compressor.Start();
	}

	/**
	 * Drive left & right motors for 2 seconds then stop
	 */
	void Autonomous()
	{
		int curPneuMode = 0; // 0 = left blocker, 1 = right blocker, 2 = ramp active
		int tarPneuMode = 0;
		int lastPneuMode = 0;
		pneuModeTimer.Start();
		
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
			
			if (stick.GetRawButton(LEFTBLOCKERID)) // Left blocker
			{
				if (curPneuMode != 1)
				{
					tarPneuMode == 1;
					pneuModeTimer.Reset();
				}
			}
			else if (stick.GetRawButton(RIGHTBLOCKERID)) // Right blocker
			{
				if (curPneuMode != 2)
				{
					tarPneuMode == 2;
					pneuModeTimer.Reset();
				}
			}
			else if (stick.GetRawButton(RAMPID)) // Move Ramp
			{
				if (curPneuMode != 3)
				{
					tarPneuMode == 3;
					pneuModeTimer.Reset();
				}
			}
			
			if (tarPneuMode != curPneuMode)
			{
				leftRampSolenoid.Set(false); //Disable all pneumatics
				rightRampSolenoid.Set(false);
				
			}
			
		}
	}
	
	/**
	 * Runs during test mode
	 */
	void Test() {

	}
};




