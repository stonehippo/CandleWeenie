/*
 CandleWeenie is a little LED pumpkin light. It's got a photoresistor so that it can figure out
 when it's dark enough to turn on its cluster of candle flicker LEDs.

 This is, of course, overkill. The circuit could be built without a microcontroller at all.
 But what's the point of that? ;-)

 Also, this could be done with less code. I added several methods to make the code more readable,
 but really, but it could easily be optimized. Given how little it does, there's not much point.

 CandleWeenie is based on a ATTiny85, though this code should work fine with just about any
 microcotroller that works with the Arduino IDE. For example, porting over to an Arduino Uno
 doesn't really require any changes at all (though you'd probably want to switch over to hardware
 serial, and assign a different pin to the LED control).
*/

#include <SoftwareSerial.h>

SoftwareSerial tinySerial(3,4);

const byte photoresistor = A1;
const byte leds = 1;
const int photoresistor_threshold = 512;

boolean led_state = false;

void setup() {
    pinMode(photoresistor, INPUT);
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
