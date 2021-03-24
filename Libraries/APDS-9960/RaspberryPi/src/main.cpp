#include <iostream>
#include "SparkFun_APDS9960.h"

using namespace std;

//#define APDS9960_INT    2 // Needs to be an interrupt pin
const int Intpin = 7; // Interrupt pin

// Global Functions
void handleGesture();

// Global Variables
SparkFun_APDS9960 apds = SparkFun_APDS9960();

int main(int argc, char **argv)
{
	// Set Interrupt Pin as an input
	pinMode(Intpin, INPUT); 
	// Initialize APDS-9960 (configure I2C and initial values)
	if (apds.init() ) {
		cout << "APDS-9960 initialization complete" << endl;
	} else {
		cout << "Something went wrong during APDS-9960 init!" << endl;
	}
	
	// Start running the APDS-9960 gesture sensor engine
	if ( apds.enableGestureSensor(true) ) {
		cout << "Gesture sensor is now running" << endl;
    } else {
		cout << "Something went wrong during gesture sensor init!" << endl;
	}
	
	while(1)
	{
		if (digitalRead(Intpin) == 0)
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
    if ( apds.isGestureAvailable() ) {
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
