// Import required libraries
#include <ESP8266WiFi.h>
#include <aREST.h>
#include <aREST_UI.h>
#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // twelve servo objects can be created on most boards
 
// Create aREST instance
aREST_UI rest = aREST_UI();

// WiFi parameters
const char* ssid = "lucky";
const char* password = "laxmish53";

// The port to listen for incoming TCP connections
#define LISTEN_PORT           80

// Create an instance of the server
WiFiServer server(LISTEN_PORT);

// Variables to be exposed to the API
int Servo_val;
int potpin = 5;  // analog pin used to connect the potentiometer
int val = 0;    // variable to read the value from the analog pin
int ledControl(String command);
int ServoControl(String val);
void setup(void) {
  // Start Serial
  Serial.begin(115200);

  // Set the title
  rest.title("aREST Servo test");

  // Create button to control pin 5
  rest.button(15);
rest.slider(5);
  // Init variables and expose them to REST API
  Servo_val = val;
  rest.variable("Servo_val", &Servo_val);
  

  // Labels
  rest.label("Servo_val");

  // Function to be exposed
  rest.function("led", ledControl);
    rest.function("Servo", ServoControl);

  // Give name and ID to device
  rest.set_id("1");
  rest.set_name("esp8266");

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
   myservo.attach(2);  // attaches the servo on GIO2 to the servo object 

}

void loop() {
  // Handle REST calls
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while (!client.available()) {
    delay(1);
  }
  rest.handle(client);
//  int pos;
//  for(pos = 0; pos <= 180; pos += 1) // goes from 0 degrees to 180 degrees 
//  {                                  // in steps of 1 degree 
//    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
//    delay(15);                       // waits 15ms for the servo to reach the position 
//  } 
//  for(pos = 180; pos>=0; pos-=1)     // goes from 180 degrees to 0 degrees 
//  {                                
//    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
//    delay(15);                       // waits 15ms for the servo to reach the position 
//  } 
//val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
//  val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
//  myservo.write(val);                  // sets the servo position according to the scaled value
//  delay(15);                           // waits for the servo to get there
}

int ledControl(String command) {
  // Print command
  Serial.println(command);

  // Get state from command
  int state = command.toInt();

  digitalWrite(15, state);
  return 1;
}
int ServoControl(String val) {
  // Print command
  Serial.println(val);
  int servoval = val.toInt();
  // Get state from command
//  int state = command.toInt();
//  return 1;
  servoval = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
  servoval = map(servoval, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  myservo.write(servoval);                  // sets the servo position according to the scaled value
  delay(15);  
  return 1; 
}
