/*********************************************************************
  This is an example for our nRF51822 based Bluefruit LE modules

  Pick one up today in the adafruit shop!

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  MIT license, check LICENSE for more information
  All text above, and the splash screen below must be included in
  any redistribution
*********************************************************************/

/*
    Please note the long strings of data sent mean the *RTS* pin is
    required with UART to slow down data sent to the Bluefruit LE!
*/

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <Adafruit_BLE.h>
#include <Adafruit_BluefruitLE_SPI.h>
#include <Adafruit_BluefruitLE_UART.h>
#include <Adafruit_GPS.h>

#include "BluefruitConfig.h"

// LED error flag
#define LED_PIN 2

// Create the Bluefruit object for Feather 32u4
Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ,
                             BLUEFRUIT_SPI_RST);

// Create Adafruit GPS
Adafruit_GPS GPS(&Serial1);

// BNO settings
#define BNO055_SAMPLERATE_DELAY_MS (200)
Adafruit_BNO055 bno = Adafruit_BNO055(55);

// GATT service information
int32_t imuServiceId;
int32_t orientationCharId;
int32_t calibrationCharId;
int32_t locationCharId;

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
void initSensor(void) {
  if (!bno.begin()) {
    error(F("No BNO055 detected. Check your wiring or I2C ADDR!"));
  }
  delay(1000);
  bno.setExtCrystalUse(true);
}

// Keeps track of whether we're using the interrupt
// off by default!
boolean usingInterrupt = false;

void useInterrupt(boolean v) {
  if (v) {
    // Timer0 is already used for millis() - we'll just interrupt somewhere
    // in the middle and call the "Compare A" function above
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
    usingInterrupt = true;
  } else {
    // do not call the interrupt function COMPA anymore
    TIMSK0 &= ~_BV(OCIE0A);
    usingInterrupt = false;
  }
}

// Initializes GPS
void initGPS(void) {
  // 9600 NMEA is the default baud rate for Adafruit MTK GPS's- some use 4800
  GPS.begin(9600);

  // Turn on only the "minimum recommended" data for high update rates!
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);

  // Set the update rate
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_200_MILLIHERTZ);  // 200 MHz update rate
  // For the parsing code to work nicely and have time to sort through the data,
  // and print it out using anything higher than 1 Hz is not suggested

  delay(1000);
  // Ask for firmware version
  Serial1.println(PMTK_Q_RELEASE);

  // This code can have a timer0 interrupt go off
  // every 1 millisecond, and read data from the GPS. That makes the
  // loop code  a lot easier!
  useInterrupt(true);
}

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
  if (!ble.sendCommandCheckOK(F("AT+GAPDEVNAME=NaturelyBT"))) {
    error(F("Could not set device name."));
  }

  // Add the IMU Service definition
  success =
      ble.sendCommandWithIntReply(F("AT+GATTADDSERVICE=UUID128=DE-AD-BE-EF-44-"
                                    "55-66-77-88-99-AA-BB-CC-DD-EE-FF"),
                                  &imuServiceId);
  if (!success) {
    error(F("Could not add Orientation service."));
  }

  // Add the Orientation characteristic
  success = ble.sendCommandWithIntReply(
      F("AT+GATTADDCHAR=UUID128=DE-AD-BE-EF-44-55-66-77-88-99-AA-BB-CC-DD-EE-"
        "FF,PROPERTIES=0x10,MIN_LEN=1,MAX_LEN=17,VALUE=\"\""),
      &orientationCharId);
  if (!success) {
    error(F("Could not add Orientation characteristic."));
  }

  // Add the Orientation Service to the advertising data
  // (needed for Nordic apps to detect the service)
  ble.sendCommandCheckOK(F("AT+GAPSETADVDATA=02-01-06-05-02-0d-18-0a-18"));

  // Add the Calibration characteristic
  success = ble.sendCommandWithIntReply(
      F("AT+GATTADDCHAR=UUID128=BE-EF-DE-AD-44-55-66-77-88-99-AA-BB-CC-DD-EE-"
        "FF,PROPERTIES=0x10,MIN_LEN=1,MAX_LEN=17,VALUE=\"\""),
      &calibrationCharId);
  if (!success) {
    error(F("Could not add Calibration characteristic."));
  }

  // Add the Calibration Service to the advertising data
  // (needed for Nordic apps to detect the service)
  ble.sendCommandCheckOK(F("AT+GAPSETADVDATA=02-01-06-05-02-0d-18-0a-18"));

  // Add the Location characteristic
  success = ble.sendCommandWithIntReply(
      F("AT+GATTADDCHAR=UUID128=BF-EF-DE-AD-44-57-66-77-88-A9-AA-BB-CC-DD-EE-"
        "FF,PROPERTIES=0x10,MIN_LEN=1,MAX_LEN=17,VALUE=\"\""),
      &locationCharId);
  if (!success) {
    error(F("Could not add Location characteristic."));
  }

  // Add the Location Service to the advertising data
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

  pinMode(LED_PIN, OUTPUT);
  analogWrite(LED_PIN, LOW);
  Serial.begin(115200);

  // Setup the BNO055 sensor
  initSensor();

  // Setup the GPS
  initGPS();

  // Setup the Bluetooth
  initBluetooth();
}

// Interrupt is called once a millisecond, looks for any new GPS data, and
// stores it
SIGNAL(TIMER0_COMPA_vect) { char c = GPS.read(); }

bool isCalibrated() {
  /* Get the four calibration values (0..3) */
  /* Any sensor data reporting 0 should be ignored, */
  /* 3 means 'fully calibrated" */
  uint8_t system, gyro, accel, mag;  // variable for gyroscope, accelerometer
                                     // and magnetometer
  system = gyro = accel = mag = 0;
  bno.getCalibration(&system, &gyro, &accel, &mag);

  // Command is sent when \n (\r) or println is called
  // AT+GATTCHAR=CharacteristicID,value
  ble.print(F("AT+GATTCHAR="));
  ble.print(calibrationCharId);
  ble.print(F(","));
  ble.print(String(system));
  ble.print(F(","));
  ble.print(String(gyro));
  ble.print(F(","));
  ble.print(String(accel));
  ble.print(F(","));
  ble.println(String(mag));

  if (gyro >= 2 && mag >= 2) {
    return true;
  } else {
    return false;
  }
}

void orientation() {
  if (!isCalibrated()) {
    return;
  }

  sensors_event_t event;
  bno.getEvent(&event);

  float rotX = event.orientation.x;
  float rotY = event.orientation.y;
  float rotZ = event.orientation.z;

  // Command is sent when \n (\r) or println is called
  // AT+GATTCHAR=CharacteristicID,value
  ble.print(F("AT+GATTCHAR="));
  ble.print(orientationCharId);
  ble.print(F(","));
  ble.print(String(rotX));
  ble.print(F(","));
  ble.print(String(rotY));
  ble.print(F(","));
  ble.println(String(rotZ));
}

void location() {
  // if a sentence is received, we can check the checksum, and then parse it...
  if (GPS.newNMEAreceived()) {
    // If we print the NMEA sentence, or data
    // we end up not listening and catching other sentences!
    // so be very wary if using OUTPUT_ALLDATA and trying to print out data
    // Serial.println(GPS.lastNMEA());   // this also sets the newNMEAreceived()
    // flag to false

    if (!GPS.parse(GPS.lastNMEA()))  // this also sets the newNMEAreceived()
                                     // flag to false
      return;  // we can fail to parse a sentence in which case we should just
               // wait for another

    // if (!GPS.fix) return

    // Command is sent when \n (\r) or println is called
    // AT+GATTCHAR=CharacteristicID,value
    ble.print(F("AT+GATTCHAR="));
    ble.print(locationCharId);
    ble.print(F(","));
    ble.print(GPS.latitudeDegrees, 4);
    ble.print(F(","));
    ble.println(GPS.longitudeDegrees, 4);
  }
}

void loop(void) {
  orientation();
  location();

  // Check if command executed OK
  if (!ble.waitForOK()) {
    error(F("Failed to get response!"));
  }

  // Delay before next measurement update
  delay(BNO055_SAMPLERATE_DELAY_MS);
}
