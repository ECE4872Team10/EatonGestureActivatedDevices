#include <iostream>
#include "APDS9960_RPi.h"

using namespace std;

// Pins
#define APDS9960_INT 7 // Needs to be an interrupt pin
#define LED_PIN 11

// Global Functions
void handleGesture();

// Global Variables
APDS9960_RPi apds = APDS9960_RPi();

int main(int argc, char **argv)
{
	wiringPiSetup();
	// Set Interrupt Pin as an input
	pinMode(APDS9960_INT, INPUT);
	// Set LED pin as output
	pinMode(LED_PIN, OUTPUT);
	
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
		if( digitalRead(APDS9960_INT) != 0 )
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
		//cout << apds.readGesture() << endl;
	switch ( apds.readGesture() ) {
	case DIR_UP:
		cout << "UP" << endl;
		// Turn on LED for a half a second
		digitalWrite(LED_PIN, HIGH);
		delay(500);
		digitalWrite(LED_PIN, LOW);
		break;
	case DIR_DOWN:
		cout << "DOWN" << endl;
		// Turn on LED for a half a second
		digitalWrite(LED_PIN, HIGH);
		delay(500);
		digitalWrite(LED_PIN, LOW);
		break;
	case DIR_LEFT:
		cout << "LEFT" << endl;
		// Turn on LED for a half a second
		digitalWrite(LED_PIN, HIGH);
		delay(500);
		digitalWrite(LED_PIN, LOW);
		break;
	case DIR_RIGHT:
		cout << "RIGHT" << endl;
		// Turn on LED for a half a second
		digitalWrite(LED_PIN, HIGH);
		delay(500);
		digitalWrite(LED_PIN, LOW);
		break;
	case DIR_NEAR:
		cout << "NEAR" << endl;
		// Turn on LED for a half a second
		digitalWrite(LED_PIN, HIGH);
		delay(500);
		digitalWrite(LED_PIN, LOW);
		break;
	case DIR_FAR:
		cout << "FAR" << endl;
		// Turn on LED for a half a second
		digitalWrite(LED_PIN, HIGH);
		delay(500);
		digitalWrite(LED_PIN, LOW);
		break;
	default:
		cout << "NONE" << endl;
    }
  }
}
