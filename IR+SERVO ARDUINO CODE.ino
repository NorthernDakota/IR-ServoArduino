
/*
 * Bas on Tech
 * This course is part of the courses on https://arduino-tutorials.net
 *  
 * (c) Copyright 2018-2019 - Bas van Dijk / Bas on Tech
 * This code and course is copyrighted. It is not allowed to use these courses commerically
 * without explicit written approval
 * 
 * YouTube:    https://www.youtube.com/c/BasOnTech
 * Facebook:   https://www.facebook.com/BasOnTechChannel
 * Instagram:  https://www.instagram.com/BasOnTech
 * Twitter:    https://twitter.com/BasOnTech
 * 
 * ---------------------------------------------------------------------------
 *  
 * Original code by:
 * http://arcfn.com door Ken Shirriff
 *
 */

/*
 * Modified Code by: 
 * Dakota Vanderwege - Added Servo functionality to be used with Ir-Remote
 */


// Import the IR-remote library and Servo Library
#include <IRremote.h>
#include <Servo.h>

//Below this names the servos and makes them exist

Servo s1Base; // Servo 1 - Will turn the robot arm base left or right

Servo s2ud;  // Servo 2 - Will move the robot arm up or down

Servo s3fb;  // Servo 3 - Will move the robot arm foward or back

Servo s4claw; // Servo 4 - Will open or close the claw on the robot arm

//Below this is to set all variables so that they are able to be used

int pos = 10; // original position

// Each number is every servo, so pos1 for servo1 and posneg1 to move it the opposite way

int pos1 = 0;  // For Servo 1
int posneg1 = 0;

int pos2 = 0;  // For Servo 2
int posneg2 = 0;

int pos3 = 0;  // For Servo 3
int posneg3 = 0;

int pos4 = 0;  // For Servo 4
int posneg4 = 0;


int IrReceiverPin = 12; // The pin that the reciever will connect to, used for reading the buttons                


IRrecv irrecv(IrReceiverPin);           // create a new instance of "irrecv" and save this instance in variabele "IRrecv"
decode_results results;                 // define the variable "results" to store the received button code
                        
void setup()
{
    Serial.begin(9600);                 // Initialise the serial monitor

    s1Base.attach(3); // Sets Servo 1 to pin 3
    s1Base.write(pos); // Moves Servo 1 to Original Pos
    
    s2ud.attach(4); // Sets Servo 2 to pin 4
    s2ud.write(pos); // Moves Servo 2 to Original Pos
    
    s3fb.attach(5); // Sets Servo 3 to pin 5
    s3fb.write(pos); // Moves Servo 3 to Original Pos
    
    s4claw.attach(6); // Sets Servo 4 to pin 6
    s4claw.write(pos); // Moves Servo 4 to Original Pos
    

    // When the IR-remote library crashes we can see it from the shown text
    Serial.println("Starting IR-receiver...");

    irrecv.enableIRIn();      // start the IR-receiver

    Serial.println("IR-receiver active");

}


void loop() {

    // When the IR-receiver receives a signal
    if (irrecv.decode(&results)) {

        // Print the received value as a hexadecimal value
        Serial.println(results.value, HEX);

        // Resume the IR-receiver to listen for new signals
        irrecv.resume();
  
        // Determine which button has been pressed
        switch (results.value) {
            
            // For Servo 1
            case 0xFF18E7:  //Button 2 will make S1-Base go left   
               pos1 = pos += 20;
               s1Base.write(pos1);   
                break;

            case 0xFF7A85:     // button 3 will make S1-Base go Right
               posneg1 = pos -= 50;
               s1Base.write(posneg1);  
                break;

            
            // For Servo 2
            case 0xFF6897:    // button 0 will make s2-ud go down
               pos2 = pos += 20;
               s2ud.write(pos2);
                break;

            case 0xFF30Cf:   // button 1 will make s2-ud go up
               posneg2 = pos -= 20;
               s2ud.write(posneg2);
                break;
            
            
            // For Servo 3
            case 0xFF10EF:   // Button 4 to make s3-fb go foward
               pos3 = pos += 20;
               s3fb.write(pos3);
               break;

            case 0xFF42BD:  // Button 7 to make s3-fb go back
               posneg3 = pos -= 20;
               s3fb.write(posneg3);
               break;


            // for Servo 4
            case 0xFF38C7:   // button 5 for s4-claw
               pos4 = pos += 20;
               s4claw.write(pos4);
               break;

            case 0xFF5AA5:  // Button 6 for s4-claw
               posneg4 = pos -=20;
               s4claw.write(posneg4);
               break;


        }

    }

}