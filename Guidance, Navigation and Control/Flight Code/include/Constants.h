#ifndef CONSTANTS
#define CONSTANTS

// All constants are defined here 
namespace Constants {
    // Physics
    static constexpr float GRAVITY = 9.81f;

    // Pins
    static constexpr int RBF_PIN = 2;
    static constexpr int CS_PIN = 10;
    static constexpr int SERVO1_PIN = 0;
    static constexpr int SERVO2_PIN = 0;
    static constexpr int SERVO3_PIN = 0;
    static constexpr int SERVO4_PIN = 0;

    // PID parameters
    static constexpr float PROPORTIONAL = 0;
    static constexpr float INTEGRATOR = 0;
    static constexpr float DERIVATIVE = 0;
}


#endif