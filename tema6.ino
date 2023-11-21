#include <Arduino.h>

const int RGBLED_BluePin = 9;
const int RGBLED_GreenPin = 10;
const int RGBLED_RedPin = 11;

const int buzzerPin = 3;

const int trigPin = 6;
const int echoPin = 5;

const int irSensorPin = A0;
int photocellValue;

// Variable to keep track of the current submenu
int currentSubMenu = 0;
bool automaticMode = false;
int sensorSamplingInterval = 1;

int lastRed = 0;
int lastGreen = 0;
int lastBlue = 0;

long duration = 0;
int distance = 0;

int freqBuzzer = 1000;
int timeBuzzer = 1000;

int thresholdValueUltrasonic;
int thresholdValueLDR;



void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  pinMode(RGBLED_GreenPin, OUTPUT);
  pinMode(RGBLED_RedPin, OUTPUT);
  pinMode(RGBLED_BluePin, OUTPUT);

  Serial.begin(9600);
  printMenu();
}

void loop() {
  // Continuously checks for incoming serial data
  if (Serial.available()) {
    // Reads an integer value from the serial buffer (user's menu choice)
    int choice = Serial.parseInt();
    // Calls function to print a message based on the user's choice
    printMessage(choice);
    printMenu();
  }
}

// Function to display a menu of options to the user
void printMenu() {
  Serial.println("Menu Interface:");

  // Check the current submenu and display the corresponding options
  switch (currentSubMenu) {
    case 0:
      Serial.println("Select an option:");
      Serial.println("1. Sensor Settings");
      Serial.println("2. Reset Logger Data");
      Serial.println("3. System Status");
      Serial.println("4. RGB LED Control");
      break;
    case 1:
      Serial.println("Sensor Settings Submenu:");
      Serial.println("1.1 Sensors Sampling Interval");
      Serial.println("1.2 Ultrasonic Alert Threshold");
      Serial.println("1.3 LDR Alert Threshold");
      Serial.println("1.4 Back to Main Menu");
      break;
    case 2:
      Serial.println("Reset Logger Data Submenu:");
      Serial.println("2.1 Yes");
      Serial.println("2.2 No");
      break;
    case 3:
      Serial.println("System Status Submenu:");
      Serial.println("3.1 Current Sensor Readings");
      Serial.println("3.2 Current Sensor Settings");
      Serial.println("3.3 Display Logged Data");
      Serial.println("3.4 Back to Main Menu");
      break;
    case 4:
      Serial.println("RGB LED Control Submenu:");
      Serial.println("4.1 Manual Color Control");
      Serial.println("4.2 LED: Toggle Automatic ON/OFF");
      Serial.println("4.3 Back to Main Menu");
      break;
  }
}

// Function to print different messages based on the user's selection
void printMessage(int option) {
  Serial.print("\nPrinted message: ");
  switch (currentSubMenu) {
    case 0:
      // Main menu options
      switch (option) {
        case 1:
          // Switch to Sensor Settings submenu
          currentSubMenu = 1;
          Serial.println("Entering Sensor Settings Submenu\n");
          break;
        case 2:
          currentSubMenu = 2;
          Serial.println("Are you sure?\n");
          break;
        case 3:
          currentSubMenu = 3;
          Serial.println("Option 3\n");
          break;
        case 4:
          currentSubMenu = 4;
          Serial.println("Option 4\n");
          break;
        default:
          Serial.println("The selected option is outside the scope of the menu\n");
          break;
      }
      break;
    case 1:
      switch (option) {
        case 1:
          // Sensor Settings submenu options
          Serial.println("Sensors Sampling Interval\n");
          // Prompt the user for a sampling interval
          Serial.println("Enter the sampling interval in seconds (1-10):");
          while (!Serial.available()) {
            // Wait for user input
          }

          // Read user input
          int interval = Serial.parseInt();

          // Update the sensor sampling interval
          sensorSamplingInterval = interval;

          Serial.print("Sensor Sampling Interval set to ");
          Serial.print(sensorSamplingInterval);
          Serial.println(" seconds\n");

          delay(sensorSamplingInterval);
          // Sets the trigPin on HIGH state for 10 micro seconds
          digitalWrite(trigPin, HIGH);
          delayMicroseconds(10);
          digitalWrite(trigPin, LOW);
          photocellValue = analogRead(irSensorPin);
          duration = pulseIn(echoPin, HIGH);
          // Sound wave reflects from the obstacle, so to calculate the distance we   
          // consider half of the distance traveled.
          distance = duration*0.034/2;
          // Prints the distance on the Serial Monitor
          Serial.print("Distance: ");
          Serial.println(distance);
          Serial.print("Light: ");
          Serial.println(photocellValue);
          break;

        case 2:
          Serial.println("Ultrasonic Alert Threshold\n");
          Serial.println("Enter a min values for Ultrasonic Sensor:");
          while (!Serial.available()) {
            // Wait for user input
          }
          thresholdValueUltrasonic = Serial.parseInt();
          duration = pulseIn(echoPin, HIGH);
          // Sound wave reflects from the obstacle, so to calculate the distance we   
          // consider half of the distance traveled.
          distance = duration*0.034/2;
          if (distance <= thresholdValueUltrasonic){
            if(automaticMode == 1){
              analogWrite(RGBLED_RedPin, 255);
            }
            tone(buzzerPin, freqBuzzer, timeBuzzer);
          }
          break;

        case 3:
          Serial.println("LDR Alert Threshold\n");
          Serial.println("Enter a min values for LDR Sensor:");
          while (!Serial.available()) {
          // Wait for user input
          }
          thresholdValueLDR = Serial.parseInt();

          digitalWrite(trigPin, HIGH);
          delayMicroseconds(10);
          digitalWrite(trigPin, LOW);

          photocellValue = analogRead(irSensorPin);
          // Sound wave reflects from the obstacle, so to calculate the distance we   

          if (photocellValue <= thresholdValueLDR){
            if(automaticMode == 1){
              analogWrite(RGBLED_RedPin, 255);
            }
            tone(buzzerPin, freqBuzzer, timeBuzzer);
          }
          break;
        case 4:
          // Return to the main menu
          currentSubMenu = 0;
          Serial.println("Returning to Main Menu\n");
          break;
        default:
          Serial.println("The selected option is outside the scope of the menu\n");
          break;
      }
      break;
    case 2:
      // Sensor Settings submenu options
      switch (option) {
        case 1:
          Serial.println("Yes\n");
          break;
        case 2:
          Serial.println("No\n");
          break;
        default:
          Serial.println("The selected option is outside the scope of the menu\n");
          break;
      }
      break;
    case 3:
      // Sensor Settings submenu options
      switch (option) {
        case 1:
          Serial.println("Current Sensor Readings\n");
          break;
        case 2:
          Serial.println("Current Sensor Settings\n");
          break;
        case 3:
          Serial.println("Display Logged Data\n");
          break;
        case 4:
          // Return to the main menu
          currentSubMenu = 0;
          Serial.println("Returning to Main Menu\n");
          break;
        default:
          Serial.println("The selected option is outside the scope of the menu\n");
          break;
      }
      break;
    case 4:
      // RGB LED Control submenu options
      switch (option) {
        case 1:
          Serial.println("Manual Color Control\n");
          // Prompt the user for RGB values
          Serial.println("Enter RGB values (0-255) separated by spaces (red green blue):");
          while (!Serial.available()) {
            // Wait for user input
          }
          // Read user input
          int red = Serial.parseInt();
          int green = Serial.parseInt();
          int blue = Serial.parseInt();

          // Ensure valid input range (0-255)
          red = constrain(red, 0, 255);
          green = constrain(green, 0, 255);
          blue = constrain(blue, 0, 255);

          // Set the RGB LED colors
          analogWrite(RGBLED_RedPin, red);
          analogWrite(RGBLED_GreenPin, green);
          analogWrite(RGBLED_BluePin, blue);

          Serial.println("RGB LED colors set successfully!\n");
          currentSubMenu = 4;
          break;
        case 2:
          Serial.println("LED: Toggle Automatic ON/OFF\n");
          Serial.println("Enter values for sensors (ex: 6 100 - Ultrasonic Sensor LDR):");
          while (!Serial.available()) {
            // Wait for user input
          }
          // Read user input
          thresholdValueUltrasonic = Serial.parseInt();
          thresholdValueLDR = Serial.parseInt();
          // Toggle automatic mode
          automaticMode = !automaticMode;

          if (automaticMode) {
            Serial.println("Automatic mode is ON\n");

            int photocellValue = analogRead(irSensorPin);
            digitalWrite(trigPin, LOW);
            delayMicroseconds(2);
            // Sets the trigPin on HIGH state for 10 micro seconds
            digitalWrite(trigPin, HIGH);
            delayMicroseconds(10);
            digitalWrite(trigPin, LOW);
    
            duration = pulseIn(echoPin, HIGH);
            // Sound wave reflects from the obstacle, so to calculate the distance we   
            // consider half of the distance traveled.
            distance = duration*0.034/2;

            if (distance <= thresholdValueUltrasonic and photocellValue <= thresholdValueLDR) {
              // No alert, set LED to GREEN
              analogWrite(RGBLED_GreenPin, 255); // Green color
            } else {
              // Alert, set LED to RED
              analogWrite(RGBLED_RedPin, 255); // Red color
              }
            } else {
              Serial.println("Automatic mode is OFF\n");
              // Use the last saved RGB values
              analogWrite(RGBLED_RedPin, lastRed);
              analogWrite(RGBLED_GreenPin, lastGreen);
              analogWrite(RGBLED_BluePin, lastBlue);
            } 
          break;
        case 3:
          // Return to the main menu
          currentSubMenu = 0;
          Serial.println("Returning to Main Menu\n");
          break;
        default:
          Serial.println("The selected option is outside the scope of the menu\n");
          break;
      }
      break;
  }
}