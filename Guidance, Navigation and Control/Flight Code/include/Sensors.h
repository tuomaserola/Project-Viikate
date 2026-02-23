#ifndef SENSORS
#define SENSORS

#include "FlightData.h"
#include "Arduino.h"
#include "Constants.h"
#include "Wire.h"
#include "MPU6500.h"

class Sensors {
    public: 
        Sensors();
        void initialize();
        FlightData readFlightData();

    private: 
        bfs::Mpu6500 imu;
        FlightData data_;
        float readAltitude();
        float computeVerticalVelocity();
        float readAccelZ();
        float readRotatZ();
        float readAccelMagnitude();
};






#endif