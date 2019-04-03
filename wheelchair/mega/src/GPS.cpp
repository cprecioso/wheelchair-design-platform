
#include "GPS.h"

namespace GPS {
// Create Adafruit GPS
Adafruit_GPS GPS(&Serial1);

// Initializes GPS
void setup() {
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
}

void loop() {
  GPS.read();

  static auto lastTime = millis() + 500;
  if (millis() - lastTime < 1000) return;
  lastTime = millis();

  // if a sentence is received, we can check the checksum, and then parse it...
  if (!GPS.newNMEAreceived()) return;

  // If we print the NMEA sentence, or data
  // we end up not listening and catching other sentences!
  // so be very wary if using OUTPUT_ALLDATA and trying to print out data
  // Serial.println(GPS.lastNMEA());   // this also sets the
  // newNMEAreceived() flag to false

  if (!GPS.parse(GPS.lastNMEA()))  // this also sets the newNMEAreceived()
                                   // flag to false
    return;  // we can fail to parse a sentence in which case we should just
             // wait for another

  // if (!GPS.fix) return;

  // Command is sent when \n (\r) or println is called
  messenger.sendCmdStart(kGPS);
  messenger.sendCmdArg(String(GPS.latitudeDegrees, 4));
  messenger.sendCmdArg(String(GPS.longitudeDegrees, 4));
  messenger.sendCmdEnd();
}
}  // namespace GPS
