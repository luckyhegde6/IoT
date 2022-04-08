int speakerPin = 16;
int length = 26;
char notes[] = "eeeeeeegcde fffffeeeeddedg";
int beats[] = { 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2};

int tempo = 300;
void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    // Flash festive lights
    digitalWrite(12, LOW);
    digitalWrite(14, HIGH);
    delayMicroseconds(tone);
    digitalWrite(14, LOW);
    digitalWrite(13, HIGH);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
    digitalWrite(13, LOW);
    digitalWrite(12, HIGH);
  }
}
void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };
  
  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}
void setup() {
  pinMode(speakerPin, OUTPUT);
   pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
}
void loop() {
  for (int i = 0; i < length; i++) {
    if (notes[i] == ' ') {
      delay(beats[i] * tempo); // rest
    } else {
      playNote(notes[i], beats[i] * tempo);
    }
    
    // pause between notes
    delay(tempo / 2); 
  }
 
}

/*void lights()
{
  // Flash festive lights
    digitalWrite(12, LOW);
    digitalWrite(14, HIGH);
    delay(1);
    digitalWrite(14, LOW);
    digitalWrite(13, HIGH);
    delay(1); 
    digitalWrite(13, LOW);
    digitalWrite(12, HIGH);
    delay(1);
     lights();}*/
