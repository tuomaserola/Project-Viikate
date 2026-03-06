#include <Arduino.h>

// Using a Teensy core utility class (from cores/teensy4)
elapsedMillis blink_timer;

// Called automatically after startup (Arduino-like entry)
void setup() {
  // Initialize LED pin
  pinMode(LED_BUILTIN, OUTPUT);

  // Initialize serial comms (USB CDC, since we use -DUSB_SERIAL)
  Serial.begin(9600);
  while (!Serial && millis() < 2000) {
    // Wait up to 2s for Serial connection
  }

  Serial.println("Teensy 4.1 core link test starting...");
}

// Main loop
void loop() {
  if (blink_timer > 500) {
    // Toggle LED every 500 ms
    static bool state = false;
    digitalWrite(LED_BUILTIN, state ? HIGH : LOW);
    state = !state;

    Serial.print("Millis = ");
    Serial.println(millis());

    blink_timer = 0; // reset timer
  }
}

// The Teensy startup code normally calls setup() and loop()
// from within main(), but if you’re bypassing startup.c linkage,
// you can provide your own main() for testing:
