#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define myPeriodic 60 //in sec | Thingspeak pub is 60sec

const char* server = "api.thingspeak.com";
String apiKey ="WJ7PWH7WOV3KQEW0";
const char* MY_SSID = "lucky_home"; 
const char* MY_PWD = "laxmish53";
int sent = 0;
 int IR;
int light;
void setup() {
  Serial.begin(115200);
  connectWifi();
   pinMode(A0,INPUT);
    pinMode(14,INPUT);
  pinMode(13,OUTPUT);
}

void loop() {
  
  IR = digitalRead(14);
  //String tempC = dtostrf(temp, 4, 1, buffer);//handled in sendTemp()
  Serial.print(String(sent)+" IR Value: ");
  Serial.println(IR);
  sendIRData(IR);
  int count = myPeriodic;
  while(count--)
  delay(1000);
  light = analogRead(A0);
  //String tempC = dtostrf(temp, 4, 1, buffer);//handled in sendTemp()
  Serial.print(String(sent)+" light Value: ");
  Serial.println(light);
  sendLDRData(light);
  count = myPeriodic;
  while(count--)
  delay(1000);
}

void connectWifi()
{
  Serial.print("Connecting to "+*MY_SSID);
  WiFi.begin(MY_SSID, MY_PWD);
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("Connected");
  Serial.println("");  
}//end connect

void sendIRData(int val)
{  
   WiFiClient client;
  
   if (client.connect(server, 80)) { // use ip 184.106.153.149 or api.thingspeak.com
   Serial.println("WiFi Client connected ");
   
   String postStr = apiKey;
   postStr += "&field1=";
   postStr += String(IR);
   postStr += "&field2=";
   postStr += String(light);
   postStr += "\r\n\r\n";
   
   client.print("POST /update HTTP/1.1\n");
   client.print("Host: api.thingspeak.com\n");
   client.print("Connection: close\n");
   client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
   client.print("Content-Type: application/x-www-form-urlencoded\n");
   client.print("Content-Length: ");
   client.print(postStr.length());
   client.print("\n\n");
   client.print(postStr);
   delay(1000);
   
   }//end if
   sent++;
 client.stop();
 if (IR==1)
{ digitalWrite(13,HIGH);
  delay(100);
  digitalWrite(13,LOW);
  delay(100);
  digitalWrite(13,HIGH);
  delay(100);
  digitalWrite(13,LOW);
}
}//end send
void sendLDRData(int val)
{  
   WiFiClient client;
  
   if (client.connect(server, 80)) { // use ip 184.106.153.149 or api.thingspeak.com
   Serial.println("WiFi Client connected ");
   
   String postStr = apiKey;
   postStr += "&field2=";
   postStr += String(light);
   postStr += "\r\n\r\n";
   
   client.print("POST /update HTTP/1.1\n");
   client.print("Host: api.thingspeak.com\n");
   client.print("Connection: close\n");
   client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
   client.print("Content-Type: application/x-www-form-urlencoded\n");
   client.print("Content-Length: ");
   client.print(postStr.length());
   client.print("\n\n");
   client.print(postStr);
   delay(1000);
   
   }//end if
   sent++;
 client.stop();
 if (light<500)
{ digitalWrite(13,HIGH);
  delay(300);
  digitalWrite(13,LOW);
  delay(100);
  digitalWrite(13,HIGH);
  delay(300);
  digitalWrite(13,LOW);
}
}//end send
