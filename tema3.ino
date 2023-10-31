//LEVEL1

const int Button_Level1 = 2;
const int LED_Level1 = 3;

byte stateLED1 = 1; //la inceput liftul este la primul etaj
byte stateButton1 = 0;

byte readingButton1 = 0;
byte lastReadingB1 = 0;

unsigned int lastDebounceTimeB1 = 0;


//LEVEL2

const int Button_Level2 = 4;
const int LED_Level2 = 5;

byte stateLED2 = 0;
byte stateButton2 = 0;

byte readingButton2 = 0;
byte lastReadingB2 = 0;

unsigned int lastDebounceTimeB2 = 0;


//LEVEL3

const int Button_Level3 = 7;
const int LED_Level3 = 6;

byte stateLED3 = 0;
byte stateButton3 = 0;

byte readingButton3 = 0;
byte lastReadingB3 = 0;

unsigned int lastDebounceTimeB3 = 0;


//extra

const int LED_Move = 9;

int open = 1; //usa e deschisa
int travelStartTime;
int step = 0;
int Move = 0;
int timeBetween_Blink = 500;

unsigned int debounceDelay = 50;

//buzzer

const int buzzer = 10;

int freqBuzzer_Stay = 1000;
int timeBuzzer_Stay = 500;

int freqBuzzer_Move = 1500;
int timeBuzzer_Move = 4000;
 

void setup() {

  pinMode(LED_Level1, OUTPUT);
  pinMode(Button_Level1, INPUT_PULLUP);

  pinMode(LED_Level2, OUTPUT);
  pinMode(Button_Level2, INPUT_PULLUP);

  pinMode(LED_Level3, OUTPUT);
  pinMode(Button_Level3, INPUT_PULLUP);

  pinMode(LED_Move, OUTPUT);

}

void Start(){
    if(open == 1){
      stateButton1 = !stateButton1;
      stateButton2 = !stateButton2;
      stateButton3 = !stateButton3; 
    }
}

void SwitchLevels(){
  analogWrite(LED_Move, HIGH);
  delay(timeBetween_Blink);
  analogWrite(LED_Move, LOW);
  delay(timeBetween_Blink);
}

void SwitchLevels_inter(const int LED){
  analogWrite(LED_Move, HIGH);
  analogWrite(LED, HIGH);
  delay(timeBetween_Blink);
  analogWrite(LED_Move, LOW);
  analogWrite(LED, LOW);
  delay(timeBetween_Blink);
}

void loop() {

  analogWrite(LED_Level1, stateLED1);
  analogWrite(LED_Level2, stateLED2);
  analogWrite(LED_Level3, stateLED3);

  readingButton1 = digitalRead(Button_Level1);

  if(readingButton1 != lastReadingB1){
    lastDebounceTimeB1 = millis();
  }
  if((millis() - lastDebounceTimeB1) > debounceDelay) {
    if(readingButton1 != stateButton1){
      stateButton1 = readingButton1;

      if(stateButton1 == LOW){
        stateLED1 = !stateLED1;
      }
    }
  }
  lastReadingB1 = readingButton1;

  ////////////////////////////////////////////////////////////////

  readingButton2 = digitalRead(Button_Level2);

  if(readingButton2 != lastReadingB2){
    lastDebounceTimeB2 = millis();
  }
  if((millis() - lastDebounceTimeB2) > debounceDelay) {
    if(readingButton2 != stateButton2){
      stateButton2 = readingButton2;

      if(stateButton2 == LOW){
        stateLED2 = !stateLED2;
      }
    }
  }
  lastReadingB2 = readingButton2;

  ////////////////////////////////////////////////////////////////

  readingButton3 = digitalRead(Button_Level3);

  if(readingButton3 != lastReadingB3){
    lastDebounceTimeB3 = millis();
  }
  if((millis() - lastDebounceTimeB3) > debounceDelay) {
    if(readingButton3 != stateButton3){
      stateButton3 = readingButton3;

      if(stateButton3 == LOW){
        stateLED3 = !stateLED3;
      }
    }
  }
  lastReadingB3 = readingButton3;

  Start();

  ////////////////////////////////////////////////////////////////

  switch(step){

    case 0:
          if(stateButton1 == 1){
            travelStartTime= millis();
            analogWrite(LED_Move, HIGH);
            step= 1;
          }
          if(stateButton2 == 1){
            travelStartTime= millis();
            analogWrite(LED_Move, HIGH);
            step = 1;
          }
          if(stateButton3 == 1){
            travelStartTime= millis();
            analogWrite(LED_Move, HIGH);
            step = 1;
          }
          break;
    case 1:
////////////daca liftul este la etajul 1 si sta
          if(stateLED1 == 1)
          {
            if(stateButton1 == 1){
              tone(buzzer, freqBuzzer_Stay, timeBuzzer_Stay);
              break;
            }
            if(stateButton2 == 1){
              stateLED1 = 0;
              stateLED2 = 1;
              analogWrite(LED_Level1, stateButton1);

              tone(buzzer, freqBuzzer_Move, timeBuzzer_Move);

              SwitchLevels();
              SwitchLevels();
              SwitchLevels();
              SwitchLevels();

              tone(buzzer, freqBuzzer_Stay, timeBuzzer_Stay);
              analogWrite(LED_Move, HIGH);
              analogWrite(LED_Level2, stateLED2);

              step = 0;
              stateButton2=0;
              break;
            }
            if(stateButton3 == 1){
              stateLED1 = 0;
              stateLED2 = 0;
              stateLED3 = 1;
              analogWrite(LED_Level1, stateButton1);

              tone(buzzer, freqBuzzer_Move, 2*timeBuzzer_Move);

              SwitchLevels();
              SwitchLevels();
              SwitchLevels();
              SwitchLevels();

              SwitchLevels_inter(LED_Level2);

              SwitchLevels();
              SwitchLevels();
              SwitchLevels();

              tone(buzzer, freqBuzzer_Stay, timeBuzzer_Stay);
              analogWrite(LED_Move, HIGH);
              analogWrite(LED_Level3, stateLED3);

              step = 0;
              stateButton3=0;
              break;
            }
          }
////////////daca liftul este la etajul 2 si sta
          if(stateLED2 == 1)
          {
            if(stateButton2 == 1){
              tone(buzzer, freqBuzzer_Stay, timeBuzzer_Stay);
              break;
            }
            if(stateButton1 == 1){
              stateLED2 = 0;
              stateLED1 = 1;
              analogWrite(LED_Level2, stateButton2);

              tone(buzzer, freqBuzzer_Move, timeBuzzer_Move);

              SwitchLevels();
              SwitchLevels();
              SwitchLevels();
              SwitchLevels();

              tone(buzzer, freqBuzzer_Stay, timeBuzzer_Stay);
              analogWrite(LED_Move, HIGH);
              analogWrite(LED_Level1, stateLED1);

              step = 0;
              stateButton1=0;
              break;
            }
            if(stateButton3 == 1){
              stateLED1 = 0;
              stateLED2 = 0;
              stateLED3 = 1;
              analogWrite(LED_Level2, stateButton2);

              tone(buzzer, freqBuzzer_Move, timeBuzzer_Move);

              SwitchLevels();
              SwitchLevels();
              SwitchLevels();
              SwitchLevels();

              tone(buzzer, freqBuzzer_Stay, timeBuzzer_Stay);
              analogWrite(LED_Move, HIGH);
              analogWrite(LED_Level3, stateLED3);
              
              step = 0;
              stateButton3=0;
              break;
            }
          }
////////////daca liftul este la etajul 3 si sta
          if(stateLED3 == 1)
          {
            if(stateButton3 == 1){
              tone(buzzer, freqBuzzer_Stay, timeBuzzer_Stay);
              break;
            }
            if(stateButton2 == 1){
              stateLED3 = 0;
              stateLED2 = 1;
              analogWrite(LED_Level3, stateButton3);

              tone(buzzer, freqBuzzer_Move, timeBuzzer_Move);

              SwitchLevels();
              SwitchLevels();
              SwitchLevels();
              SwitchLevels();

              tone(buzzer, freqBuzzer_Stay, timeBuzzer_Stay);
              analogWrite(LED_Move, HIGH);
              analogWrite(LED_Level2, stateLED2);

              step = 0;
              stateButton2=0;
              break;
            }
            if(stateButton1 == 1){
              stateLED1 = 1;
              stateLED2 = 0;
              stateLED3 = 0;
              analogWrite(LED_Level3, stateButton3);

              tone(buzzer, freqBuzzer_Move, 2*timeBuzzer_Move);

              SwitchLevels();
              SwitchLevels();
              SwitchLevels();
              SwitchLevels();

              SwitchLevels_inter(LED_Level2);

              SwitchLevels();
              SwitchLevels();
              SwitchLevels();

              tone(buzzer, freqBuzzer_Stay, timeBuzzer_Stay);
              analogWrite(LED_Move, HIGH);
              analogWrite(LED_Level1, stateLED1);

              step = 0;
              stateButton1=0;
              break;
            }
          }
          break;
    
  }

}