#include <Servo.h> 
//define the pins
#define LED LED_BUILTIN
int PIR = 13;
int Buzzer = 5;
Servo myservo;  // create servo object to control a servo 
                // twelve servo objects can be created on most boards
 
void setup() {
  Serial.begin(115200);
  //define the LED and Buzzer pin as output
  pinMode(LED, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  //define the sensor pin as input
  pinMode(PIR, INPUT);
   myservo.attach(2);  // attaches the servo on GIO2 to the servo object 

}

void loop() {
  //using the digitalRead function we will read the signal of the sensor
  int value = digitalRead(PIR);
  delay(1000);
  int pos;

  //if its high or if an any object is detected it will activate the LED and Buzzer
  if (value == HIGH){
    digitalWrite(LED, HIGH);
    digitalWrite(Buzzer, HIGH);
    Serial.println(value);
    Serial.println("Motion Detected");
    
  for(pos = 0; pos <= 180; pos += 1) // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 

  }
  else {
    digitalWrite(LED, LOW);
    digitalWrite(Buzzer, LOW);
    Serial.println(value);
    
  for(pos = 180; pos>=0; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  }
}
