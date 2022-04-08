#include <WiFi.h>
#include <aREST.h>
#include <aREST_UI.h>

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
int Digital;
float Analog;

int ledControl(String command);

void setup(void) {
  // Start Serial
  Serial.begin(115200);

  // Set the title
  //rest.title("aREST UI Demo");
  rest.title("ESP32 aREST T1");

  // Create button to control pin 5
  //rest.button.label("GPIO 5");
  rest.button(5);
   //rest.button.label("GPIO 21");
  rest.button(21);
 // rest.button.label("GPIO 22");
  rest.slider(22);

  // Init variables and expose them to REST API
  Digital = digitalRead(16);
  Analog = analogRead(4);
  rest.variable("Digital", &Digital);
  rest.variable("Analog", &Analog);

  // Labels
  rest.label("Digital");
  rest.label("Analog");

  // Function to be exposed
  rest.function("led", ledControl);

  // Give name and ID to device
  rest.set_id("1");
  rest.set_name("ESP32");

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
 
     Digital = digitalRead(16);
  Analog = analogRead(4);
  rest.variable("Digital", &Digital);
  rest.variable("Analog", &Analog);
 rest.handle(client);
}

int ledControl(String command) {
  // Print command
  Serial.println(command);

  // Get state from command
  int state = command.toInt();

  digitalWrite(5, state);

  return 1;
}
