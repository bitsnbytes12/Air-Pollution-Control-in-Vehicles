#include <Wire.h>
#include <LiquidCrystal.h>
#include <HardwareSerial.h>

// LCD pins
const int rs = 11, en = 12, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Sensor pins
const int mq135Pin = 32; // MQ135 connected to A0
const int mq7Pin = 33;   // MQ7 connected to A1
const int mq5Pin = 35;   // MQ5 connected to A2

// GSM module pins
#define RXD2 16  // ESP32 RX pin connected to SIM800L TX
#define TXD2 17  // ESP32 TX pin connected to SIM800L RX
#define RESET_PIN 5 // Reset pin (optional)

// Initialize hardware serial for GSM communication
HardwareSerial gsm(1);  // UART1 for SIM800L

void setup() {
  // Initialize LCD
  lcd.begin(16,2);
  
  // Print a welcome message to the LCD
  lcd.setCursor(0, 0);
  lcd.print("Gas Sensor Test");
  delay(2000);
  lcd.clear();
  
  // Initialize serial communication (for debugging)
  Serial.begin(115200);
  gsm.begin(9600, SERIAL_8N1, RXD2, TXD2);  // Start GSM communication
  
  // Initialize GSM module
  pinMode(RESET_PIN, OUTPUT);
  digitalWrite(RESET_PIN, HIGH); // Keep module on
  
  Serial.println("Initializing GSM module...");
  sendATCommand("AT");
  sendATCommand("AT+CPIN?");  // Check if SIM card is ready
  sendATCommand("AT+CREG?");  // Check network registration
  sendATCommand("AT+CMGF=1");  // Set SMS mode to text

  delay(2000); // Wait for GSM module to stabilize
}

void loop() {
  // Read sensor values
  int mq135Value = analogRead(mq135Pin);
  int mq7Value = analogRead(mq7Pin);
  int mq5Value = analogRead(mq5Pin);
  
  // Display sensor values on the LCD
  lcd.setCursor(0, 0);
  lcd.print("M135:");
  lcd.print(mq135Value);
  
  lcd.setCursor(9, 0);
  lcd.print("M7:");
  lcd.print(mq7Value);
  
  lcd.setCursor(0, 1);
  lcd.print("M5:");
  lcd.print(mq5Value);

  // Print sensor values to the serial monitor
  Serial.print("MQ135: ");
  Serial.print(mq135Value);
  Serial.print(" | MQ7: ");
  Serial.print(mq7Value);
  Serial.print(" | MQ5: ");
  Serial.println(mq5Value);
  
  // Example: Trigger an SMS if MQ135 value exceeds threshold
  if (mq135Value > 500) {
    String phoneNumber = "+1234567890";  // Replace with destination phone number
    String message = "Warning: High gas levels detected! MQ135 value: " + String(mq135Value);
    sendSMS(phoneNumber, message);
  }

  // Delay before the next loop iteration
  delay(2000);
}

// Function to send AT commands to the GSM module
void sendATCommand(String cmd) {
  gsm.println(cmd);
  delay(1000);  // Give the module time to respond
  while (gsm.available()) {
    String response = gsm.readString();
    Serial.print("Response: ");
    Serial.println(response);
  }
}

// Function to send SMS
void sendSMS(String phoneNumber, String message) {
  Serial.println("Sending SMS...");
  
  // Start SMS text mode
  gsm.print("AT+CMGS=\"");
  gsm.print(phoneNumber);
  gsm.println("\"");
  delay(1000);  // Wait for prompt
  
  // Send the actual message content
  gsm.print(message);
  delay(1000);
  
  // End the message by sending Ctrl+Z character
  gsm.write(26);
  delay(1000);
  
  Serial.println("SMS Sent!");
}
