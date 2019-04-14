// Based on the Adafruit Feather example

#include <Arduino.h>
#include <Adafruit_BLE.h>
#include <Adafruit_BluefruitLE_SPI.h>
#include <Adafruit_BluefruitLE_UART.h>

#include "BluefruitConfig.h"
#include "Configuration.h"

// LED error flag
#define LED_PIN 2

// Create the Bluefruit object for Feather 32u4
Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ,
                             BLUEFRUIT_SPI_RST);

const auto heartSensorPin =
    A0;                   // Pulse Sensor PURPLE WIRE connected to ANALOG PIN 0
const int delayMs = 250;  // delay for half a second

// GATT service information
int32_t imuServiceId;
int32_t heartRateCharId;

// A small helper
void error(const __FlashStringHelper *err) {
  if (Serial.available()) {
    Serial.println(err);
  }
  // In any case, turn on the LED to signal the error
  analogWrite(LED_PIN, HIGH);
  while (1)
    ;
}

// Initializes BNO055 sensor
void initSensor(void) { pinMode(heartSensorPin, INPUT); }

void initBluetooth() {
  boolean success;

  // Initialise the module
  if (!ble.begin(VERBOSE_MODE)) {
    error(
        F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check "
          "wiring."));
  }

  // Perform a factory reset to make sure everything is in a known state
  if (!ble.factoryReset()) {
    error(F("Couldn't factory reset."));
  }

  // Disable command echo from Bluefruit
  ble.echo(false);

  // Print Bluefruit information
  ble.info();
  ble.verbose(true);

  // Change the device name to fit its purpose
  if (!ble.sendCommandCheckOK(F("AT+GAPDEVNAME=" BLE_NAME))) {
    error(F("Could not set device name."));
  }

  // Add the IMU Service definition
  success = ble.sendCommandWithIntReply(
      F("AT+GATTADDSERVICE=UUID128=" BLE_SERVICE), &imuServiceId);
  if (!success) {
    error(F("Could not add Heart Rate service."));
  }

  // Add the Orientation characteristic
  success = ble.sendCommandWithIntReply(
      F("AT+GATTADDCHAR=UUID128=" BLE_CHARACTERISTIC
        ",PROPERTIES=0x10,MIN_LEN=1,MAX_LEN=17,VALUE=\"\""),
      &heartRateCharId);
  if (!success) {
    error(F("Could not add Heart Rate characteristic."));
  }

  // Add the Orientation Service to the advertising data
  // (needed for Nordic apps to detect the service)
  ble.sendCommandCheckOK(F("AT+GAPSETADVDATA=02-01-06-05-02-0d-18-0a-18"));

  // Reset the device for the new service setting changes to take effect
  ble.reset();
}

// Sets up the HW an the BLE module (this function is called
// automatically on startup)
void setup(void) {
  delay(500);

  // Set LED error flag
  Serial.begin(115200);

  // Setup the sensor
  initSensor();

  // Setup the Bluetooth
  initBluetooth();
}

void loop(void) {
  int heartRate = analogRead(heartSensorPin);

  // We store the last 10 values, and overwrite the oldest ones (round-robin)
  static const int numValues = 10;
  static int lastValues[numValues];
  static int currentValue = 0;

  lastValues[currentValue] = heartRate;
  currentValue = (currentValue + 1) % numValues;

  static auto lastTime = millis();
  if (millis() - lastTime >= BLE_SAMPLE_RATE_MS) {
    lastTime = millis();

    // Average the last 10 values.
    // This gives us better resilience against suddent jumps that usually
    // happen.
    int average = 0;
    for (int i = 0; i < numValues; i++) average += lastValues[i];
    average /= numValues;

    // Write it to the BLE characteristic
    ble.print(F("AT+GATTCHAR="));
    ble.print(heartRateCharId);
    ble.print(F(","));
    ble.println(String(average));

    // Check if command executed OK
    if (!ble.waitForOK()) {
      error(F("Failed to get response!"));
    }
  }

  // Delay before next measurement update
  delay(SENSOR_SAMPLE_RATE_MS);
}
