#define first_led   9
#define second_led  10
#define third_led   11

#define potentiometer_pin 0
int ADC_val;
double real_voltage_val;

void setup() {
  
  pinMode(first_led, OUTPUT);
  pinMode(second_led, OUTPUT);
  pinMode(third_led, OUTPUT);
  digitalWrite(first_led, LOW);
  digitalWrite(second_led, LOW);
  digitalWrite(third_led, LOW);
  
  Serial.begin(9600);
}

void loop() {
  while(Serial.available() > 0)
  {
    char ledPin = Serial.read();
    int ledState = Serial.parseInt();
    ToggleLed(ledPin, ledState);
  }

  ADC_val = analogRead(potentiometer_pin);
  real_voltage_val = (ADC_val / 1024) * 5;
  Serial.print(real_voltage_val);
  Serial.print(",");
  Serial.flush();
  delay(1000);
}

void ToggleLed(char ledSpec, int ledState)
{
  if (ledSpec == 'f')
  {
    digitalWrite(first_led, ledState);
    delay(100);
    return;
  }
  if (ledSpec == 's')
  {
    digitalWrite(second_led, ledState);
    delay(100);
    return;
  }
  if (ledSpec == 't')
  {
    digitalWrite(third_led, ledState);
    delay(100);
    return;
  }
}
