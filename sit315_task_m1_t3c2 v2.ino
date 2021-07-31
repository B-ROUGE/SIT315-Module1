const uint8_t TOGGLE_PIN = 13;

volatile uint8_t toggleState = LOW;
volatile uint8_t sensorValue = 0;

void setup()
{
  pinMode(A0, INPUT);
  pinMode(TOGGLE_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  // Read analog input and save to variable
  sensorValue = analogRead(A0);
  // Change toggle pin state if analog read over certain threshold
  if(sensorValue > 100)
  {
    toggleState = HIGH;   
  }
  else
  {
    toggleState = LOW;
  }
  digitalWrite(TOGGLE_PIN, toggleState);
  
  Serial.println(toggleState);
  Serial.println(sensorValue);
  Serial.println();
  delay(10);
}

