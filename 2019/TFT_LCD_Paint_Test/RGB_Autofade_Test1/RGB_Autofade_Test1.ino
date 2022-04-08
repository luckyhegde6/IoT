/*
RGB LED
*/
 
int redPin = A0;
int greenPin = A1;
int bluePin = A2;
 
//uncomment this line if using a Common Anode LED
#define COMMON_ANODE
 
void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT); 
   Serial.begin(9600);  // ...set up the serial ouput  
}
 
void loop()
{
  setColor(255, 0, 0);  // red
  delay(500);
  setColor(0, 255, 0);  // green
  delay(500);
  setColor(0, 0, 255);  // blue
  delay(500);
  setColor(255, 255, 0);  // yellow
  delay(500);  
  setColor(80, 0, 80);  // purple
  delay(500);
  setColor(0, 255, 255);  // aqua
  delay(500);
 
}
 
void setColor(int red, int green, int blue)
{
  #ifdef COMMON_ANODE
    red = 255 - red;
  int  redVal=red;
    green = 255 - green;
   int grnVal=green;
    blue = 255 - blue;
 int bluVal=blue;
  #endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
  Serial.print("RGB values:");
  Serial.print("R =");
  Serial.print(redVal);
  Serial.print(" G= ");
  Serial.print(grnVal);
  Serial.print(" B= ");  
  Serial.println(bluVal); 
}

/*Try the sketch out and then we will dissect it in some detail......

The sketch starts by specifying which pins are going to be used for each of the colors:
Copy Code
int redPin = 11;
int greenPin = 10;
int bluePin = 9;
The next step is to write the 'setup' function. As we have learnt in earlier lessons, the setup function runs just once after the Arduino has reset. In this case, all it has to do is define the three pins we are using as being outputs.
Copy Code
void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);  
}
Before we take a look at the 'loop' function, lets look at the last function in the sketch.
Copy Code
void setColor(int red, int green, int blue)
{
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}
This function takes three arguments, one for the brightness of the red, green and blue LEDs. In each case the number will be in the range 0 to 255, where 0 means off and 255 means maximum brightness. The function then calls 'analogWrite' to set the brightness of each LED.
If you look at the 'loop' function you can see that we are setting the amount of red, green and blue light that we want to display and then pausing for a second before moving on to the next color.
Copy Code
void loop()
{
  setColor(255, 0, 0);  // red
  delay(1000);
  setColor(0, 255, 0);  // green
  delay(1000);
  setColor(0, 0, 255);  // blue
  delay(1000);
  setColor(255, 255, 0);// yellow
  delay(1000);  
  setColor(80, 0, 80);  // purple
  delay(1000);
  setColor(0, 255, 255);// aqua
  delay(1000);
}
*/
