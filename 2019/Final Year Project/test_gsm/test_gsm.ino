#include<msp430.h> 
int flag=1;
void setup()
{
Serial.begin(9600);
}
void loop(){
if(flag)
{
flag=0;
sendsms();
}
}
void sendsms()
{
Serial.println("AT\r\n");
delay(200);
Serial.println("AT+HVOIC;\r\n");
delay(200);
Serial.println("AT+CMGF=1;\r\n");
delay(200);
Serial.println("AT+CMGS=\"9886991029\";\r\n"); //Enter Mobile Number between double " " codes.
delay(200);                                  
Serial.println("L-G Fault found\x1A"); //SMS to ur Mobile Number
delay(200);
}
