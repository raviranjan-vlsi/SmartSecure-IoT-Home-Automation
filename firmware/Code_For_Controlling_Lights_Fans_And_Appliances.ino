//3. Code For Controlling Lights, Fans, And Appliances Through Relays, Touch Switches And Bluetooth/Voice Command

#include <EEPROM.h>
#include <SoftwareSerial.h>

// Define pin assignments
const int ledPin1 = 12;          // LED relay 1 pin
const int ledPin2 = 11;           // LED relay 2 pin
const int ledPin3 = 13;           // LED relay 3 pin
const int fanRelayPin = 10;       // Fan relay pin
const int switchPin1 = 9;        // Touch switch for LED 1
const int switchPin2 = 8;       // Touch switch for LED 2
const int switchPin3 = 7;       // Touch switch for LED 3
const int fanSwitchPin = 6;     // Touch switch for Fan

// EEPROM addresses
const int eepromAddress1 = 0;    // EEPROM address for LED 1 state
const int eepromAddress2 = 1;    // EEPROM address for LED 2 state
const int eepromAddress3 = 2;    // EEPROM address for LED 3 state
const int eepromAddressFan = 3;  // EEPROM address for Fan state

// States for LEDs and fan
bool ledState1, ledState2, ledState3, fanState;

// Button states for debouncing
bool lastButtonState1 = LOW, lastButtonState2 = LOW, lastButtonState3 = LOW, lastFanButtonState = LOW;
bool buttonPressed1 = false, buttonPressed2 = false, buttonPressed3 = false, fanButtonPressed = false;

// Bluetooth communication
SoftwareSerial Bluetooth(4, 5);  // RX, TX pins for Bluetooth module





// string for bluetooth
String command;

void setup() {
  // Set pins as outputs
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(fanRelayPin, OUTPUT);

  // Set touch switch pins as inputs with pull-up resistors
  pinMode(switchPin1, INPUT_PULLUP);
  pinMode(switchPin2, INPUT_PULLUP);
  pinMode(switchPin3, INPUT_PULLUP);
  pinMode(fanSwitchPin, INPUT_PULLUP);

  // Initialize Bluetooth and Serial communication
  Bluetooth.begin(9600);
  Serial.begin(9600);

  // Read previous states from EEPROM
  ledState1 = EEPROM.read(eepromAddress1);
  ledState2 = EEPROM.read(eepromAddress2);
  ledState3 = EEPROM.read(eepromAddress3);
  fanState = EEPROM.read(eepromAddressFan);

  // Set LEDs and fan to the last saved states
  digitalWrite(ledPin1, ledState1 ? HIGH : LOW);
  digitalWrite(ledPin2, ledState2 ? HIGH : LOW);
  digitalWrite(ledPin3, ledState3 ? HIGH : LOW);
  digitalWrite(fanRelayPin, fanState ? HIGH : LOW);
}




void loop() {
  // Bluetooth control
  while(Bluetooth.available()) {
   delay(10);
    char data = Bluetooth.read();
     if (data == '#') {break;} //Exit the loop when the # is detected after the word
    command += data;
  }
    String last_command;
    if( command.length() > 0 )
    {
      
     // Control LEDs via Bluetooth commands
     if (command == "turn off entrance light") {
      ledState1 = true;
      digitalWrite(ledPin1, HIGH);
      EEPROM.write(eepromAddress1, ledState1);
      Serial.println(command);
      // Bluetooth.println("turning off entrance light");
      last_command = command;
       command = "";

     } else if (command == "turn on entrance light") {
      ledState1 = false;
      digitalWrite(ledPin1, LOW);
      EEPROM.write(eepromAddress1, ledState1);

       Serial.println(command);
      // Bluetooth.println("turning on entrance light");
      last_command = command;
      command = "";
     }




 else if (command == "turn off room light") {
      ledState2 = true;
      digitalWrite(ledPin2, HIGH);
      EEPROM.write(eepromAddress2, ledState2);
       Serial.println(command);
      // Bluetooth.println("turning off room light");
      last_command = command;
      command = "";
     } 
else if (command == "turn on room light") {
      ledState2 = false;
      digitalWrite(ledPin2, LOW);
      EEPROM.write(eepromAddress2, ledState2);
       Serial.println(command);
      // Bluetooth.println("turning on room light");
      last_command = command;
      command = "";
     }
 else if (command == "turn off garden light") {
      ledState3 = true;
      digitalWrite(ledPin3, HIGH);
      EEPROM.write(eepromAddress3, ledState3);
       Serial.println(command);
      // Bluetooth.println("turning on garden light");
      last_command = command;
      command = "";
     }
 else if (command == "turn on garden light") {
      ledState3 = false;
      digitalWrite(ledPin3, LOW);
      EEPROM.write(eepromAddress3, ledState3);
       Serial.println(command);
      // Bluetooth.println("turning on garden light");
      last_command = command;
      command = "";
     } 
else if (command == "turn on fan") {  // Fan ON command
      fanState = true;
      digitalWrite(fanRelayPin, HIGH);
      EEPROM.write(eepromAddressFan, fanState);
      Serial.println(command);
      // Bluetooth.println("turning on fan");
      last_command = command;
      command = "";
     } else if (command == "turn off fan") {  // Fan OFF command
      fanState = false;
      digitalWrite(fanRelayPin, LOW);
      EEPROM.write(eepromAddressFan, fanState);
      // Bluetooth.println("turning off fan");
      Serial.println(command);
      last_command = command;
      command = "";
     }
       // Handle unrecognized commands
      Bluetooth.println("Invalid Command: " + command);
      Serial.println("Unrecognized Command: " + command);
    
     }

  // Physical touch switch control
  checkSwitch(switchPin1, ledPin1, ledState1, eepromAddress1, lastButtonState1, buttonPressed1);
  checkSwitch(switchPin2, ledPin2, ledState2, eepromAddress2, lastButtonState2, buttonPressed2);
  checkSwitch(switchPin3, ledPin3, ledState3, eepromAddress3, lastButtonState3, buttonPressed3);
  checkSwitch(fanSwitchPin, fanRelayPin, fanState, eepromAddressFan, lastFanButtonState, fanButtonPressed);
}

// Function to check and debounce touch switches
void checkSwitch(int switchPin, int relayPin, bool &state, int eepromAddress, bool &lastButtonState, bool &buttonPressed) {
  bool buttonState = digitalRead(switchPin);


  // Detect falling edge (button press)
  if (buttonState == LOW && lastButtonState == HIGH && !buttonPressed) {
    buttonPressed = true;           // Mark button as pressed
    state = !state;                 // Toggle state
    digitalWrite(relayPin, state ? HIGH : LOW);  // Update relay state
    EEPROM.write(eepromAddress, state);         // Save state to EEPROM
  }

  // Reset button pressed state when released
  if (buttonState == HIGH) {
    buttonPressed = false;
  }

  // Update last button state
  lastButtonState = buttonState;
}












