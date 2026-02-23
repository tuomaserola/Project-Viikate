#ifndef FLIGHTDATA
#define FLIGHTDATA

/**
 * @brief Flight data passed into the state machine.
 *
 * This struct is populated by the main loop using filters
 * and hardware inputs. The StateMachine doesn't talk
 * directly to sensors.
 *
 */
struct FlightData {
    float altitude;          // [m] Altitude (baro)
    float verticalVelocity;  // [m/s] Positive up
    float accelZ;            // [m/s^2] Acceleration along vertical axis (gravity removed)
    float rotatZ;            // [Rad/s] Rotation around the z axis
    float accelMagnitude;    // [m/s^2] Total acceleration magnitude
    unsigned long timeMs;    // [ms] System time since boot
    bool rbfRemoved;         // True if remove-before-flight pin is removed
};

#endif