/* an example message:
   m r 100 200
   means
   move relative steps (speed)100 (units)200
*/

#include <Streaming.h>
#include <Messenger.h>
#include <AccelStepper.h>

#include "structs.h"

AccelStepper stepper(1, 3, 6);
Messenger message = Messenger();

void runOp(opSettings_t opSettings) {
  Serial << "Op:" << endl;
  Serial << "relativity: " << opSettings.relativity << endl;
  Serial << "speed: " << opSettings.speed << endl;
  Serial << "position: " << opSettings.position << endl;
  stepper.setAcceleration(opSettings.speed);
  switch (opSettings.relativity) {
    case RELATIVE:
      Serial << "Moving relative to " << opSettings.position << endl;
      stepper.move(opSettings.position);
      break;
    case ABSOLUTE:
      Serial << "Moving absolute to " << opSettings.position << endl;
      stepper.moveTo(opSettings.position);
      break;
  }
}

void processMessage() {
  if (message.checkString("m")) {
    opSettings_t opSettings;
    if (message.checkString("a")) {
      opSettings.relativity = ABSOLUTE;
    } else if (message.checkString("r")) {
      opSettings.relativity = RELATIVE;
    }
    opSettings.speed = message.readLong();
    opSettings.position = message.readLong();
    runOp(opSettings);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(8, INPUT_PULLUP);
  stepper.setMaxSpeed(1000);
  stepper.setAcceleration(500);
  stepper.move(100000000);
  while (digitalRead(8) != LOW) {
    stepper.run();
  }
  stepper.stop();
  stepper.setCurrentPosition(0);
  message.attach(processMessage);
}

void loop() {
  while (Serial.available()) {
    message.process(Serial.read());
  }
  stepper.run();
}
