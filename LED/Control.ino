int BLU;
int led = 8;// add the pin number that you want to control.
void setup() 
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  
}
void loop() {
  while (Serial.available()) {
    BLU = Serial.read();
    Serial.println(BLU);
    {
      if (BLU == 1)
        digitalWrite(led, HIGH);
    }
    {
      if (BLU == 0)
        digitalWrite(led, LOW);
    }
  }
}
