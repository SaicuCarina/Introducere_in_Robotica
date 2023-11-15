// Define connections to the shift register
const int latchPin = 11; // Connects to STCP (latch pin) on the shift register
const int clockPin = 10; // Connects to SHCP (clock pin) on the shift register
const int dataPin = 12; // Connects to DS (data pin) on the shift register

const int startButtonPin = 13; 
const int resetButtonPin = 8;
const int saveButtonPin = 2;

// Define connections to the digit control pins for a 4-digit display
const int segD1 = 4;
const int segD2 = 5;
const int segD3 = 6;
const int segD4 = 7;

// Store the digits in an array for easy access
int displayDigits[] = {segD1, segD2, segD3, segD4};
const int displayCount = 4; // Number of digits in the display

// Define the number of unique encodings (0-9, A-F for hexadecimal)
const int encodingsNumber = 16;
// Define byte encodings for the hexadecimal characters 0-F
byte byteEncodings[encodingsNumber] = {
//A B C D E F G DP 
  B11111100, // 0 
  B01100000, // 1
  B11011010, // 2
  B11110010, // 3
  B01100110, // 4
  B10110110, // 5
  B10111110, // 6
  B11100000, // 7
  B11111110, // 8
  B11110110, // 9
  B11101110, // A
  B00111110, // b
  B10011100, // C
  B01111010, // d
  B10011110, // E
  B10001110  // F
};
// Variables for controlling the display update timing
unsigned long lastIncrement = 0;
unsigned long delayCount = 100; // Delay between updates (milliseconds)
unsigned long number = 0; // The number being displayed

//ButtonDebounce
int buttonNumber = 3;

// const int button[buttonNumber] = {12, 8, 2}; //start, reset, save

byte stateButtonStart = 1;
byte lastReadingStart = 0;
unsigned int lastDebounceTimeStart = 0;

byte stateButtonReset = 1;
byte lastReadingReset = 0;
unsigned int lastDebounceTimeReset = 0;

byte stateButtonSave = 1;
byte lastReadingSave = 0;
unsigned int lastDebounceTimeSave = 0;

int numberOfLaps = 4;
unsigned long saveLap[4] = {0, 0, 0, 0};
int laps = -1;

unsigned int debounceDelay = 50;
bool isRunning = 0;
bool staart = 0;
bool stopWatchStopped = true;
bool shouldIncrement = false;

int increment = 0;

bool pressedLap = 0;

void setup() {
  // Initialize the pins connected to the shift register as outputs
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  pinMode(startButtonPin, INPUT_PULLUP);
  pinMode(resetButtonPin, INPUT_PULLUP);
  pinMode(saveButtonPin, INPUT_PULLUP);

  // Initialize digit control pins and set them to LOW (off)
  for (int i = 0; i < displayCount; i++) {
    pinMode(displayDigits[i], OUTPUT);
    digitalWrite(displayDigits[i], LOW);
  }  
  // attachInterrupt(digitalPinToInterrupt(startButtonPin), start, CHANGE);
  // attachInterrupt(digitalPinToInterrupt(saveButtonPin), functie, CHANGE);
  // Begin serial communication for debugging purposes
  Serial.begin(9600);
}

void loop() {
  pressedLap = 0;

  if(staart == 0){
    reset();
  }
  

  if(isRunning == 0){
    numberOf0();
    writeNumber(number);
  }
  
  int readingButtonStart = digitalRead(startButtonPin);

  if(readingButtonStart != lastReadingStart){
    lastDebounceTimeStart = millis();
  }
  if ((millis() - lastDebounceTimeStart) > debounceDelay) {
    if (readingButtonStart != stateButtonStart) {
      stateButtonStart = readingButtonStart;

      if (stateButtonStart == LOW) {
        if (isRunning) {
          isRunning = false;
          stopWatchStopped = true;
        } else {
          isRunning = true;
          stopWatchStopped = false;
          staart = 1;
        }
      }
    }
  }
  lastReadingStart = readingButtonStart;

  stopWatch();

  int readingButtonReset = digitalRead(resetButtonPin);

  if (readingButtonReset != lastReadingReset) {
    lastDebounceTimeReset = millis();
  }
  if ((millis() - lastDebounceTimeReset) > debounceDelay) {
    if (readingButtonReset != stateButtonReset) {
      stateButtonReset = readingButtonReset;

      if (stateButtonReset == LOW) {
          if(isRunning == 0){
          staart = 0;
          number = 0;
        }
      }
    }
  }
  lastReadingReset = readingButtonReset;

  int readingButtonSave = digitalRead(saveButtonPin);

  if (readingButtonSave != lastReadingSave) {
    lastDebounceTimeSave = millis();
  }
  if ((millis() - lastDebounceTimeSave) > debounceDelay) {
    if (readingButtonSave != stateButtonSave) {
      stateButtonSave = readingButtonSave;

      if (stateButtonSave == LOW) {
        if(isRunning == 1){
          laps = laps + 1;
          if(laps < numberOfLaps){
            saveLap[laps] = number;
          }
          else{
            laps = 0;
            saveLap[laps] = number;
          }
        }
        if(staart == 0){
          saveLapFunction();
          pressedLap = 1;
        }
      }
    }
  }
  lastReadingSave = readingButtonSave;
} 

void saveLapFunction(){
  // allLow();
  if(increment < numberOfLaps){
    writeReg(B00000000);
    number = saveLap[increment];
    // writeNumber(number);
    increment = increment + 1;
  }
  else{
    increment = 0;
    writeReg(B00000000);
    number = saveLap[increment];
    // writeNumber(number);
    increment = increment + 1;
  }
}

void stopWatch(){

  if (isRunning) {
  
    numberOf0();
    // Increment the number only when the stopwatch is running
    if (millis() - lastIncrement > delayCount) {
      number++;
      number %= 10000; // Wrap around after 9999
      lastIncrement = millis();
    }
    // Display the incremented number on the 7-segment display using multiplexing
    writeNumber(number);
  }
}

void numberOf0(){
    activateDisplay(2);
    writeReg(B00000001); // Display "0" with the third dot active

    if(number == 0){
      display0(displayCount);
    }

    writeReg(B00000000);
    if(number < 10){
      display0(displayCount-1);
    }
    if(number < 100){
      display0(displayCount-2);
    }
    if(number >= 100 and number < 1000){
      display0(displayCount-3);
    }
    if(number >= 1000){
      activateDisplay(0);
      writeReg(B00000000); // Turn off all segments
    }
}

void display0(int displayNumber){
  writeReg(B00000000);
  for(int i = 0; i < displayNumber; i++){
    activateDisplay(i);
    writeReg(byteEncodings[0]); // Display "0"

    writeReg(B00000000);
  }
}

void allLow(){
  for (int i = 0; i < displayCount; i++) {
    activateDisplay(i);
    writeReg(B00000000); // Turn off all segments
  }
}

void reset(){

  isRunning = false;  // Stop the stopwatch

  // Clear the display by turning off all segments for each digit
  allLow();

  // If "Save" button is pressed during reset, display the saved number
  if (pressedLap == 1) {
    saveLapFunction();
  } else {
    // If "Start" button is pressed during reset, start from 0
    if (digitalRead(startButtonPin) == LOW) {
      number = 0;
    } else {
      // Display "000.0"
      numberOf0();
    }
  }
}

void start(){
   isRunning = true;
}

void writeReg(int digit) {
    // Prepare to shift data by setting the latch pin low
    digitalWrite(latchPin, LOW);
    // Shift out the byte representing the current digit to the shift register
    shiftOut(dataPin, clockPin, MSBFIRST, digit);
    // Latch the data onto the output pins by setting the latch pin high
    digitalWrite(latchPin, HIGH);
}
void activateDisplay(int displayNumber) {
  // Turn off all digit control pins to avoid ghosting
  for (int i = 0; i < displayCount; i++) {
    digitalWrite(displayDigits[i], HIGH);
  }
  // Turn on the current digit control pin
  digitalWrite(displayDigits[displayNumber], LOW);
}

void writeNumber(int number) {
  // DONE: Initialize necessary variables for tracking the current number and digit position
  int currentNumber = number;
  int displayDigit = 3; // Start with the least significant digit
  int lastDigit = 0;

  // DONE: Loop through each digit of the current number
  while (currentNumber != 0) {
    // DONE: Extract the last digit of the current number
    lastDigit = currentNumber % 10;
    // DONE: Activate the current digit on the display
    activateDisplay(displayDigit);
    // DONE: Output the byte encoding for the last digit to the display
    writeReg(byteEncodings[lastDigit]);
    // DONE: Implement a delay if needed for multiplexing visibility
    delay(0); // A delay can be increased to visualize multiplexing
    // DONE: Move to the next digit
    displayDigit--;
    // DONE: Update 'currentNumber' by removing the last digit
    currentNumber /= 10;
    
    // DONE: Clear the display to prevent ghosting between digit activations
    writeReg(B00000000); // Clear the register to avoid ghosting
  }
}