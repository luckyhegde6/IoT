// Output
int redPin = A0;   // Red LED,   connected to Aanlog A0
int grnPin = A1;  // Green LED, connected to Aanlog A1
int bluPin = A2;  // Blue LED,  connected to Aanlog A2

// Color arrays
int black[3]  = { 0, 0, 0 };
int white[3]  = { 100, 100, 100 };
int red[3]    = { 100, 0, 0 };
int green[3]  = { 0, 100, 0 };
int blue[3]   = { 0, 0, 100 };
int yellow[3] = { 40, 95, 0 };
int dimWhite[3] = { 30, 30, 30 };
// etc.
// Set initial color
int redVal = black[0];
int grnVal = black[1]; 
int bluVal = black[2];


void setup()
{
  pinMode(redPin, OUTPUT);   // sets the pins as output
  pinMode(grnPin, OUTPUT);   
  pinMode(bluPin, OUTPUT); 
    Serial.begin(9600);  // ...set up the serial ouput 
  
}

// Main program: list the order of crossfades
void loop()
{
  crossFade(red);
  delay(200);
  crossFade(green);
  delay(200);
  crossFade(blue);
}
 int calculateVal(int val, int i) {
  // Defensive driving: make sure val stays in the range 0-255
  if (val > 255) {
    val = 255;
  } 
  else if (val < 0) {
    val = 0;
  }
  return val;
}
  void crossFade(int color[3]) {
  // Convert to 0-255
  int R = (color[0] * 255) / 100;
  int G = (color[1] * 255) / 100;
  int B = (color[2] * 255) / 100;



  for (int i = 0; i <= 1020; i++) {
    redVal = calculateVal(redVal, i);
    grnVal = calculateVal(grnVal, i);
    bluVal = calculateVal(bluVal, i);

    analogWrite(redPin, redVal);   // Write current values to LED pins
    analogWrite(grnPin, grnVal);      
    analogWrite(bluPin, bluVal);
        Serial.print("Loop/RGB: #");
        Serial.print(i);
        Serial.print(" | ");
        Serial.print(redVal);
        Serial.print(" / ");
        Serial.print(grnVal);
        Serial.print(" / ");  
        Serial.println(bluVal); 

 }
}

