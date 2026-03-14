// 2. Code for Environmental Monitoring System and Blynk Integration 

#define BLYNK_PRINT Serial

// Blynk configuration
#define BLYNK_TEMPLATE_ID "TMPL3g8vg3o2Y"
#define BLYNK_TEMPLATE_NAME "arduino R4"
#define BLYNK_AUTH_TOKEN "qrxKXXIYXy_7C9dWLfqRs7-ETsPwn60w"

#include <SPI.h>
#include <WiFiS3.h>
#include <BlynkSimpleWifi.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"
#include <Servo.h>

// Matrix and LCD setup
ArduinoLEDMatrix matrix;
LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(12, DHT11);

// Wi-Fi credentials
char ssid[] = "RKranjan";
char pass[] = "9608109057";

// Pin Definitions
#define GREEN_LIGHT 3
#define WHITE_LIGHT 4
#define RED_LIGHT 5
#define ALERT_LED 6
#define MQ2_PIN A0




#define BUZZER_PIN 11
#define RAIN_SENSOR_PIN A1
#define SERVO_PIN 8

// Virtual pins for Blynk
#define VIRTUAL_PIN_TEMPERATURE V1
#define VIRTUAL_PIN_HUMIDITY V2

// Global variables
float gasValue = 0;
bool gasDetected = false;
unsigned long lcdUpdateTimer = 0;
unsigned long gasCheckTimer = 0;
unsigned long rainCheckTimer = 0;
bool blynkConnected = false;
bool isRoofClosed = false;

// Previous values for change detection
float prevTemp = -999, prevHum = -999;

// Servo object for roof movement
Servo roofServo;

// Function declarations
void readSensors();
void checkGasSensor();
void checkRainSensor();
void updateLCD();
void handleGasAlert();






void setup() {
  Serial.begin(115200);

  // Pin modes
  pinMode(GREEN_LIGHT, OUTPUT);
  pinMode(WHITE_LIGHT, OUTPUT);
  pinMode(RED_LIGHT, OUTPUT);
  pinMode(ALERT_LED, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Initialize sensors and display
  dht.begin();
  lcd.init();
  lcd.backlight();
  matrix.begin();
  roofServo.attach(SERVO_PIN);
  roofServo.write(0); // Initialize with roof open

  // Wi-Fi setup
  WiFi.begin(ssid, pass);
  Blynk.config(BLYNK_AUTH_TOKEN);

  // Initial LCD message
  lcd.setCursor(0, 0);
  lcd.print("Initializing...");
  delay(2000);

  // led matrix
  matrix.begin();
  matrix.beginDraw();
  matrix.stroke(0xFFFFFFFF);





  matrix.textScrollSpeed(100);
  matrix.textFont(Font_4x6);
  matrix.beginText(0, 1, 0xFFFFFF);


  matrix.println(" RKRanjan ");
  matrix.endText(SCROLL_LEFT);
  matrix.endDraw();
}

void loop() {
  // Attempt to connect to Blynk if not connected
  if (WiFi.status() == WL_CONNECTED && !blynkConnected) {
    blynkConnected = Blynk.connect(2000);
  }

  if (blynkConnected) {
    Blynk.run();
  }

  // Sensor reading and handling
  readSensors();
  checkGasSensor();
  checkRainSensor();
  handleGasAlert();
  updateLCD();
  scrollMatrixText();
}

void readSensors() {
  // Update sensor values every 1 second
  if (millis() - lcdUpdateTimer >= 1000) {
    lcdUpdateTimer = millis();




    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    Serial.println(temperature);
    Serial.println(humidity);


    // Check if the readings are valid
    if (!isnan(temperature) && !isnan(humidity)) {
      // Update Blynk values if connected
      if (blynkConnected) {
        Blynk.virtualWrite(VIRTUAL_PIN_TEMPERATURE, temperature);
        Blynk.virtualWrite(VIRTUAL_PIN_HUMIDITY, humidity);
      }

      // Save the values for LCD display
      prevTemp = temperature;
      prevHum = humidity;
      
    } else {
      Serial.println("DHT Sensor Error!");
    }
  }
}

void checkGasSensor() {
  // Prioritize gas sensor by reading it frequently
  if (millis() - gasCheckTimer >= 500) {
    gasCheckTimer = millis();
    gasValue = analogRead(MQ2_PIN);
    gasDetected = (gasValue > 260); // Set your threshold




    // Debugging logs
    Serial.print("Gas Value: ");
    Serial.println(gasValue);
  }
}

void smoothServoMove(Servo &servo, int startAngle, int endAngle, int delayMs) {
  if (startAngle < endAngle) {
    for (int angle = startAngle; angle <= endAngle; angle++) {
      servo.write(angle);
      delay(delayMs); // Delay for smooth motion
    }
  } else {
    for (int angle = startAngle; angle >= endAngle; angle--) {
      servo.write(angle);
      delay(delayMs); // Delay for smooth motion
    }
  }
}

void checkRainSensor() {
  // Check rain sensor every 500 ms
  if (millis() - rainCheckTimer >= 500) {
    rainCheckTimer = millis();
    int rainValue = analogRead(RAIN_SENSOR_PIN);
    Serial.print("Rain Sensor Value: ");
    Serial.println(rainValue);

    if (rainValue < 500 && !isRoofClosed) {
      // Rain detected, close the roof smoothly
      Serial.println("Rain detected. Closing roof...");
      smoothServoMove(roofServo, 0, 100, 10); // Move servo from 0° to 90° with a delay of 10ms
      isRoofClosed = true;
    }


 else if (rainValue >= 500 && isRoofClosed) {
      // No rain, open the roof smoothly
      Serial.println("No rain detected. Opening roof...");
      smoothServoMove(roofServo, 100, 0, 10); // Move servo from 90° to 0° with a delay of 10ms
      isRoofClosed = false;
    }}}

void handleGasAlert() {
  // Alert if gas is detected
  if (gasDetected) {
    digitalWrite(ALERT_LED, HIGH);
    tone(BUZZER_PIN, 1000);
  } else {
    digitalWrite(ALERT_LED, LOW);
    noTone(BUZZER_PIN);
  }
}

void updateLCD() {
  // Update LCD with T (Temp), H (Humidity), and G (Gas) values
lcd.setCursor(0, 0);
lcd.print("T:");
lcd.print(prevTemp);
lcd.print("C       ");
lcd.setCursor(0, 1);
lcd.print("H:");
lcd.print(prevHum);
lcd.print("% ");
lcd.setCursor(10, 1);
lcd.print("G:");
lcd.print(gasValue);
}




// Matrix Text Scrolling
void scrollMatrixText() {
  static unsigned long lastScrollTime = 0;
  if (millis() - lastScrollTime > 500) {
    lastScrollTime = millis();
    matrix.beginDraw();



    matrix.stroke(0xFFFFFFFF);
    matrix.textScrollSpeed(80);
    matrix.textFont(Font_5x7);
    matrix.beginText(0, 1, 0xFFFFFF);
    matrix.println(" GGV ECE - HOME AUTOMATION ");
    matrix.endText(SCROLL_LEFT);
    matrix.endDraw();
  }
}

// Blynk Button Controls
BLYNK_WRITE(V0) {
  digitalWrite(GREEN_LIGHT, param.asInt());
}
BLYNK_WRITE(V4) {
  digitalWrite(WHITE_LIGHT, param.asInt());
}
BLYNK_WRITE(V3) {
  digitalWrite(RED_LIGHT, param.asInt());
}

