#include "FS.h"
#include "SPIFFS.h"

#define DEFAULT_CUTTING_TIME 60
#define ANTI_CUTTING_TIME 1500
#define SENSOR_QUICKSHIFTER 34
#define OUTPUT_COIL_1 23
#define OUTPUT_LED_ONBOARD 2

int KILLING_TIME = DEFAULT_CUTTING_TIME;
bool isTestMode = false; // Variable for TEST mode

void setup() {

  // Set pin modes for quickshifter sensor, coil output, and onboard LED
  pinMode(SENSOR_QUICKSHIFTER, INPUT);
  pinMode(OUTPUT_COIL_1, OUTPUT); 
  pinMode(OUTPUT_LED_ONBOARD, OUTPUT); 

  // Initialize outputs to low (OFF)
  digitalWrite(OUTPUT_COIL_1, LOW);
  digitalWrite(OUTPUT_LED_ONBOARD, LOW); 

  Serial.begin(115200); // Start serial communication
  if (!SPIFFS.begin(true)) { // Initialize SPIFFS file system
    Serial.println("Failed to mount SPIFFS");
    return;
  }
  
  // Load cutting time from SPIFFS if the file exists
  if (SPIFFS.exists("/cuttingTime.txt")) {
    File file = SPIFFS.open("/cuttingTime.txt", "r");
    if (file) {
      String value = file.readStringUntil('\n');
      KILLING_TIME = value.toInt(); 
      Serial.print("Cutting time loaded from SPIFFS: ");
      Serial.println(KILLING_TIME);
      file.close();
    }
  } else {
    Serial.println("No cuttingTime file found. Using default value.");
  }
  
  // Prompt user to enter new cutting time or test mode
  Serial.println("Enter new cutting time, or 'TEST1' or 'TEST2' to enter test mode:");

  // Wait for user input (about 10 seconds)
  long startMillis = millis();
  long ledBlinkStartMillis = millis();  // Timer for LED blinking
  bool ledState = LOW;
  bool timeout = false;
  
  // Loop until timeout or valid input
  while (!timeout) {
    if (Serial.available()) {
      String input = Serial.readStringUntil('\n');
      input.trim(); // Trim any extra spaces or newlines
      if (input.length() > 0) {
        if (input.equalsIgnoreCase("TEST")) {
          isTestMode = true;
          testMode();  // Call testMode() for TEST1
          break; // Exit loop for test mode
        } else {
          KILLING_TIME = input.toInt(); // Convert input to integer
          Serial.print("New cutting time set: ");
          Serial.println(KILLING_TIME);

          // Save new cutting time to SPIFFS
          saveCuttingTimeToSPIFFS(KILLING_TIME);
          break; // Exit loop after receiving input
        }
      }
    }

    // Blink the onboard LED every 500ms
    if (millis() - ledBlinkStartMillis >= 500) {
      ledState = !ledState; // Toggle LED state
      digitalWrite(OUTPUT_LED_ONBOARD, ledState); // Set LED state
      ledBlinkStartMillis = millis(); // Reset timer
    }

    // Check if 10 seconds have passed
    if (millis() - startMillis >= 10000) {
      timeout = true;  // Timeout after 10 seconds
    }
  }

  // After timeout, turn off the onboard LED and coil
  digitalWrite(OUTPUT_LED_ONBOARD, LOW);
  digitalWrite(OUTPUT_COIL_1, LOW);
  delay(20);
}

void loop() {
  if (!isTestMode) { // Normal mode
    int SHIFTUP = digitalRead(SENSOR_QUICKSHIFTER);

    if (SHIFTUP == LOW) { 
      digitalWrite(OUTPUT_COIL_1, HIGH); // Turn on relay
      digitalWrite(OUTPUT_LED_ONBOARD, HIGH); // Turn on LED
      delay(KILLING_TIME); // Delay based on cutting time
      digitalWrite(OUTPUT_COIL_1, LOW); // Turn off relay
      digitalWrite(OUTPUT_LED_ONBOARD, LOW); // Turn off LED
      delay(ANTI_CUTTING_TIME); // Delay for anti-cut time
    }
  }
}

// Function for TEST (Random relay operation for 20 seconds)
void testMode() {
  Serial.println("Entering TEST mode: Playing Random Fast Relay Music for 20 seconds");

  long duration = 20000; // 20 seconds in milliseconds
  long startMillis = millis();  // Record start time

  // Run until 20 seconds have passed
  while (millis() - startMillis < duration) {
    int onTime = random(50, 300);  // Random ON time (50-300 ms)
    int offTime = random(50, 300); // Random OFF time (50-300 ms)

    digitalWrite(OUTPUT_COIL_1, HIGH); // Turn on relay
    digitalWrite(OUTPUT_LED_ONBOARD, HIGH); // Turn on LED
    delay(onTime); // Wait for ON time
    digitalWrite(OUTPUT_COIL_1, LOW);  // Turn off relay
    digitalWrite(OUTPUT_LED_ONBOARD, LOW);  // Turn off LED
    delay(offTime); // Wait for OFF time
  }

  Serial.println("TEST mode (Random Music) completed after 20 seconds.");
}

// Function to save cuttingTime to SPIFFS
void saveCuttingTimeToSPIFFS(int value) {
  File file = SPIFFS.open("/cuttingTime.txt", "w");
  if (file) {
    file.println(value);
    file.close();
    Serial.println("Cutting time saved to SPIFFS.");
  } else {
    Serial.println("Failed to open file for writing.");
  }
}
