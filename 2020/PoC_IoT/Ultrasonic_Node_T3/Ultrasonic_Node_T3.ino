#define trigPin 5
#define echoPin 4
#define led LED_BUILTIN
const int numReadings = 10;

int readings[numReadings];      // the readings from the object
int readIndex = 0;              // the index of the current reading
int total = 0; 
int RangePin = A0;
int Range = 0;
//the time we give the sensor to calibrate (10-60 secs according to the datasheet)
boolean obj;
int objval;

int calibrationTime = 10;       
 long duration, distance;
//the time when the sensor outputs a low impulse
long unsigned int lowIn;        
 
//the amount of milliseconds the sensor has to be low
//before we assume all motion has stopped
long unsigned int pause = 5000; 
 
boolean lockLow = true;
boolean takeLowTime; 

void setrange()
{
  for(int r=0;r<20;r++)
    {
     Range = analogRead(RangePin);
     Range = map(Range, 0, 1024, 0, 200);
  // in case the sensor value is outside the range seen during calibration
  Range = constrain(Range, 0, 200);
  Serial.println("Range is:");
  Serial.println(Range);
  delay(1000);
     }
     
    if ((Range>0) && (Range<50))
    {Range = 60;}
}
void setup() {
  Serial.begin (115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);

  setrange();
  Serial.println("Range Set is:");
  Serial.println(Range);
   // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
  //give the sensor some time to calibrate
  Serial.print("calibrating sensor ");
    for(int i = 0; i < calibrationTime; i++){
      Serial.print(".");
      delay(1000);
      }
    Serial.println(" done");
    Serial.println("SENSOR ACTIVE");
    delay(50);
    
    
}

void loop() {
  
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  Motiondetect();
  delay(1000);
  
}

void Motiondetect()
{
  
if (distance >= Range || distance <= 0){
    Serial.println("Out of Range");
    obj = false;
    objval = 0;
    digitalWrite(led, LOW);  //the led visualizes the sensors output pin state
 
       if(takeLowTime){
        lowIn = millis();          //save the time of the transition from high to LOW
        takeLowTime = false;       //make sure this is only done at the start of a LOW phase
        }
       //if the sensor is low for more than the given pause,
       //we assume that no more motion is going to happen
       if(!lockLow && millis() - lowIn > pause)
       { 
           //makes sure this block of code is only executed again after
           //a new motion sequence has been detected
           lockLow = true;                       
           Serial.print("motion ended at ");      //output
           Serial.print((millis() - pause)/1000);
           Serial.println(" sec");
           delay(50);
           }
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");
    obj = true;
    objval = 1;
    digitalWrite(led, LOW);   //the led visualizes the sensors output pin state
       if(lockLow){ 
         //makes sure we wait for a transition to LOW before any further output is made:
         lockLow = false;           
         Serial.println("---");
         Serial.print("motion detected at ");
         Serial.print(millis()/1000);
         Serial.println(" sec");
         delay(50);
         }        
         takeLowTime = true;
         delay(500);
  }
  

 // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = objval;
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }
}
