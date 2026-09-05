#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

// =====================================================
// LCD PINS
// =====================================================
const int rs = 11;
const int en = 12;
const int d4 = 5;
const int d5 = 4;
const int d6 = 3;
const int d7 = 2;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// =====================================================
// GAS SENSOR PINS - ARDUINO UNO
// =====================================================
const int mq135Pin = A0;
const int mq7Pin   = A1;
const int mq5Pin   = A2;

// =====================================================
// SIM800L GSM PINS - ARDUINO UNO
// =====================================================
// Arduino UNO RX <- SIM800L TX
// Arduino UNO TX -> SIM800L RX

const int gsmRX = 7;
const int gsmTX = 8;

SoftwareSerial gsm(gsmRX, gsmTX);

// =====================================================
// POLLUTION THRESHOLDS
// =====================================================
const int mq135Threshold = 500;
const int mq7Threshold   = 500;
const int mq5Threshold   = 500;

// =====================================================
// PHONE NUMBER
// =====================================================
String phoneNumber = "+1234567890";
// Replace with your actual phone number

// =====================================================
// SETUP
// =====================================================
void setup() {

  // Serial Monitor
  Serial.begin(9600);

  // GSM
  gsm.begin(9600);

  // LCD
  lcd.begin(16, 2);

  // Welcome message
  lcd.setCursor(0, 0);
  lcd.print("AIR POLLUTION");
  lcd.setCursor(0, 1);
  lcd.print("MONITORING");

  delay(2000);
  lcd.clear();

  Serial.println("================================");
  Serial.println("Air Pollution Monitoring System");
  Serial.println("Arduino UNO + SIM800L");
  Serial.println("================================");

  // Initialize GSM
  Serial.println("Initializing GSM...");

  sendATCommand("AT");
  sendATCommand("AT+CPIN?");
  sendATCommand("AT+CREG?");
  sendATCommand("AT+CMGF=1");

  delay(2000);

  Serial.println("System Ready");
}

// =====================================================
// MAIN LOOP
// =====================================================
void loop() {

  // Read gas sensors
  int mq135Value = analogRead(mq135Pin);
  int mq7Value   = analogRead(mq7Pin);
  int mq5Value   = analogRead(mq5Pin);

  // ===================================================
  // SERIAL MONITOR
  // ===================================================

  Serial.print("MQ-135: ");
  Serial.print(mq135Value);

  Serial.print(" | MQ-7: ");
  Serial.print(mq7Value);

  Serial.print(" | MQ-5: ");
  Serial.println(mq5Value);

  // ===================================================
  // LCD DISPLAY
  // ===================================================

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("135:");
  lcd.print(mq135Value);

  lcd.setCursor(9, 0);
  lcd.print("7:");
  lcd.print(mq7Value);

  lcd.setCursor(0, 1);
  lcd.print("5:");
  lcd.print(mq5Value);

  // ===================================================
  // POLLUTION DETECTION
  // ===================================================

  if (mq135Value > mq135Threshold ||
      mq7Value > mq7Threshold ||
      mq5Value > mq5Threshold) {

    Serial.println("WARNING: HIGH GAS LEVEL DETECTED!");

    delay(500);

    // Display warning
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("WARNING!");

    lcd.setCursor(0, 1);
    lcd.print("HIGH POLLUTION");

    // Create SMS
    String message =
      "Vehicle Pollution Warning! "
      "MQ135=" + String(mq135Value) +
      " MQ7=" + String(mq7Value) +
      " MQ5=" + String(mq5Value);

    // Send SMS
    sendSMS(phoneNumber, message);

    // Wait before checking again
    delay(10000);

  } else {

    Serial.println("Pollution Level: NORMAL");

  }

  delay(2000);
}

// =====================================================
// SEND AT COMMAND
// =====================================================
void sendATCommand(String command) {

  Serial.print("AT Command: ");
  Serial.println(command);

  gsm.println(command);

  delay(1000);

  while (gsm.available()) {

    String response = gsm.readString();

    Serial.print("GSM Response: ");
    Serial.println(response);
  }
}

// =====================================================
// SEND SMS
// =====================================================
void sendSMS(String number, String message) {

  Serial.println("Sending SMS...");

  // Set SMS text mode
  gsm.println("AT+CMGF=1");

  delay(1000);

  // Select recipient
  gsm.print("AT+CMGS=\"");
  gsm.print(number);
  gsm.println("\"");

  delay(1000);

  // Send message
  gsm.print(message);

  delay(500);

  // Ctrl + Z
  gsm.write(26);

  delay(5000);

  Serial.println("SMS process completed.");
}

