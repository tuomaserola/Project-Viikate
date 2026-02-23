#include "Sensors.h"
 
Sensors::Sensors() : imu(&Wire, bfs::Mpu6500::I2C_ADDR_PRIM) {
    data_.altitude = 0.0;
    data_.verticalVelocity = 0.0;
    data_.accelZ = 0.0;
    data_.accelMagnitude = 0.0;
    data_.timeMs = 0.0;
    data_.rbfRemoved = false;
}

FlightData Sensors::readFlightData() {
    
    imu.Read(); 
    data_.altitude         = readAltitude();
    data_.verticalVelocity = computeVerticalVelocity();
    data_.accelZ           = readAccelZ();
    data_.rotatZ           = readRotatZ();
    data_.accelMagnitude   = readAccelMagnitude();
    data_.timeMs           = millis();
    data_.rbfRemoved       = digitalRead(Constants::RBF_PIN);

    return data_;
}

void Sensors::initialize() {
    Wire.begin(); // Begin I2C transmission
    if (!imu.Begin()) {
        //Serial.print("FAIL");
       // TODO: Logger -> IMU FAILURE;
    }
}

float Sensors::readAltitude() {
    return 1.11;
}

float Sensors::computeVerticalVelocity() {
    return 2.22;
}

float Sensors::readAccelZ() {
    return imu.accel_z_mps2() + Constants::GRAVITY; // Remove gravity
}

float Sensors::readRotatZ() {
    return imu.gyro_z_radps();

}

float Sensors::readAccelMagnitude() {
    return 4.44;
}

















