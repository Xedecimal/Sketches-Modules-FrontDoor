// SERIAL WRITING OUTPUT WILL BREAK EVERYTHING NEVER DO IT!

#define SKETCH_NAME "ModuleFrontDoor"
#define SKETCH_VERSION "1.0"
#define MY_BAUD_RATE 115200
#define MY_NODE_ID 46

// #define NODEMANAGER_SLEEP OFF
// #define NODEMANAGER_OTA_CONFIGURATION ON
// #define NODEMANAGER_DEBUG ON
// #define NODEMANAGER_CONDITIONAL_REPORT ON

#include <XMySensors/XMySensors.h>
#include <MySensors_NodeManager.h>

// Add MQ sensor

#include <sensors/SensorRelay.h>
SensorRelay lock(7);

// Add door lock relay

// Add door sensor

bool inited = false;

void before()
{
	lock.setInvertValueToWrite(ON);
	// Stop relay from triggering on boot.
	digitalWrite(7, HIGH);
	nodeManager.setReportIntervalSeconds(10);
	nodeManager.before();
}

void setup()
{
	nodeManager.setup();
}

void presentation()
{
	nodeManager.presentation();
}

void loop()
{
	// Must send all values at least once for HASS to show them.
	if (!inited) {
		// Relay Door Lock
		send(MyMessage(1, V_STATUS).set(0));

		inited = true;
	}
	nodeManager.loop();
}

void receive(const MyMessage &message)
{
	nodeManager.receive(message);
}
