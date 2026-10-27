#ifndef MUTANTFMSYNTHOPTION_H
#define MUTANTFMSYNTHOPTION_H


// 09 May 2022
// added compile options for normally-open or normally-closed switches

//  if your switches are NORMALLY OPEN, include this line and comment out the #define below
//  the Romix panel switches are normally open and short the pin to GND when pressed
#undef SWITCH_TYPE_NORMALLY_CLOSED

//  if your switches are NORMALLY CLOSED, include this line and comment out the #undef above
//#define SWITCH_TYPE_NORMALLY_CLOSED




// Romix panel: each button LED (+5V -> 470R -> LED) has its cathode on the button's own pin.
// The pin acts as an open-collector output: driven LOW lights the LED, INPUT_PULLUP leaves it off
// and lets the switch be read.  The pins are never driven HIGH, so a pressed switch can't short an output.
// Harmless if the LED cathodes are still wired to GND (the LEDs are then simply always on).
// comment out to leave the button pins as plain inputs
#define ENABLE_BUTTON_LEDS




// MIDI output on the TX pin (D1) / MIDI out jack (TRS type B), 31250 baud.
// voice 1 plays on MIDI channel 1, voice 2 on MIDI channel 2.
// Removes all text output from the serial port (it shares the TX pin), which also frees the flash used by it.
// comment out (or build with -DDISABLE_MIDI_OUTPUT) to get the debug text output back at 115200 baud
#ifndef DISABLE_MIDI_OUTPUT
#define ENABLE_MIDI_OUTPUT
#endif




// print button and knob changes to the serial port (115200 baud) - handy for checking the panel wiring
// off by default: it costs flash and CPU time.  Not available with ENABLE_MIDI_OUTPUT
//#define DEBUG_SERIAL_UI

#ifdef ENABLE_MIDI_OUTPUT
#undef DEBUG_SERIAL_UI
#endif




// 09 May 2022
// added compile options to reduce compiled image size to fit into boards with larger bootloaders, or using different compilers such as Arduino IDE
// uncomment the below to reduce the image size by 2KB

//#define COMPILE_SMALLER_BINARY




#endif


