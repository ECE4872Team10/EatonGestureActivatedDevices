#include <iostream>
#include "APDS9960_RPi.h"

using namespace std;

// Global Functions
void handleGesture();

// Global Variables
const i apds_int = 7; // Interrupt pin
APDS9960_RPi apds = APDS9960_RPi();

int main(int argc, char **argv)
{
	wiringPiSetup();
	// Set Interrupt Pin as an input
	pinMode(apds_int, INPUT); 
	// Initialize APDS-9960 (configure I2C and initial values)
	if( apds.init() ) {
		cout << "APDS-9960 initialization complete" << endl;
	} else {
		cout << "Something went wrong during APDS-9960 init!" << endl;
	}
	
	// Start running the APDS-9960 gesture sensor engine
	if( apds.enableGestureSensor(false) ) {
		cout << "Gesture sensor is now running" << endl;
	} else {
		cout << "Something went wrong during gesture sensor init!" << endl;
	}
	
	while(1)
	{
		if( digitalRead(apds_int) != 0 )
		{
			handleGesture();
		}
		else
		{
			delay(50); // wait 50 ms
		}
	}
	return 0;
}


void handleGesture() {
	//cout << "Reading Gesture" << endl;
	if ( apds.isGestureAvailable() ) {
		cout << "Gesture is available" << endl;
		cout << apds.readGesture() << endl;
	switch ( apds.readGesture() ) {
	case DIR_UP:
		cout << "UP" << endl;
		break;
	case DIR_DOWN:
		cout << "DOWN" << endl;
		break;
	case DIR_LEFT:
		cout << "LEFT" << endl;
		break;
	case DIR_RIGHT:
		cout << "RIGHT" << endl;
		break;
	case DIR_NEAR:
		cout << "NEAR" << endl;
		break;
	case DIR_FAR:
		cout << "FAR" << endl;
		break;
	default:
		cout << "NONE" << endl;
    }
  }
}
