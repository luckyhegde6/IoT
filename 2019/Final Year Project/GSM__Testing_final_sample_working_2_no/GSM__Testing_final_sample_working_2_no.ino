#include<msp430.h> 
int flag=1;
void setup()
{
Serial.begin(9600);
}
void loop()
{
 if(flag == 1)
 {
   sendsms1();
     flag=0;
  }
}
void sendsms1()
{
Serial.println("AT\r\n");
delay(200);
Serial.println("AT+HVOIC;\r\n");
delay(200);
Serial.println("AT+CMGF=1;\r\n");
delay(200);
Serial.println("AT+CMGS=\"9480789220\";\r\n"); //Enter Mobile Number between double " " codes.
delay(200);
Serial.println("Welcome to AFDS\x1A"); //SMS to ur Mobile Number
delay(6000);
Serial.println("\n");
Serial.println("AT+CMGS=\"9036758418\";\r\n"); //Enter Mobile Number between double " " codes.
delay(200);
Serial.println("MSG TO SIM@\x1A"); //SMS to ur Mobile Number
delay(200);
}

