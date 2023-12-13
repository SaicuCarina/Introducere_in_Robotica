#include <LiquidCrystal.h>
#include <EEPROM.h>
#include <LedControl.h>

const byte rs = 9;
const byte en = 8;
const byte d4 = 7;
const byte d5 = 6;
const byte d6 = 5;
const byte d7 = 4;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int LCDbrightnessPin = 3;
const int pinSW = 2;
const int joystickXPin = A0;
const int joystickYPin = A1;

byte yJoyMoved = false;
byte xJoyMoved = false;
const int minThreshold = 200;
const int maxThreshold = 600;

unsigned long debounceDelay = 50;
unsigned long lastDebounceTime = 0;
int buttonState;
int lastButtonState = LOW;
bool buttonValue = true;

int menuOption = 1;
bool inMenu = false;
int settingsMenuState = 1;
int aboutMenuState = 1;

int LCDbrightness = 20;
byte matrixBrightness = 7; 

byte downArrow[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b11111,
  0b01110,
  0b00100,
  0b00000,
  0b00000
};

byte upArrow[8] = {
  0b00000,
  0b00000,
  0b00100,
  0b01110,
  0b11111,
  0b00000,
  0b00000,
  0b00000
};

byte selectArrow[8] = {
  0b00000,
  0b00100,
  0b00110,
  0b11111,
  0b11111,
  0b00110,
  0b00100,
  0b00000
};

byte rightArrow[8] = {
  0b00000,
  0b01000,
  0b01100,
  0b01110,
  0b01110,
  0b01100,
  0b01000,
  0b00000
};

byte leftArrow[8] = {
  0b00000,
  0b00010,
  0b00110,
  0b01110,
  0b01110,
  0b00110,
  0b00010,
  0b00000
};

void setup() {
  lcd.begin(16, 2);  // Inițializează LCD-ul cu 16 coloane și 2 linii
  pinMode(pinSW, INPUT_PULLUP);
  pinMode(LCDbrightnessPin, OUTPUT);
}

void loop() {
  if (millis() < 3000) {
    lcd.setCursor(0, 0);
    lcd.print("Welcome!");
  } else {
    buttonPress();

    inMenu = buttonValue;

  
    if (inMenu == false) {
      updateMenu();
      navigate();
      settingsMenuState = 1;
    } else {
      enterMenu();
    }
  }
}

void updateMenu() {

  lcd.createChar(1, downArrow);
  lcd.createChar(2, selectArrow);
  lcd.createChar(3, upArrow);

  switch (menuOption) {
    case 0:
      menuOption = 1;
      break;

    case 1:
      
      lcd.clear();
      lcd.print(" Start game");
      lcd.setCursor(0, 1);
      lcd.print(" Settings");
      lcd.setCursor(15, 1);
      lcd.write(1);
      lcd.setCursor(0, 0);
      lcd.write(2);
      break;

    case 2:
      lcd.clear();
      lcd.print(" Settings");
      lcd.setCursor(15, 0);
      lcd.write(3);
      lcd.setCursor(0, 1);
      lcd.print(" About");
      lcd.setCursor(15, 1);
      lcd.setCursor(0, 0);
      lcd.write(2);
      break;

    case 3:
      lcd.clear();
      lcd.print(" Settings");
      lcd.setCursor(15, 0);
      lcd.write(3);
      lcd.setCursor(0, 1);
      lcd.print(" About");
      lcd.setCursor(0, 1);
      lcd.write(2);
      break;
    
    case 4:
      menuOption = 3;
      break;
  }
}

void enterMenu() {

  switch (menuOption) {
    case 1:
      lcd.clear();
      // startGame();
      break;

    case 2:
      lcd.clear();
      navigateSettings();
      settings();
      break;

    case 3:
      lcd.clear();
      navigateAbout();
      about();
      break;
  }
}

void navigateAbout() {
  int yValue = analogRead(joystickYPin);

    if (yJoyMoved == false) {
      if (yValue > maxThreshold) {
        aboutMenuState++;
        yJoyMoved = true;
      }
      if (yValue < minThreshold) {
        aboutMenuState--;
        yJoyMoved = true;
      }
    }

    if (yValue > minThreshold && yValue < maxThreshold) {
      yJoyMoved = false;
    }
}

void navigateSettings() {

  int yValue = analogRead(joystickYPin);

    if (yJoyMoved == false) {
      if (yValue > maxThreshold) {
        settingsMenuState++;
        yJoyMoved = true;
      }
      if (yValue < minThreshold) {
        settingsMenuState--;
        yJoyMoved = true;
      }
    }

    if (yValue > minThreshold && yValue < maxThreshold) {
      yJoyMoved = false;
    }
}

void about() {

  switch (aboutMenuState) {
    case 0:
      aboutMenuState = 1;
      break;
    case 1:
      lcd.createChar(1, downArrow);
      lcd.clear();
      lcd.print("Name: Bomberman");
      lcd.setCursor(0, 1);
      lcd.print("Made by Carina");
      lcd.setCursor(15, 1);
      lcd.write(1);
      break;
    case 2:
      lcd.createChar(3, upArrow);
      lcd.clear();
      lcd.print("Made by Carina");
      lcd.setCursor(0, 1);
      lcd.print("GH: SaicuCarina");
      lcd.setCursor(15, 0);
      lcd.write(3);
      break;
    case 3:
      aboutMenuState = 2;
      break;
  }

  delay(10);
}

void settings() {

  switch (settingsMenuState) {
    case 0:
      settingsMenuState = 1;
      break;

    case 1:  // LCD BRIGHTNESS CONTROL
      lcd.createChar(1, downArrow);
      lcd.createChar(2, selectArrow);
      lcd.createChar(7, rightArrow);
      lcd.createChar(8, leftArrow);

      lcd.clear();
      lcd.write(" LCD Bright:");
      lcd.setCursor(0, 0);
      lcd.write(2);
      lcd.setCursor(14, 0);
      lcd.write(8);
      lcd.setCursor(15, 0);
      lcd.write(7);
      lcd.setCursor(15, 1);
      lcd.write(1);
      lcd.setCursor(0, 1);
      lcd.write(" Matr Bright:");
      lcd.setCursor(12, 0);
      lcd.print(LCDbrightness - 10);
      lcd.setCursor(13, 1);
      lcd.print(matrixBrightness);

      navigateLCDbrightness();
      
      delay(10);

      break;

    case 2:  // MATRIX BRIGHTNESS CONTROL
      lcd.createChar(1, downArrow);
      lcd.createChar(2, selectArrow);
      lcd.createChar(7, rightArrow);
      lcd.createChar(8, leftArrow);

      lcd.clear();
      lcd.write(" LCD Bright:");
      lcd.setCursor(14, 0);
      lcd.write(8);
      lcd.setCursor(15, 0);
      lcd.write(7);
      lcd.setCursor(15, 1);
      lcd.write(1);
      lcd.setCursor(0, 1);
      lcd.write(2);
      lcd.write("Matr Bright:");
      lcd.setCursor(12, 0);
      lcd.print(LCDbrightness - 10);
      lcd.setCursor(13, 1);
      lcd.print(matrixBrightness);

      navigateMatrixBrightness();

      delay(10);

      break;

    case 3:
      settingsMenuState = 2;
      break;
  }

  delay(20);
}

void navigateMatrixBrightness(){
  int xValue = analogRead(joystickXPin);

  if (xJoyMoved == false) {
    if (xValue > maxThreshold) {
      if (matrixBrightness < 15) {
         matrixBrightness++;
      }
      xJoyMoved = true;
    }
    if (xValue < minThreshold) {
      if (matrixBrightness > 0) {
        matrixBrightness--;
      }
      xJoyMoved = true;
    }
  }

  if (xValue < maxThreshold && xValue > minThreshold) {
     xJoyMoved = false;
  }
}

void navigateLCDbrightness(){
  int xValue = analogRead(joystickXPin);

  if (xJoyMoved == false) {
    if (xValue > maxThreshold) {
      if (LCDbrightness < 25) {
        LCDbrightness++;
        // EEPROM.update(11, LCDbrightness);
      }
      xJoyMoved = true;
    }
    if (xValue < minThreshold) {
      if (LCDbrightness > 10) {
        LCDbrightness--;
        // EEPROM.update(11, LCDbrightness);
      }
      xJoyMoved = true;
    }
  }

  if (xValue < maxThreshold && xValue > minThreshold) {
    xJoyMoved = false;
  }
}

void buttonPress() {
  int reading = digitalRead(pinSW);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == HIGH) {
        buttonValue = !buttonValue;
      }
    }
  }

  lastButtonState = reading;
}

void navigate() {
  int yValue = analogRead(joystickYPin);

  if (yJoyMoved == false) {
    if (yValue > maxThreshold) {
      menuOption++;
      updateMenu();
      yJoyMoved = true;
    }
    if (yValue < minThreshold) {
      menuOption--;
      updateMenu();
      yJoyMoved = true;
    }
  }

  if (yValue > minThreshold && yValue < maxThreshold) {
    yJoyMoved = false;
  }
}