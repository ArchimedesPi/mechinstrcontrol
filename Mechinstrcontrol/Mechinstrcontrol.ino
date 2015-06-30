/* an example message:
   m r s 100 200
   means
   move relative steps (speed)100 (units)200
*/

#include <Streaming.h>
#include <Messenger.h>

Messenger message = Messenger();
void processMessage();
typedef enum {RELATIVE, ABSOLUTE} relativity_t;
typedef enum {STEPS, MM} unit_t;
typedef struct opSettings_t {
	relativity_t relativity;
	unit_t unit;
	int speed;
	int position;
} opSettings_t;

void setup() {
	Serial.begin(115200);
	message.attach(processMessage);
}

void runOp(opSettings_t opSettings) {
	Serial << "Op:" << endl;
	Serial << "relativity: " << opSettings.relativity << endl;
	Serial << "unit: " << opSettings.unit << endl;
	Serial << "speed: " << opSettings.speed << endl;
	Serial << "position: " << opSettings.position << endl;
}

void processMessage() {
	if (message.checkString("m")) {
		opSettings_t opSettings;
		switch (message.readChar()) {
			case 'r':
				opSettings.relativity = RELATIVE;
			case 'a':
				opSettings.relativity = ABSOLUTE;
		}
		switch (message.readChar()) {
			case 's':
				opSettings.unit = STEPS;
			case 'm':
				opSettings.unit = MM;
		}
		opSettings.speed = readInt();
		opSettings.position = readInt();
		runOp(opSettings);
	}
}

void loop() {
	while (Serial.available()) {
		message.process(Serial.read());
	}
}
