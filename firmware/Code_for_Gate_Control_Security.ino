//1. Code for Gate Control Security with Automatic Garden Light Control

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Keypad.h>
#include <Servo.h>

// Pin definitions
#define LDR_PIN A0
#define LIGHT_PIN A1
#define RFID_SS 10
#define RFID_RST 9
#define INCORRECT_LED_PIN 13  // LED for incorrect password indication

// Define objects
Servo servo1, servo2;                       // Two servos for two parts of the gate
LiquidCrystal_I2C lcd(0x27, 16, 2);         // LCD with I2C address 0x27 (adjust if needed)
MFRC522 rfid(RFID_SS, RFID_RST);            // RFID object

// Keypad setup
const byte ROWS = 4;                        // 4 rows
const byte COLS = 4;                        // 4 columns
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};




byte rowPins[ROWS] = {8, 7, 6, 5};          // Connect to the row pinouts of the keypad
byte colPins[COLS] = {4, 3, 2, 1};          // Connect to the column pinouts of the keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Password and RFID Tag
String correctPassword = "1234";            // Set correct password
String enteredPassword = "";                // Variable to store entered password

// LDR Threshold
const int lightThreshold = 500;             // Adjust this value as needed
void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Initialize LCD
  lcd.begin(16, 2);  // Specify 16 columns and 2 rows
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Enter Password:");

  // Initialize Servo
  servo1.attach(A2);                         // Servo 1 connected to pin 3
  servo2.attach(A3);                         // Servo 2 connected to pin 4
  servo1.write(0);                          // Initial position (locked)
  servo2.write(180);                        // Initial position (locked, opposite)

  // Initialize RFID
  SPI.begin();
  rfid.PCD_Init();







  // Set pin modes
  pinMode(LDR_PIN, INPUT);
  pinMode(LIGHT_PIN, OUTPUT);
  pinMode(INCORRECT_LED_PIN, OUTPUT);
  digitalWrite(INCORRECT_LED_PIN, LOW);     // Ensure LED is off initially
}
void loop() {
  // 1. LDR Sensor - Control Light
  int ldrValue = analogRead(LDR_PIN);
  digitalWrite(LIGHT_PIN, (ldrValue < lightThreshold) ? HIGH : LOW); // Turn on light if it's dark

  // 2. Keypad - Password Entry
  char key = keypad.getKey();
  if (key) {
    handleKeypress(key);
  }

  // 3. RFID - Check Tag
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    handleRFID();
  }
}
// Handle keypad key press
void handleKeypress(char key) {
  if (key == '#') {                         // Enter key (#)
    if (enteredPassword == correctPassword) {
      unlockDoor();
    } else {
      wrongPassword();
    }
    enteredPassword = "";                   // Reset entered password
  } 




else if (key == '*') {                  // Clear key (*)
    enteredPassword = "";
    updateLCD("Enter Password:", "                ");  // Clear password entry on LCD
  } else {                                  // Add character to entered password
    enteredPassword += key;
    updateLCD("Enter Password:", enteredPassword);  // Update LCD with entered password
  }
}



// Handle RFID tag reading
void handleRFID() {
  String rfidTag = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    rfidTag += String(rfid.uid.uidByte[i], HEX);     // Convert UID to string
  }
  // Display the RFID tag number on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Tag Detected:");
  lcd.setCursor(0, 1);
  lcd.print(rfidTag);                              // Display the tag number

  Serial.print("RFID Tag: ");
  Serial.println(rfidTag);                         // Print tag number to Serial Monitor

  if (rfidTag == "YOUR_RFID_TAG_ID") {             // Replace with your RFID tag ID
    unlockDoor();
  } else {
    wrongPassword();
  }
  



  rfid.PICC_HaltA();                               // Halt the RFID communication
}
// Unlock the door and reset the system
void unlockDoor() {
  updateLCD("Access Granted!", "");
  servo1.write(90);                                // Rotate servo 1 to open the first part
  servo2.write(90);                                // Rotate servo 2 to open the second part
  delay(2000);                                     // Keep unlocked for 2 seconds
  servo1.write(0);                                 // Lock first part of the door
  servo2.write(180);                               // Lock second part of the door
  updateLCD("Enter Password:", "");
  digitalWrite(INCORRECT_LED_PIN, LOW);            // Turn off error LED if it was on
}

// Indicate incorrect password or RFID tag
void wrongPassword() {
  updateLCD("Access Denied!", "");
  digitalWrite(INCORRECT_LED_PIN, HIGH);           // Turn on incorrect LED
  delay(2000);                                     // Display message for 2 seconds
  digitalWrite(INCORRECT_LED_PIN, LOW);            // Turn off incorrect LED
  updateLCD("Enter Password:", "");
}

// Helper function to update LCD
void updateLCD(String line1, String line2) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(line2);
}

