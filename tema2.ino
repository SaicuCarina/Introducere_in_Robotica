const int RGBLED_GreenPin = 9;
const int RGBLED_RedPin = 10;
const int RGBLED_BluePin = 11;

const int potPin_Red=A0;
int potRed_Value=0;

const int potPin_Green=A1;
int potGreen_Value=0;

const int potPin_Blue=A2;
int potBlue_Value=0;

float voltage_RedPin = 0.0;
float voltage_GreenPin = 0.0;
float voltage_BluePin = 0.0;

int sensorMin = 0;
int sensorMax = 1023;

int toLow = 0;
int toHigh = 255;

void setup() {

  Serial.begin(9600);

  pinMode(RGBLED_GreenPin, OUTPUT);
  pinMode(RGBLED_RedPin, OUTPUT);
  pinMode(RGBLED_BluePin, OUTPUT);

}

void loop() {

  potRed_Value = analogRead(potPin_Red);
  potGreen_Value = analogRead(potPin_Green);
  potBlue_Value = analogRead(potPin_Blue);

  // voltage_RedPin = (5.0 / 1023.0) * potRed_Value;
  // voltage_GreenPin = (5.0 / 1023.0) * potGreen_Value;
  // voltage_BluePin = (5.0 / 1023.0) * potBlue_Value;

  // Serial.println(voltage_RedPin);
  // Serial.println(voltage_GreenPin);
  // Serial.println(voltage_BluePin);

  // analogWrite(RGBLED_RedPin, voltage_RedPin * 50);
  // analogWrite(RGBLED_GreenPin, voltage_GreenPin * 50);
  // analogWrite(RGBLED_BluePin, voltage_BluePin * 50);

  // partea comentata de mai sus este codul de la laborator modificat pentru tema
  // functioneaza dar nu foloseste functia map()

  voltage_RedPin = map(potRed_Value, sensorMin, sensorMax, toLow, toHigh);
  voltage_GreenPin = map(potGreen_Value, sensorMin, sensorMax, toLow, toHigh);
  voltage_BluePin = map(potBlue_Value, sensorMin, sensorMax, toLow, toHigh);

  analogWrite(RGBLED_RedPin, voltage_RedPin);
  analogWrite(RGBLED_GreenPin, voltage_GreenPin);
  analogWrite(RGBLED_BluePin, voltage_BluePin);

  delay(1);

}
