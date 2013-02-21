/**
    Author: Noah Owings 
    Date: 2/20/2013
    Copyright: Use it however you want, but don't claim you wrote it.
    
    A simple program for using the HC-SR04 ultrasonic sensor with Arduino.
    
    Requires: 
    * HC-SR04 sensor. 
    * Arduino (tested with Arduino Uno R2). 
    * Breadboard.
    * Jumper Wires.

    Connect VCC to the 5V
    Connect "Trig" to pin 13 (pingPin) 
    Connect "Echo" to 12 (echoPin)
    Connect GND to GND
    
    You can of course change the pin numbers. 
    
    The data sheet says that it is accurate to 4m. This converts to
    23200 uS ping time, so checking for that rids us of many pings which
    time out above 200,000.

*/

// Pin variables
int pingPin = 13; 
int echoPin = 12; 

void setup() {
  Serial.begin(9600); 
  pinMode(pingPin, OUTPUT); 
  pinMode(echoPin, INPUT);
}

void loop() {
  
  // Local variables
  long duration;
  double distance_inch;  
  long maxDuration = 0;
 
  duration = ping(); // get ping in uS
  
  if (duration < 23200 ){ // check ping range (accurate up to 4m = 400cm = 23200 uS)
    // The speed of sound is roughly 340 m/s, which converts to about 74 uS/inch.
    // The ping travels to object and back, so duration is doubled the distance.
    distance_inch = (duration / 74.0 / 2); // convert to inch
    
    if(duration > maxDuration)
      maxDuration = duration;
  }
  
  Serial.print("Max: ");
  Serial.print(maxDuration / 73.746 / 2);
  Serial.print(" inches.\t");
  Serial.print(distance_inch);
  Serial.println(" inch");
  
  delay(300);
}

long ping(){
  digitalWrite(pingPin, LOW); // start with LOW to ensure a clean read
  delayMicroseconds(3);
  digitalWrite(pingPin, HIGH); // Triggers ping
  delayMicroseconds(3);
  digitalWrite(pingPin, LOW); // Stop ping.
  return pulseIn(echoPin, HIGH); // get ping time in uS
}
