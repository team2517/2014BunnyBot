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
#define LEFTRAMPSOLENOIDA							
#define LEFTRAMPSOLENOIDB							
#define RIGHTRAMPSOLENOIDA							
#define RIGHTRAMPSOLENOIDB		
#define LEFTBLOCKERSOLENOIDA						
#define LEFTBLOCKERSOLENOIDB						
#define RIGHTBLOCKERSOLENOIDA						
#define RIGHTBLOCKERSOLENOIDB						
#define PNEUMODETIMERDELAY							.25

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
	Solenoid leftRampA;
	Solenoid leftRampB;
	Solenoid rightRampA;
	Solenoid rightRampB;
	Solenoid leftBlockA;
	Solenoid leftBlockB;
	Solenoid rightBlockA;
	Solenoid rightBlockB;
	Timer pneuModeTimer;
	
public:
	RobotDemo():
		stick(1), frontLeft(FLJAGUARID), frontRight(FRJAGUARID), backLeft(BLJAGUARID), backRight(BRJAGUARID),
		compressor(COMPRESSORSWITCH, COMPRESSORRELAY), 
		leftRampA(LEFTRAMPSOLENOIDA), leftRampB(LEFTRAMPSOLENOIDB),
		rightRampA(RIGHTRAMPSOLENOIDA), rightRampB(RIGHTRAMPSOLENOIDB),
		leftBlockA(LEFTBLOCKERSOLENOIDA), leftBlockB(LEFTBLOCKERSOLENOIDB),
		rightBlockA(RIGHTBLOCKERSOLENOIDA), rightBlockB(RIGHTBLOCKERSOLENOIDB)
		
	{
		Watchdog().SetExpiration(1); 
		compressor.Start();
	}

	/**
	 * Drive left & right motors for 2 seconds then stop
	 */
	void Autonomous()
	{
		int curPneuMode = 0; // 0 = all disabled (in between rotations), 1 = Left block, 2 = Right block, 3 = ramp
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
			
			if (stick.GetRawButton(RAMPID)) // Move Ramp
			{
				if (curPneuMode != 3)
				{
					tarPneuMode == 3;
					pneuModeTimer.Reset();
				}
			}
			else if (!stick.GetRawButton(RAMPID) && curPneuMode == 3)
			{
				tarPneuMode == lastPneuMode;
				pneuModeTimer.Reset();
			}
			
			if (tarPneuMode != curPneuMode) // Check for button press
			{
				curPneuMode = 0;
				if (pneuModeTimer.Get() >= PNEUMODETIMERDELAY)
				{
					curPneuMode = tarPneuMode;
					if (curPneuMode != 3)
					{
						lastPneuMode = curPneuMode;
					}
				}
			}
			
								// Make sure these are correct
			
			if (curPneuMode == 0) // Everything disabled
			{
				leftRampA.Set(false);
				leftRampB.Set(true);
				rightRampA.Set(false);
				rightRampB.Set(true);
				leftBlockA.Set(false);
				leftBlockB.Set(true);
				rightBlockA.Set(false);
				rightBlockB.Set(true);
			}
			else if (curPneuMode == 1) // Left blocker
			{
				leftRampA.Set(false);
				leftRampB.Set(true);
				rightRampA.Set(false);
				rightRampB.Set(true);
				leftBlockA.Set(true);
				leftBlockB.Set(false);
				rightBlockA.Set(false);
				rightBlockB.Set(true);
			}
			else if (curPneuMode == 2) // Right blocker
			{
				leftRampA.Set(false);
				leftRampB.Set(true);
				rightRampA.Set(false);
				rightRampB.Set(true);
				leftBlockA.Set(false);
				leftBlockB.Set(true);
				rightBlockA.Set(true);
				rightBlockB.Set(false);
			}
			else if (curPneuMode == 2) // Ramp activated
			{
				leftRampA.Set(true);
				leftRampB.Set(false);
				rightRampA.Set(true);
				rightRampB.Set(false);
				leftBlockA.Set(false);
				leftBlockB.Set(true);
				rightBlockA.Set(false);
				rightBlockB.Set(true);
			}
			
		}
	}
	
	/**
	 * Runs during test mode
	 */
	void Test() {

	}
};




