/*----------------------------------------------------------------------------------------------------------
 * avMidi.h
 * 
 * MIDI-out support on the TX pin (D1)
 * 
 * Enable with ENABLE_MIDI_OUTPUT in MutantFMSynthOptions.h - all text output on the serial port 
 * is compiled out when it is enabled, as it would corrupt the MIDI stream
 * 
 * Assumes serial port is already set up at MIDI_BAUD_RATE
 * 
 * Source Code Repository:  https://github.com/Meebleeps/MeeBleeps-Freaq-FM-Synth
 * Youtube Channel:         https://www.youtube.com/channel/UC4I1ExnOpH_GjNtm7ZdWeWA
 * 
 * (C) 2021-2022 Meebleeps
*-----------------------------------------------------------------------------------------------------------
*/

#ifndef AVMIDI_H
#define AVMIDI_H

#include <Arduino.h>

// ENABLE_MIDI_OUTPUT is set in MutantFMSynthOptions.h
#include "MutantFMSynthOptions.h"

#define MIDI_BAUD_RATE  31250
#define MIDI_NOTE_OFF   0x80
#define MIDI_NOTE_ON    0x90
#define MIDI_VELOCITY   100

// sends a 3-byte MIDI channel message.  channel is 0-15 (MIDI channels 1-16)
inline void midiSend(uint8_t status, uint8_t channel, uint8_t data1, uint8_t data2) 
{  
  Serial.write(status | channel);
  Serial.write(data1);
  Serial.write(data2);
}

#endif
