//Project 9 Fade RGB colors using sin wave
int redLED = A0;
int greenLED = A1;
int blueLED = A2;
int redLevel = 0;
int greenLevel = 0;
int blueLevel = 0;
float counter = 0;
float pi = 3.14159;

void setup(){
  pinMode(redLED,OUTPUT);
  pinMode(greenLED,OUTPUT);
  pinMode(blueLED,OUTPUT);
}

void loop(){
  counter = counter + 1;
  redLevel = sin(counter/100)*1000;
  greenLevel = sin(counter/100 + pi*2/3)*1000;
  blueLevel = sin(counter/100 + pi*4/3)*1000;
  redLevel = map(redLevel,-1000,1000,0,100);
  greenLevel = map(greenLevel,-1000,1000,0,100);
  blueLevel = map(blueLevel,-1000,1000,0,100);
  analogWrite(redLED,redLevel);
  analogWrite(greenLED,greenLevel);
  analogWrite(blueLED,blueLevel);
  delay(10);    
}
