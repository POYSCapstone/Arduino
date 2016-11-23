//Sound Sensor test

int soundPin = 2;
int ledPin = 13;

void setup()
{
  pinMode(ledPin, OUTPUT); 
}

void loop()
{
  if (digitalRead(soundPin) == LOW) {
    digitalWrite(ledPin, HIGH);
    delay(3000);
  } else
    digitalWrite(ledPin, LOW);
}
