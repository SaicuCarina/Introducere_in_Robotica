#include <LedControl.h>

// Initialize the LED matrix
LedControl lc = LedControl(12, 11, 10, 1); // (DataIn, CLK, LOAD, Number of MAX7219 ICs)

// Define variables for joystick pins
const int pinSW = 2;
const int joystickXPin = A0;
const int joystickYPin = A1;

const int pinBuzzer = 3;

// Matrix size
const int matrixSize = 8;
byte matrixBrightness = 5;

int freqBuzzer = 700;
int timeBuzzer = 500;

// 2D array to represent the matrix
byte mapPlay[matrixSize][matrixSize];

// Player position
int playerX = 0;
int playerY = 0;

// Player blinking variables
bool isPlayerVisible = true;
bool isPlayerBlinking = true;  // Added variable to control player blinking
unsigned long lastPlayerBlinkTime = 0;
const unsigned long playerBlinkInterval = 500; // Player blinks every 500 milliseconds

// Player movement variables
bool isPlayerMoving = false;
unsigned long lastMoveTime = 0;
const unsigned long moveInterval = 200; // Move every 200 milliseconds

// Bomb variables
bool isBombPlaced = false;
unsigned long bombStartTime = 0;
unsigned long lastBombBlinkTime = 0;
const unsigned long bombBlinkInterval = 50; // Bomb blinks every 100 milliseconds
const unsigned long bombDetonationTime = 3000; // Bomb detonates after 5 seconds

unsigned long previousMillis = 0;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 150;

int lastSwState = HIGH; // Assume switch is initially not pressed
int swState = HIGH;

bool bombLedState = false;

void generateMap(){
  // Calculate the number of LEDs to set randomly (50% to 75% of the remaining matrix)
  int numLedsToSet = random((matrixSize * matrixSize) / 2, ((matrixSize * matrixSize) / 2) + ((matrixSize * matrixSize) / 4));

  // Set random LEDs within the specified range, excluding the top-left square
  for (int i = 0; i < numLedsToSet; ++i) {
    int row, col;

    // Generate random coordinates
    row = random(1, matrixSize); // Avoid the first row
    col = random(matrixSize);

    // Set the LED
    lc.setLed(0, row, col, true);
    mapPlay[row][col] = 1;
  }
}

void player() {
  // Blinking effect
  unsigned long currentTime = millis();

  // Check if the player is not moving and enough time has passed since the last blink
  if (!isBombPlaced && isPlayerBlinking && !isPlayerMoving && currentTime - lastPlayerBlinkTime >= playerBlinkInterval) {
    isPlayerVisible = !isPlayerVisible;
    lastPlayerBlinkTime = currentTime;
  }

  // Display the player on the LED matrix
  if (isPlayerVisible && !isBombPlaced) {
    lc.setLed(0, playerY, playerX, true);
  } else {
    lc.setLed(0, playerY, playerX, false);
  }

   if (isPlayerMoving){
    lc.setLed(0, playerY, playerX, true);
  }

  if (isBombPlaced){
    lc.setLed(0, playerY, playerX, false);
  }
}

void movePlayer(int deltaX, int deltaY) {
  // Check if the player is moving
  isPlayerMoving = (deltaX != 0 || deltaY != 0);

  // Check if enough time has passed since the last movement
  unsigned long currentTime = millis();
  if (currentTime - lastMoveTime >= moveInterval) {
    // Check if the next position is within the boundaries and not a wall
    int nextX = playerX + deltaX;
    int nextY = playerY + deltaY;

    if (nextX >= 0 && nextX < matrixSize && nextY >= 0 && nextY < matrixSize && mapPlay[nextY][nextX] != 1) {
      // Clear the current player position
      lc.setLed(0, playerY, playerX, false);

      // Update the player position
      playerX = nextX;
      playerY = nextY;
    }

    // Update the last movement time
    lastMoveTime = currentTime;
  }
}

void bomb() {
  int reading = digitalRead(pinSW);

  if (reading != lastSwState) {
    lastDebounceTime = millis(); //lastTime
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != swState) {
      swState = reading;
      if (swState == LOW) { // Button is pressed
        if (!isBombPlaced) {
          // Place the bomb at the player's position
          isBombPlaced = true;
          bombStartTime = millis();
          
          // Stop player blinking when the bomb is placed
          isPlayerBlinking = false;
          // lc.setLed(0, playerY, playerX, false);
        }
      }
    }
  }

  lastSwState = reading;

  // Check if the bomb is placed and enough time has passed for blinking
  if (isBombPlaced) {
    unsigned long currentTimeBomb = millis();
    if (currentTimeBomb - lastBombBlinkTime >= bombBlinkInterval) {
      bombLedState = !bombLedState; // Toggle bomb LED state
      lc.setLed(0, playerY, playerX, bombLedState); // Set bomb LED based on the toggle state
      lastBombBlinkTime = currentTimeBomb;
    }

    // Check if enough time has passed for detonation
    if (currentTimeBomb - bombStartTime >= bombDetonationTime) {
      // Detonate the bomb: Destroy walls in the vicinity
      destroyWalls(playerX - 1, playerY);
      destroyWalls(playerX, playerY - 1);
      destroyWalls(playerX + 1, playerY);
      destroyWalls(playerX, playerY + 1);

      // Clear the bomb
      lc.setLed(0, playerY, playerX, false);
      isBombPlaced = false;

      // Resume player blinking after the bomb explodes
      isPlayerBlinking = true;
      tone(pinBuzzer, freqBuzzer, timeBuzzer);
    }
  }
}

void destroyWalls(int x, int y) {
  if (x >= 0 && x < matrixSize && y >= 0 && y < matrixSize && mapPlay[y][x] == 1) {
    // Clear the wall
    lc.setLed(0, y, x, false);
    mapPlay[y][x] = 0;
  }
}

void howToMove() {
  // Read joystick values
  int joystickX = analogRead(joystickXPin);
  int joystickY = analogRead(joystickYPin);

  // Map joystick values to player movement
  int deltaX = 0;
  int deltaY = 0;

  if (joystickX < 200) {
    deltaX = -1; // Left
  } else if (joystickX > 900) {
    deltaX = 1; // Right
  }

  if (joystickY < 200) {
    deltaY = -1; // Up
  } else if (joystickY > 900) {
    deltaY = 1; // Down
  }

  // Move the player
  movePlayer(deltaX, deltaY);
}

void setup() {
  // Seed the random number generator with an analogRead value
  randomSeed(analogRead(A3));

  // the zero refers to the MAX7219 number, it is zero for 1 chip
  lc.shutdown(0, false); // turn off power saving, enables display
  lc.setIntensity(0, matrixBrightness); // sets brightness (0~15 possible values)
  lc.clearDisplay(0); // clear screen

  // Set joystick and switch pins as inputs
  pinMode(pinSW, INPUT_PULLUP);
  pinMode(joystickXPin, INPUT);
  pinMode(joystickYPin, INPUT);

  generateMap();
  player(); // Initial display of the player
}

void loop() {
  howToMove();

  // Handle bomb placement and detonation
  bomb();

  // Display the player
  player();
}