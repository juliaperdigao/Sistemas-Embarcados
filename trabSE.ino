// Includes the Servo library
#include <Servo.h>

// Defines Tirg and Echo pins of the Ultrasonic Sensor
const int trigPin1 = 10;
const int echoPin1 = 11;

const int trigPin2 = 3;
const int echoPin2 = 2;
// Variables for the duration and the distance
long duration;
int distance1;
int distance2;
int distance;

Servo myServo; // Creates a servo object for controlling the servo motor

void setup() {
  pinMode(trigPin1, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin1, INPUT); // Sets the echoPin as an Input
  pinMode(trigPin2, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin2, INPUT);
  Serial.begin(9600);
  myServo.attach(12);// Defines on which pin is the servo motor attached
  pinMode(8,OUTPUT);
}
void loop() {
  // rotates the servo motor from 15 to 165 degrees
  for(int i=15;i<=165;i++){  
  myServo.write(i);
  delay(30);
  distance1 = calculateDistance(trigPin1, echoPin1);// Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree
  distance2 = calculateDistance(trigPin2, echoPin2);
  Serial.print(distance1);
  Serial.print(" ");
  Serial.print(distance2);
  Serial.print(" ");
  distance = (distance1+distance2)/2;
  if(distance < 10) digitalWrite(8,HIGH);
  else digitalWrite(8,LOW);
  Serial.print(distance); // Sends the distance value into the Serial Port
  Serial.println(" cm"); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
  }
  
  // Repeats the previous lines from 165 to 15 degrees
  for(int i=165;i>15;i--){  
  myServo.write(i);
  delay(30);
  distance1 = calculateDistance(trigPin1, echoPin1);
  distance2 = calculateDistance(trigPin2, echoPin2);
  Serial.print(distance1);
  Serial.print(" ");
  Serial.print(distance2);
  Serial.print(" ");
  distance = (distance1+distance2)/2;
  if(distance < 10) digitalWrite(8,HIGH);
  else digitalWrite(8,LOW);
  Serial.print(distance);
  Serial.println(" cm");
  }
}
// Function for calculating the distance measured by the Ultrasonic sensor
int calculateDistance(int trig, int echo){ 
  
  digitalWrite(trig, LOW); 
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trig, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance= duration*0.034/2;
  return distance;
}
