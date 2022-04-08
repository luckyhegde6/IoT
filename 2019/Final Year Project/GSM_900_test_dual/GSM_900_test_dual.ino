    //THis code is sending both messages to first number
#include <GSM.h>

#define PINNUMBER ""
const int buttonPin = 4;
const int ledPin1 = 13;  
const int ledPin2 = 12;
int buttonState = 0;

// initialize the library instance
GSM gsmAccess; // include a 'true' parameter for debug enabled
GSM_SMS sms;

// char array of the telephone number to send SMS
const char* number1 = "9036758418"; // enter any two mobile numbers here in international format
const char* number2 = "9480789220";

// char array of the message
char txtMsg[200]="test";

// connection state
boolean notConnected = true;

void setup()
{
  pinMode(ledPin1, OUTPUT); 
  pinMode(ledPin2, OUTPUT);
  pinMode(buttonPin, INPUT); 
  // initialize serial communications
  Serial.begin(9600);

  Serial.println("SMS Messages Sender");

  // Start GSM shield
  // If your SIM has PIN, pass it as a parameter of begin() in quotes
  while(notConnected)
  {
    if(gsmAccess.begin(PINNUMBER)==GSM_READY)
      notConnected = false;
    else
    {
      Serial.println("Not connected");
      delay(1000);
    }
  }
  Serial.println("GSM initialized");
  }

void loop()
{
buttonState = digitalRead(buttonPin);
 {
    sendSMS(); 
 }
}


void sendSMS()
{
digitalWrite(ledPin1, HIGH);
digitalWrite(ledPin2, LOW);
if(buttonState == HIGH) {
  buttonState = 1;
};
if (buttonState == 1) {

  digitalWrite(ledPin2, HIGH);
  delay(1000);

  Serial.print("Message to mobile number: ");
  Serial.println(number1);

  // sms text
  Serial.println("SENDING");
  Serial.println();
  Serial.println("Message:");
  Serial.println(txtMsg);

  // send the message
  sms.beginSMS(number1);
  sms.print(txtMsg);
  Serial.println("\nFirst Message Sent\n");
  digitalWrite(ledPin2, LOW);

  delay (60000);

    digitalWrite(ledPin2, HIGH);
  delay(1000);

  Serial.print("Message to mobile number: ");
  Serial.println(number2);

  // sms text
  Serial.println("SENDING");
  Serial.println();
  Serial.println("Message:");
  Serial.println(txtMsg);
