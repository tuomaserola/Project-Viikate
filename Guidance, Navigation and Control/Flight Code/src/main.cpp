#include "StateMachine.h"
#include "Sensors.h"
#include "Arduino.h"

StateMachine StateMachine_;
Sensors Sensors_;

void setup() {
  Sensors_.initialize();
  Serial.begin(9600);
  //Pins.initialize(); 
  //Controls.initialize();


}

void loop() {
  //Serial.print("Hello World");
  FlightData data = Sensors_.readFlightData();
  Serial.println(data.rotatZ);
  delay(100);
 
}