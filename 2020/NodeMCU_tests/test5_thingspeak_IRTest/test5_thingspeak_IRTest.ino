#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* host = "https://api.thingspeak.com/channels/167229"; // Your domain  
String ApiKey = "73HOVD1Q7083NI4W";
String path = "/update?key=WQU1X09CAJ72ZQWN" + ApiKey + "&field1=IR Test";  

const char* ssid = "lucky_home";
const char* pass = "laxmish53";

void setup(void){
  Serial.begin(115200);
  Serial.println("");
  pinMode(14,INPUT);
  pinMode(13,OUTPUT);
  
  WiFi.begin(ssid, pass);
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

int getIRval() {
  int IR;
  IR = digitalRead(14);
  return(IR);
}


void loop() {

  int IRval = getIRval();
  // send IR data to the serial console
  Serial.println(IRval);

  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  client.print(String("GET ") + path + IRval + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: keep-alive\r\n\r\n");
  delay(500);
if (IRval==1)
{ digitalWrite(13,HIGH);
  delay(100);
  digitalWrite(13,LOW);
}
}
