#include "Arduino.h"
#include "Datalogger.h"
#include "StateMachine.h"
#include "Sensors.h"


DataLogger DataLogger_;
StateMachine StateMachine_;
Sensors Sensors_;

void setup() {
  Serial.begin(115200); 
  while (!Serial); // Wait for serial connection to initialize
  Sensors_.initialize();
  DataLogger_.initialize();
  // Controls_.initialize(); 

}

void loop() {
  // Serial.println("Hello Space");
  FlightData data = Sensors_.readFlightData();
  DataLogger_.logFlightData(data);
  // Controller.control(data)
  delay(100);
 
}