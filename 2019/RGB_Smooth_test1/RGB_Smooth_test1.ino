/*
  Updated Fade RGB LED Smoothly through 7 colours
  Fades an RGB LED using PWM smoothly through 7 different colours pausing for 1 seconds on each colour.
  Re-writted code to non blocking program using timers.
  
  Connect an common Cathode RGB LED with appropriate resistors on each anode to your Arduino Uno; 
  Red to pin 6, Green to pin 5, Blue to pin 3, Cathode to GND.
  
  Developed for Arduino Uno by Joshua David - TechHelpBlog.com
   
  Please Feel Free to adapt and use this code in your projects. 
  Contact me at techhelpblog.com and let me know how you've used it!  
*/

#define GRN_PIN A0
#define RED_PIN A1
#define BLU_PIN A2

byte RED, GREEN, BLUE; 
byte RED_A = 0;
byte GREEN_A = 0; 
byte BLUE_A = 0;
int led_delay = 0;
byte colour_count = 1;                //Count the colours out
#define colour_count_max 7              //Set this to the max number of colours defined
#define colour_delay 4000             //Define the delay between changing colours in ms
#define time_at_colour 1000           //Time to stay on a colour in ms

//Some Time values
unsigned long TIME_LED = 0;
unsigned long TIME_COLOUR = 0;

//Define Colours here.
//Blue
#define C1_R 0
#define C1_G 0
#define C1_B 255
//Red
#define C2_R 255
#define C2_G 0
#define C2_B 0
//White
#define C3_R 255
#define C3_G 255
#define C3_B 255
//Orange
#define C4_R 255
#define C4_G 186
#define C4_B 0
//Light Blue
#define C5_R 0
#define C5_G 168
#define C5_B 255
//Purple
#define C6_R 255
#define C6_G 0
#define C6_B 255
//Yellow
#define C7_R 255
#define C7_G 250
#define C7_B 0

void setup()
{

  //Assign initial values
  RED = C1_R;
  GREEN = C1_G;
  BLUE = C1_B;
  //Get the led_delay speed
  led_delay = (colour_delay - time_at_colour) / 255; 

  analogWrite(GRN_PIN, 0);
  analogWrite(RED_PIN, 0);
  analogWrite(BLU_PIN, 0);

}

void loop()
{

  //Rest of your program - Avoid using delay(); function!

  if(millis() - TIME_LED >= led_delay){
    TIME_LED = millis();

    //Run the LED Function to check and adjust the values
    LED();
  }

  if(millis() - TIME_COLOUR >= colour_delay){
    TIME_COLOUR = millis();

    //Run the Colour Change function
    COLOUR();
  }

}

void LED()
{

  //Check Values and adjust "Active" Value
  if(RED != RED_A){
    if(RED_A > RED) RED_A = RED_A - 1;
    if(RED_A < RED) RED_A++;
  }
  if(GREEN != GREEN_A){
    if(GREEN_A > GREEN) GREEN_A = GREEN_A - 1;
    if(GREEN_A < GREEN) GREEN_A++;
  }
  if(BLUE != BLUE_A){
    if(BLUE_A > BLUE) BLUE_A = BLUE_A - 1;
    if(BLUE_A < BLUE) BLUE_A++;
  }

  //Assign modified values to the pwm outputs for each colour led
  analogWrite(RED_PIN, RED_A);
  analogWrite(GRN_PIN, GREEN_A);
  analogWrite(BLU_PIN, BLUE_A);

}

void COLOUR()
{

  //Increment the colour by one or go back to 1 if maxed out
  if(colour_count < colour_count_max) colour_count++;
  else colour_count = 1;

  if(colour_count == 1){
    RED = C1_R;
    GREEN = C1_G;
    BLUE = C1_B;
  } else if(colour_count == 2){
    RED = C2_R;
    GREEN = C2_G;
    BLUE = C2_B;
  } else if(colour_count == 3){
    RED = C3_R;
    GREEN = C3_G;
    BLUE = C3_B;
  } else if(colour_count == 4){
    RED = C4_R;
    GREEN = C4_G;
    BLUE = C4_B;
  } else if(colour_count == 5){
    RED = C5_R;
    GREEN = C5_G;
    BLUE = C5_B;
  } else if(colour_count == 6){
    RED = C6_R;
    GREEN = C6_G;
    BLUE = C6_B;
  } else if(colour_count == 7){
    RED = C7_R;
    GREEN = C7_G;
    BLUE = C7_B;
  }
}
