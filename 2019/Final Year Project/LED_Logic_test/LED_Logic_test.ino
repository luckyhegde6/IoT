const int a = P1_3;
const int b = P1_4;
const int c = P1_5;
const int d = P1_7;

void setup() {
   Serial.begin(9600); 
  pinMode(a,OUTPUT);
   pinMode(b,OUTPUT);
   pinMode(c,OUTPUT);
   pinMode(d,OUTPUT);  
}

void loop() {
  
  if (Serial.available() > 0) {
    int FAULT = Serial.read();
    
     switch (FAULT) {
    case '1':    
      digitalWrite(a,LOW);   
      digitalWrite(b, HIGH);    
      digitalWrite(c, LOW);   
     digitalWrite(d, LOW);
      break;
    case '2':    
      digitalWrite(a, HIGH);   
      digitalWrite(b, HIGH);    
      digitalWrite(c, HIGH);   
     digitalWrite(d, HIGH);
      break;
    case '3':    
      digitalWrite(a, HIGH);   
      digitalWrite(b, HIGH);    
      digitalWrite(c, HIGH);   
     digitalWrite(d, LOW);
      break;
    case '4':    
     digitalWrite(a, LOW);   
      digitalWrite(b, HIGH);    
      digitalWrite(c, HIGH);   
     digitalWrite(d, HIGH);
      break;
      
    case '5':    
      digitalWrite(a,LOW);   
      digitalWrite(b, LOW);    
      digitalWrite(c, LOW);   
     digitalWrite(d, LOW);
      break;
     }
  }
 }
