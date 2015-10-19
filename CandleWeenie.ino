#include <SoftwareSerial>

SoftwareSerial tinySerial(3,4);

const byte photoresistor = A1;
const byte leds = 1;
const int photoresistor_threshold = 512;

boolean led_state = false;

void setup() {
    pinmode(photoresistor, INPUT);
    pinMode(leds, OUTPUT);
    tinySerial.begin(9600);
}

void loop() {
    if (exceeds(photoresistor_threshold, readPhotoresistorValue())) {
        enableLeds();
    } else {
        disableLeds();
    }
}

int readPhotoresistorValue() {
    return analogRead(photoresistor);
}

boolean getLedState() {
    return led_state;
}

void enableLeds() {
    if (!getLedState()) {
        setLedState(HIGH, true, "LEDs enabled");        
    }
}

void disableLeds() {
    if (getLedState()) {
        setLedState(LOW, false, "LEDs disabled");        
    }
}

void setLedState(byte value, byte state, String message) {
    digitalWrite(leds, value);
    led_state = state;
    tinySerial.println(message);
}

boolean exceeds(int threshold, int level) {
    return level < threshold;
}