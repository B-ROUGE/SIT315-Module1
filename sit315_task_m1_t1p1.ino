// Set labels for pins
const uint8_t SEN_PIN = 2;
const uint8_t LED_PIN = 13;

// Set variable to record input state
uint8_t sensorState = LOW;

void setup()
{
  // Set pins as input or output
  pinMode(SEN_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  // Begin recording serial
  Serial.begin(9600);
}

void loop()
{
  // Set input value to variable
  sensorState = digitalRead(SEN_PIN);
  // Change LED based on variabl
  digitalWrite(LED_PIN, sensorState);
  // Display vatiable in serial monitor
  Serial.print("Sensor state: ");
  Serial.println(sensorState);
}