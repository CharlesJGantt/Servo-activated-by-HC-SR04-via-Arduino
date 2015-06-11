// Turning NeoPixels on and off using a HC-SRO4 Ping Sensor
/*
   This sketch reads a HC-SR04 ultrasonic rangefinder and returns the
   distance to the closest object in range. To do this, it sends a pulse
   to the sensor to initiate a reading, then listens for a pulse 
   to return.  The length of the returning pulse is proportional to 
   the distance of the object from the sensor.

   The Arduino then takes this information and initiates a series of
   sweeps. A sweep is defined as the servo moving its horn from the
   0 position to 180 and back to 0 then to -180 and back to 0.  

   This code was developed partially from Ping))) code found in the public domain
   written by David A. Mellis, and adapted to the HC-SRO4 by Tautvidas Sipavicius, 
   while other portions were written by Charles Gantt and Curtis Gauger from
   http://www.themakersworkbench.com. 
   
   This code was written for a tutorial on http://www.themakersworkbench.com, 
   and was designed for use in a project built by The Young Makers of Greater Augusta. 
   */

//Tell the Arduino Ide to include the Servo.h library.
#include <Servo.h> 
 
 //Setup the variables for the HC-SR04
 const int trigPin = 6;
 const int echoPin = 7;

 // create servo object to control a servo
 // a maximum of eight servo objects can be created
Servo myservo; 
                 
// variable to store the servo position 
int pos = 0;    

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  
// attaches the servo on pin 9 to the servo object
  myservo.attach(9);  
  
}

void loop()
{
  // establish variables for duration of the ping, 
  // and the distance result in inches and centimeters:
  long duration, inches, cm;
  
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  
  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  
  //Tell the Arduino to print the measurement in the serial console
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  // This if-else statement tells the Arduino at what distance 
  // it should trigger the servo, what the servo should do,
  // and what it should do if the distance is too far away.
   if (inches <= 24)  {sweep(3);
   	
   }
   else if (inches >= 24) {myservo.write(pos);
   }
   
   // Tell the Arduino to wait 0.10 seconds before pinging the 
   // Ultrasonic Sensor again.
   delay(100);
}
// Converts the microseconds reading to Inches
long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}
//Converts the Microseconds Reading to Centimeters
long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

//This sub-routein is what dictates the movement of the servo
void sweep(int NUM_OF_CYCLES) 
  
{ 
// Tells the Arduino to start this loop at 0 and incriment it by 1
// each time the loop completes. This is how the Arduino knows to 
// stop the loop when a specific number of the Sweep routein has been ran.
  for (int j=0; j<NUM_OF_CYCLES; j++)
  for(pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(10);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = 180; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(10);                       // waits 15ms for the servo to reach the position 
  } 
} 
