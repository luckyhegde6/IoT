
const int buttonPin1 = PUSH2;     // the number of the pushbutton pin
const int buttonPin2 = P1_7;     // the number of the pushbutton pin
const int ledPin1 =  GREEN_LED;      // the number of the LED pin
const int ledPin2 =  RED_LED;      // the number of the LED pin

// variables will change:
int buttonState1 = 0;         // variable for reading the pushbutton status
int buttonState2 = 0;         // variable for reading the pushbutton status

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin1, OUTPUT);  
pinMode(ledPin2, OUTPUT);    
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin1, INPUT_PULLUP);
    pinMode(buttonPin2, INPUT_PULLUP);
 Serial.begin(9600);   
}

void loop(){
  // read the state of the pushbutton value:
  buttonState1 = digitalRead(buttonPin1);
buttonState2 = digitalRead(buttonPin2);
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState1 == LOW) {     
    // turn LED on:    
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, LOW);
     Serial.println("\n");
     Serial.println("button1 =\n");
     delay(500);  
     Serial.println("\n");
   Serial.print(buttonState1);
 delay(500);
 Serial.println("\n");
  Serial.println("\nbutton2 =");
     delay(500);  
     Serial.println("\n");
   Serial.print(buttonState2);
   delay(500); 
  } 
  else if (buttonState2 == LOW){
    // turn LED off:
    digitalWrite(ledPin1, LOW); 
    digitalWrite(ledPin2, HIGH);
     Serial.println("\n");
     Serial.println("button2 =\n");
     delay(500);  
   Serial.print(buttonState2);
   delay(500);  
    Serial.println("button1 =\n");
     delay(500);  
   Serial.print(buttonState1);
 delay(500); 
  }
  else {
    // turn LED off:
    digitalWrite(ledPin1, LOW); 
    digitalWrite(ledPin2, LOW);
  }
}
