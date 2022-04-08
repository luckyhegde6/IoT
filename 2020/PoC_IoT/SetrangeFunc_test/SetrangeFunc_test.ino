int RangePin = A0;
int Range = 0;

void setrange()
{
  for(int r=0;r<20;r++)
    {
     Range = analogRead(RangePin);
     Range = map(Range, 0, 1024, 0, 200);
  // in case the sensor value is outside the range seen during calibration
  Range = constrain(Range, 0, 200);
  Serial.println("Range is:");
  Serial.println(Range);
  delay(1000);
     }
     
    if ((Range>0) && (Range<50))
    {Range = 60;}
    
  }
void setup() {
  Serial.begin (115200);
  setrange();
    Serial.println("Range Set is:");
  Serial.println(Range);
}

void loop() {
  // put your main code here, to run repeatedly:

}
