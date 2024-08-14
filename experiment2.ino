#include <Wire.h>
#include <RTClib.h>  // Include library for real-time clock

RTC_DS1307 rtc;  // Create an RTC object

const int AOUTpin = A0;  // Define the analog output pin connected to the sensor

// Calibration constants derived from the calibration process
const float m = 22.22;  // Slope from calibration curve
const float b = -11.11; // Intercept from calibration curve

void setup() {
  Serial.begin(9600);  // Start serial communication at 9600 baud rate
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);  // Stop if RTC is not found
  }

  // Check if the RTC is running
  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    rtc.adjust(DateTime(F(_DATE), F(TIME_)));  // Set RTC to compile time
  }
}

void loop() {
  DateTime now = rtc.now();  // Get the current date and time from the RTC

  int sensorValue = analogRead(AOUTpin);  // Read the analog value from the sensor
  float voltage = sensorValue * (5.0 / 1023.0);  // Convert the analog reading to voltage

  float concentration = m * voltage + b;  // Convert voltage to ethylene concentration in ppm

  // Print the current date, time, and ethylene concentration
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.print(", Ethylene Concentration (ppm): ");
  Serial.println(concentration);

  delay(18000000);  // Log data every 5 hours (5 * 60 * 60 * 1000 milliseconds)
}
