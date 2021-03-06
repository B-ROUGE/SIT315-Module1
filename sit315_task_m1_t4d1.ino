// In order to convert an analog input to an LOW/HIGH value and utilise
// interrupts I have set an additional Arduino board to perform the conversion.
// The second Arduino board simply takes the value from the photoresistor and
// changes it to a HIGH state value if over 100 and LOW state if under


// Set labels for pins
const uint8_t SEN_PIN1 = 2;
const uint8_t SEN_PIN2 = 3;
const uint8_t LED_PIN1 = 12;
const uint8_t LED_PIN2 = 13;
const uint8_t LED_PIN3 = 11;
const uint8_t LED_PIN4 = 10;

// Set variable to record input state
volatile uint8_t sensor1State = LOW;
volatile uint8_t sensor2State = LOW;
volatile uint8_t timerState = LOW;
volatile uint8_t pcintState = LOW;


void setup()
{
  noInterrupts();
  // Set pins as input or output
  pinMode(SEN_PIN1, INPUT);
  pinMode(SEN_PIN2, INPUT);
  pinMode(LED_PIN1, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
  pinMode(LED_PIN3, OUTPUT);
  pinMode(LED_PIN4, OUTPUT);
  
  // Turn on Port C for Pin Change Interrupt
  PCICR |= 0b00000010;  
  // Turn on PCINT12 (PC4), physical pin 27
  PCMSK1 |= 0b00010000;
  
  // Set an interrupt to occur when a change is detected
  attachInterrupt(digitalPinToInterrupt(SEN_PIN1), pin1_ISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(SEN_PIN2), pin2_ISR, CHANGE);
  // Begin recording serial
  Serial.begin(9600);
  // Start internal timer interrupt
  startTimer();
  interrupts();
}

void loop()
{
  // Display variable in serial monitor
  // Serial.println("Sensor1 - Sensor2 - Timer - PCINT");
  Serial.print(sensor1State);
  Serial.print(sensor2State);
  Serial.print(timerState);
  Serial.print(pcintState);
  Serial.println();
  delay(10);
}

void startTimer(){
  noInterrupts();
  
  // Clear registers
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  
  // Set timer compare based on a frequench of 2MHz
  // and a prescaler of 1024
  OCR1A = ((16000000/2)/1024);
  // Prescaler 1024
  TCCR1B |= (1 << CS12) | (1 << CS10);
  // Enable Timer1 compare Interrupt
  TIMSK1 |= (1 << OCIE1A);
  // CTC
  TCCR1B |= (1 << WGM12);
  
  interrupts();
}

void pin1_ISR()
{
  // Set input value to variable
  sensor1State = digitalRead(SEN_PIN1);
  // Change LED based on state
  digitalWrite(LED_PIN2, sensor1State);
}
void pin2_ISR()
{
  // Set input value to variable
  sensor2State = digitalRead(SEN_PIN2);
  // Change LED based on state
  digitalWrite(LED_PIN1, sensor2State);
}

ISR(TIMER1_COMPA_vect)
{
  // Turn LED on/off when timer interrupt is called
  timerState = !timerState;
  digitalWrite(LED_PIN3, timerState);
}

ISR(PCINT1_vect)
{
  // Turn LED on/off when Pin Change Interrupt is called
  pcintState = !pcintState;
  digitalWrite(LED_PIN4, pcintState);
}