#include "Arduino.h"
#include "constants.h"
#include "control.h"
#include "control_hardware.h"
#include "data_logger.h"
#include "sensors.h"
#include "state_machine.h"
#include <vector>

DataLogger data_logger;
StateMachine state_machine(data_logger);
Sensors sensors(data_logger);
ControlHardware control_hardware;
Control control;

float error;

unsigned long lastSwitchTime = 0;
const unsigned long interval = 10000; 

std::vector<float> setpoints = {0.0f, 90.0f};
int setpoint_index = 0;

struct TelemetryData {
    float altitude;
    float verticalVelocity;
    float accZ;
    float rotZ;
    float error;
    uint32_t timestamp;
} __attribute__((packed));

void sendToSerial(Print &serial, FlightData data, Control control) {
    TelemetryData telem;
    telem.altitude = data.altitude;
    telem.verticalVelocity = data.verticalVelocity;
    telem.accZ = data.accZ;
    telem.rotZ = data.oriZ;
    telem.error = control.get_error();
    telem.timestamp = micros();

    serial.write((uint8_t *)&telem, sizeof(telem));
}

void logTelemetryToSerial(Print &serial, const FlightData& data, const Control& control) {
    // Print values to Serial
    serial.print("Altitude: ");
    serial.println(data.altitude);
    serial.print("Vertical Velocity: ");
    serial.println(data.verticalVelocity);
    serial.print("AccelZ: ");
    serial.println(data.accZ);
    serial.print("RotZ: ");
    serial.println(data.rotZ);
    serial.print("AccelMagnitude: ");
    serial.println(data.accelMagnitude);
    serial.print("RBF Removed: ");
    serial.println(data.rbfRemoved);
    serial.print("Acc (x, y, z): ");
    serial.print(data.accX);
    serial.print(", ");
    serial.print(data.accY);
    serial.print(", ");
    serial.println(data.accZ);
    serial.print("Gyro Angular Rate (x, y, z): ");
    serial.print(data.rotX);
    serial.print(", ");
    serial.print(data.rotY);
    serial.print(", ");
    serial.println(data.rotZ);
    serial.print("Orientation (x, y, z): ");
    serial.print(data.oriX);
    serial.print(", ");
    serial.print(data.oriY);
    serial.print(", ");
    serial.println(data.oriZ);
    serial.print("Mag: ");
    serial.print(data.magX);
    serial.print(", ");
    serial.print(data.magY);
    serial.print(", ");
    serial.println(data.magZ), Serial.print("Heading: ");
    serial.println(data.heading);
    serial.println("--------------------");

    serial.println("Control error:");
    error = control.get_error();
    
    serial.println(error);
    serial.print("Current setpoint: ");
    serial.println(setpoints[setpoint_index]);
}

void setup() {
    Serial.begin(9600);
    Serial8.begin(9600);

    data_logger
        .Initialize();  // Initialize this before anything else to log failures
    sensors.Initialize();
    //control_hardware.Initialize();
    control.Initialize();
    data_logger.LogEvent(LogType::kInfo, "SETUP COMPLETE");

    pinMode(constants::kLEDPin, OUTPUT);  // Set LED pin as output
}

/**
 * @brief Arduino main loop.
 *
 * Reads sensor data, logs flight telemetry, and performs control.
 */
void loop() {
    FlightData data = sensors.ReadFlightData();
    data_logger.LogFlightData(data);

    /*unsigned long currentTime = millis();

    if (currentTime - lastSwitchTime >= interval) {
        lastSwitchTime = currentTime;

        // Run PID with current setpoint
        control.PID(
            setpoints[setpoint_index],
            data.oriZ
        );

        // Move to next setpoint
        setpoint_index = (setpoint_index + 1) % setpoints.size();
    }*/
    // char serializedFlightData[512] = "";
    // data.SerializeJson(serializedFlightData, sizeof(serializedFlightData));
    // Serial8.println(serializedFlightData);

    // the above allows switching the reference angle

    control.PID(
        90.0f,
        data.oriZ
    );

    // logTelemetryToSerial(Serial, data, control);
    // uncomment the above for live telemetry

    sendToSerial(Serial8, data, control);
}
