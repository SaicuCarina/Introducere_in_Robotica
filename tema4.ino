const int baudRate = 9600;

// declaram pinii de la joystick
const int pinSW = 2;
const int pinX = A0;  // A0 - analog pin conectat la X
const int pinY = A1;  // A1 - analog pin conectat la Y

// declaram pinii de la segmente
const int pinA = 12;
const int pinB = 10;
const int pinC = 9;
const int pinD = 8;
const int pinE = 7;
const int pinF = 6;
const int pinG = 5;
const int pinDP = 4;

const int pinBuzzer = 3;
int freqBuzzer = 1000; //frecventa pt buzzer
int timeBuzzer = 250; //cat timp face buzzerul sunet

const int segSize = 8; //numarul total de segmente

byte swState = HIGH;
byte lastSwState = LOW;
int xValue = 0;
int yValue = 0;

bool joyMoved = false;
int minThreshold = 400;
int maxThreshold = 600;
int direction = 0;

int currentLocation = 7; //mai intai se incepe de pe segmentul punct
byte currentLocationState = LOW;

const int blinkInterval = 350;
const int repeatTime = 3000;
byte longPress = LOW;

unsigned long previousMillis = 0;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 150;


byte pinStates[segSize] = {
  0, 0, 0, 0, 0, 0, 0, 1 // {A, B, C, D, E, F, G, DP}
};

bool secondStateMatrix[segSize] = {
  0, 0, 0, 0, 0, 0, 0, 0 // {A, B, C, D, E, F, G, DP}
};

int segments[segSize] = {
  12, 10, 9, 8, 7, 6, 5, 4 // {A, B, C, D, E, F, G, DP}
};

// {UP, DOWN, LEFT, RIGHT}
const int movementMatrix[8][4] = {
  { 0, 5, 6, 10 },   // A pin12
  { 12, 5, 6, 0 },   // B pin10
  { 5, 8, 7, 4 },    // C pin9
  { 5, 0, 7, 9 },    // D pin8
  { 5, 8, 0, 9 },    // E pin7
  { 12, 5, 0, 10 },  // F pin6
  { 12, 8, 0, 0 },   // G pin5
  { 0, 0, 9, 0 }     // DP pin4
};

void setup() {
  // initializam pinii
  for (int i = 0; i < segSize; i++) {
    pinMode(segments[i], OUTPUT);
  }
  pinMode(pinSW, INPUT_PULLUP);

  Serial.begin(baudRate);
}

void blink() { //functia de blink face ca segmentul sa palpaie cand suntem pozitionat pe el
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= blinkInterval) {
    previousMillis = currentMillis;
    pinStates[currentLocation] = !pinStates[currentLocation];
    digitalWrite(segments[currentLocation], !currentLocationState);
  }
}

void reset() { //functia reset este apelata cand tinem apasat pe buton si face sa se reseteze codul
//reinitializez variabilele cum erau initial
  currentLocation = 7;
  for (int i = 0; i < segSize; i++) {
    pinStates[i] = 0;
    secondStateMatrix[i] = 0;
  }
  pinStates[currentLocation] = 1;
}

//aici voi verifica cum se misca joystickul si cum trebuie sa mut locatia curenta
void directionFunct(){

  for(int i = 0; i < segSize; i++){
    if( i != currentLocation){ //aici fac ca segemtul sa pulseze chiar daca e HIGH si sunt pe el
      digitalWrite(segments[i], secondStateMatrix[i]); //segmentele apasate raman aprinse
    }
    
  }
  digitalWrite(segments[currentLocation], pinStates[currentLocation]);

  xValue = analogRead(pinX);
  yValue = analogRead(pinY);

  if (minThreshold <= xValue && xValue <= maxThreshold && minThreshold <= yValue && yValue <= maxThreshold) {
    joyMoved = false;
  }
 // verific toate variantele in care se putea misca joystickul 
  if (joyMoved == false) {
    if (xValue > maxThreshold) {
      joyMoved = true;
      direction = 3;  // RIGHT
    } else {
      if (xValue < minThreshold) {
        joyMoved = true;
        direction = 2;  // LEFT
      } else {
        if (yValue < minThreshold) {
          joyMoved = true;
          direction = 0;  // UP
        } else {
          if (yValue > maxThreshold) {
            joyMoved = true;
            direction = 1;  // DOWN
          }
        }
      }
    }
    //daca am mutat joystick ul si pozitia unde l am mutat are un segment care poate sa fie aprins atunci il aprind
    if (movementMatrix[currentLocation][direction] != 0 && joyMoved == true) {
      for(int i = 0; i < segSize; i++){
        if(segments[i] == movementMatrix[currentLocation][direction]){
          currentLocation = i;
          i=9;
        } 
      }
    }
  }
}

void loop() {

  blink(); //apelez functia blink

  //fac debounce pt buton

  int reading = digitalRead(pinSW);

  if (reading != lastSwState) {
    lastDebounceTime = millis(); //lastTime
  }

  if((millis() - lastDebounceTime) > repeatTime){ //verific daca am apasat lung, in cazul in care da, resetez
    if(reading != longPress){
      longPress = reading;
      if(longPress == LOW){
          reset();
      }
    }
  }

  if ((millis() - lastDebounceTime) > debounceDelay) { //daca nu am apasat lung, dar totusi am apasat, schimb valoarea curenta si buzzerul scoate un sunet

    if (reading != swState) {
      swState = reading;

      if (swState == 0) {
        secondStateMatrix[currentLocation] = !secondStateMatrix[currentLocation];
        tone(pinBuzzer, freqBuzzer, timeBuzzer);
      }
    }
  }
  
  lastSwState = reading;

  directionFunct(); //apelez functia pentru directie
}