#define  C     2100
#define  D     1870 
#define  E     1670
#define  f     1580    // Does not seem to like capital F
#define  G     1400 
// Define a special note, 'R', to represent a rest
#define  R     0


// SETUP ============================================
// Set up speaker on a PWM pin (digital 9, 10 or 11)
int speakerOut = 12;
int led = 13;
int buttonPin = 0;

void setup() {
  pinMode(speakerOut, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(buttonPin, INPUT); 
}

// BUTTON

// Variables will change:
int on = LOW;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers


// MELODY and TIMING  =======================================
//  melody[] is an array of notes, accompanied by beats[],
//  which sets each note's relative length (higher #, longer note)
int melody[] = {E, E, E,R,
E, E, E,R,
E, G, C, D, E, R,
f, f, f,f, f, E, E,E, E, D ,D,E, D, R, G ,R,
E, E, E,R,
E, E, E,R,
E, G, C, D, E, R,
f, f, f,f, f, E, E, E,  G,G, f, D, C,R };


int MAX_COUNT = sizeof(melody) / 2; // Melody length, for looping.

// Set overall tempo
long tempo = 10000;
// Set length of pause between notes
int pause = 1000;
// Loop variable to increase Rest length
int rest_count = 30;

// Initialize core variables
int tone_ = 0;
int beat = 0;
long duration  = 0;

// PLAY TONE  ==============================================
// Pulse the speaker to play a tone for a particular duration
void playTone() {
  long elapsed_time = 0;
  if (tone_ > 0) { // if this isn't a Rest beat, while the tone has
    digitalWrite(led, HIGH);
    //  played less long than 'duration', pulse speaker HIGH and LOW
    while (elapsed_time < duration) {

      digitalWrite(speakerOut,HIGH);
      delayMicroseconds(tone_ / 2);

      // DOWN
      digitalWrite(speakerOut, LOW);
      delayMicroseconds(tone_ / 2);

      // Keep track of how long we pulsed
      elapsed_time += (tone_);
    }
     digitalWrite(led, LOW);

  }
  else { // Rest beat; loop times delay
    for (int j = 0; j < rest_count; j++) { // See NOTE on rest_count
      delayMicroseconds(duration); 
    }    
  }                                
}


void jingleBells(int i){
  // Set up a counter to pull from melody[] and beats[]
    tone_ = melody[i];
    beat = 50;
    duration = beat * tempo; // Set up timing
    playTone();
    // A pause between notes...
    delayMicroseconds(pause);
}


void checkOn(int reading){
  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH),  and you've waited
  // long enough since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
 
   // toggles the ledState variable each time the button is pressed
      if (buttonState == HIGH) {
      on = !on;
    }
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:
    buttonState = reading;
  }
}

// LET THE WILD RUMPUS BEGIN =============================
void loop() {
     // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);
 
  checkOn(reading);

    if(on){
     for (int i=0; i<MAX_COUNT; i++) {
        int loopReading = digitalRead(buttonPin);
         jingleBells(i);
        if(loopReading != reading){
          on = !on;
          break;
        }
     }
   }

  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState = reading;
}
