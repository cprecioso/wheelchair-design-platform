#include "ServoMotor.h"

namespace ServoMotor {
const byte servoPin = 9;

// Create Servo
Servo myservo;

void setup() { myservo.attach(servoPin); }

void setAngle(byte angle) { myservo.write(angle); }
}  // namespace ServoMotor
