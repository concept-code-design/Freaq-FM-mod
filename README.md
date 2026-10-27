# An interpretation of the Meebleeps / Wirehead Freaq FM Synth
## Arduino Synth with Dual-voice 2-OP FM | Generative 2-track Polymetric Sequencer | Mozzi SDK

## NOTE This code is an open-source prototype and is not compatible with the Wirehead Instruments version of Freaq FM hardware
- Meebleeps was rebranded as Wirehead Instruments in 2023 to avoid brand confusion with MeeBlip - another completely separate synth design company.

This interpretation is based on https://github.com/Meebleeps/MeeBleeps-Freaq-FM-Synth

It uses a different PCB with slightly different layout. It features dual independent 2-operator FM voices paired with a 2-track generative sequencer.  

Each voice has independent carrier & modulator waveforms, FM ratio, modulation envelope & LFO.

Both tracks share the a single pattern (inspired by the Intellijel Metropolix) and can be stacked in unison or have different polymetric step-counts.  Track 1 can be offset 0-3 octaves above track 2 for separate bass & lead.

The code was addressed by Claude to match my hardware. It now also includes working MIDI out.


 #### Source Code:      https://github.com/Meebleeps/MeeBleeps-Freaq-FM-Synth
 #### Youtube Demo:     https://www.youtube.com/watch?v=KD6IrcmMkoA
 #### Youtube Channel:  https://www.youtube.com/channel/UC4I1ExnOpH_GjNtm7ZdWeWA

Source released under Creative Commons Attribution-NonCommercial-ShareAlike 4.0
Copyright (C) 2026 Concept & Code

***

## Important build-notes 

- My pcb has normally-open switches
- Work and Compile PlatformIO (I use VSCodium)). 

***

## Voices

-   2 independent FM voices
-   2-operator FM (for old-school prince of persia vibes! 😂)
-   Multi-mode FM ratios - quantised, free-multiple, independent
-   Multiple operator waveforms for carrier & modulator - Sine, Saw, Reverse Saw, Square, Noise, Off
-   Modulation level controlled by Attack/Decay envelope and LFO per-voice
-   Multiple LFO waveforms (same tables as the carrier oscillators) Sine, Saw, Reverse Saw, Square, Noise

## Sequencer

-   2/1.5 track polymetric sequencer with up to 16 steps per track (Both tracks use same note sequence but can have different step-counts for polymetric phasing)
-   Multiple generative algorithms - (semi)random notes, (semi)random runs, arpeggio, drone 
-   Sequence mutates/evolves at user-defined rate & note-density
-   Selectable tonic, octave & scale quantisation (Major, Minor, Pentatonic, Phrygian (GOA!), Octaves, Fifths)
-   Tap-tempo control
-   Sync input & output (Korg Volca compatible) 
-   16-step parameter-lock recording of synth parameters for track 1 (the Elektron way!)

## Hardware 
-   Arduino Nano (Elegoo) 
-   8x8 LED display with a MAX7219-based control board
-   Simple Mozzi output circuit 
-   Added power filtering caps on DC input and 5V rail
-   Designed to fit into Volca form factor 
-   Laser-cut metalisized acrylic faceplate 
-   Laser-cut wooden enclosure 
-   7V-12DC DC Power input 
-   Access to nano's USB port for firmware upgrades 

## Pins

These are the defaults in the original software:

| Pin | Function   | Name in `MutantFMSynth.ino` |
| --- | ---------- | --------------------------- |
| A0  | Mutation   | ANALOG_INPUT_MUTATION       |
| A1  | Wobble     | ANALOG_INPUT_LFO            |
| A2  | Population | ANALOG_INPUT_STEPCOUNT      |
| A3  | Attack     | ANALOG_INPUT_MOD_ENVELOPE2  |
| A4  | Lifespan   | ANALOG_INPUT_DECAY          |
| A5  | Decay      | ANALOG_INPUT_MOD_ENVELOPE1  |
| A6  | Ratio      | ANALOG_INPUT_MOD_RATIO      |
| A7  | Depth      | ANALOG_INPUT_MOD_AMOUNT     |
| D3  | Start      | BUTTON_INPUT_START          |
| D4  | Voice      | BUTTON_INPUT_VOICE          |
| D5  | Rec        | BUTTON_INPUT_REC            |
| D6  | Scales     | BUTTON_INPUT_SCALE          |
| D10 | Func       | BUTTON_INPUT_FUNC           |
| D12 | Tonic      | BUTTON_INPUT_TONIC          |

My hardware version (Romix panel)

The firmware in `src/` is configured for this panel. Knob functions are `primary / [FUNC] held`.

| Pin | Panel label            | Name in `MutantFMSynth.ino`  |
| --- | ---------------------- | ---------------------------- |
| A0  | MUTATION / density     | ANALOG_INPUT_MUTATION        |
| A1  | ATTACK / carrier       | ANALOG_INPUT_MOD_ENVELOPE2   |
| A2  | AMP DECAY / octave     | ANALOG_INPUT_DECAY           |
| A3  | SEQ LENGTH             | ANALOG_INPUT_STEPCOUNT       |
| A4  | DECAY / mod            | ANALOG_INPUT_MOD_ENVELOPE1   |
| A5  | FM RATIO / mode        | ANALOG_INPUT_MOD_RATIO       |
| A6  | DEPTH / lfo            | ANALOG_INPUT_MOD_AMOUNT      |
| A7  | LFO DEPTH / lfo rate   | ANALOG_INPUT_LFO             |
| D12 | Start                  | BUTTON_INPUT_START           |
| D5  | Voice                  | BUTTON_INPUT_VOICE           |
| D4  | Rec                    | BUTTON_INPUT_REC             |
| D10 | Scale                  | BUTTON_INPUT_SCALE           |
| D3  | Func                   | BUTTON_INPUT_FUNC            |
| D6  | Algo                   | BUTTON_INPUT_ALGO            |

Hardware notes:

- The switches are normally open and short their pin to GND (`SWITCH_TYPE_NORMALLY_CLOSED` is off in `MutantFMSynthOptions.h`).
- D10 (Scale) and D12 (Start) are the ATmega328's hardware SPI SS and MISO pins. With the SPI enabled, a Scale press drops it into slave mode and the Start LED can't be driven, so the display is driven by bit-banged SPI on D11 (data), D13 (clock) and D7 (CS) instead (`LedMatrix.cpp`).
- Display test: `pio run -e displaytest -t upload` walks a single pixel along rows 1–8, left to right. Flash the synth again with `pio run -t upload`.
- Button LEDs (`ENABLE_BUTTON_LEDS`): every Nano pin is in use, so each LED shares its button's pin. Wire the LED as +5V → 470Ω → LED → button pin (instead of → GND). The firmware lights an LED by pulling the pin low and turns it off by making the pin an input with pull-up (open-collector style, never driven high), briefly releasing all LEDs (for 100µs) every ~55ms to read the switches. A pressed switch always lights its own LED.
  - FUNC: lit while held
  - REC: lit while recording / clearing parameter locks
  - START: lit while the sequencer runs
  - VOICE: lit while voice 2 is selected
  - SCALE, ALGO: lit only while pressed
- MIDI out (`ENABLE_MIDI_OUTPUT`, on by default): notes for voice 1 on channel 1 and voice 2 on channel 2, on TX (D1) at 31250 baud to the TRS type B jack. All text output on the serial port is compiled out while it is enabled.
- `DEBUG_SERIAL_UI` in `MutantFMSynthOptions.h` prints every button and knob change at 115200 baud, for checking the wiring (only with MIDI off).
- Operation manual: [MANUAL.md](MANUAL.md).

## User Guide (Romix panel)

### Buttons

| Button | Press                               | [FUNC] + press                 |
| ------ | ----------------------------------- | ------------------------------ |
| START  | Start / stop the sequencer          | Tap tempo                      |
| SCALE  | Next scale                          | Next tonic (A–G)               |
| ALGO   | Next generative algorithm           | –                              |
| VOICE  | Select voice 1 / voice 2            | –                              |
| REC    | Hold while turning a knob to record it into the sequence (parameter lock) | Hold [FUNC][REC] while turning a knob to delete that knob's recorded locks |
| FUNC   | Hold to access the alternative functions | |

### Knobs

| Knob      | Turn                                         | [FUNC] + turn                                   |
| --------- | -------------------------------------------- | ----------------------------------------------- |
| MUTATION  | How often the sequence changes               | Density – how likely a step plays a note        |
| ATTACK    | Mod envelope attack (current voice)          | Carrier waveform (current voice)                |
| AMP DECAY | Note length (both voices)                    | Octave – voice 2 selected: base octave 0–6 (both voices follow); voice 1 selected: voice 1 plays 0–3 octaves above voice 2 |
| SEQ LEN   | Steps (1–16) for the current voice           | Steps for both voices                           |
| DECAY     | Mod envelope decay (current voice)           | Modulator waveform (current voice)              |
| FM RATIO  | FM ratio (current voice)                     | FM ratio mode (current voice)                   |
| DEPTH     | Mod envelope depth (current voice)           | LFO waveform (current voice)                    |
| LFO DEPTH | LFO depth (current voice)                    | LFO rate (current voice)                        |

Parameter locks can be recorded for ATTACK, AMP DECAY, DECAY, FM RATIO, DEPTH and LFO DEPTH and apply to voice 1.

Functions from the Wirehead v1.7 manual that this firmware does not have: control-all voice mode, voice mix / detune, LFO destinations, clock division, global settings, patch save/load and the call/response and scale algorithms.

### Original panel guide

#### Buttons

-   Tonic - Select tonic through natural notes A - G
    -   [Func] + Scale - Shift base octave from 0 - 5
    -   [Func][Rec] + Scale - Select octave offset to Track 1 (track 1 & 2 can be 0-4 octaves apart)
-   Scales - Select current musical scale
    -   [Func] + Algo - Select current generative algorithm
    -   [Func][Rec] + Algo - Select the LFO waveform for the current voice 
-   Rec + knob - Hold down while moving a knob to record those parameters to the sequence 
    -   [Rec] + knob - Hold down while moving a knob to delete the recorded sequence for that parameter 
    -   [Func] + buttons - Access various secondary functions
-   Start - Start or stop the sequencer
    -   [Func] + Start - Tap tempo
    -   [Func][Rec] + Start - Select the MODULATOR waveform for the current voice 
-   Voice - Select the active track which can be edited using the parameter inputs
    -   [Func] + Voice - Select the FM ratio mode for the current voice
    -   [Func][Rec] + Voice - Select CARRIER Waveform for the current voice 

#### Rotary Inputs

-   Mutation - Adjust the likelihood that the sequence will change over time
    -   [Func] + Mutation - Adjust the liklihood that any given step will be a note or a rest
-   Population - Adjust the number of steps for the active track
    -   [Func] + Population - Adjust the number of steps for all tracks
-   Lifespan - Adjust the length of the notes (for all tracks)
-   Ratio - Select the carrier--to-modulator FM ratio (based on the current FM mode)
-   Wobble - Adjust the amount of LFO to apply to the modulator level for the active track
    -   [Func] + Wobble - Adjust the LFO rate for the active track
-   Attack - Adjust the attack time for the modulator level envelope
-   Decay - Adjust the decay time for the modulator level envelope
-   Depth - Adjust the amount of envelope to apply to the modulator level for the active track

## Issues / Limitations

-   Fair bit of jitter in the sequencer timing when tracking external sync due to somewhat naive approach to the 2-step-per-pulse volca sync 
-   Mozzi audio library has 10ms buffer 
-   The code is written for NORMALLY CLOSED switches - see latest updates in MutantFMSynth.ino updateButtonControls() for support for NORMALLY OPEN
-   The code may not fit in the Arduino Nano when compiled using the Arduino IDE or using different bootloaders

### Compiling on the Arduino IDE

If you have issues with the compiled size not fitting in the Nano, this may be due to different compiler (I use VSCode & PlatformIO) or different bootloader in the Arduino (not sure which I have, but am compiling to Elegoo brand arduino nano). 
- Check the compiler options in **MutantFMSynthOptions.h** to alter switch type or compile size
- open the file MutantFMSynthOptions.h
- find the line: //#define COMPILE_SMALLER_BINARY
- uncomment the line so it looks like this:  #define COMPILE_SMALLER_BINARY
- Then compile. It should now easily fit into the Nano.  This omits the semi-random wave tablesbut you probably won't miss it! :)

### Compiling in VSCode / PlatformIO

- Do not install the Mozzi library from PlatformIO in VSCode, it's outdated and will not build successfully. Instead, install its [latest git master branch](https://github.com/sensorium/Mozzi) to `lib/mozzi`. 
- The default settings target the Nano ATmega328 with the new bootloader. If you have avrdude errors during upload, you might have the old bootloader: change both instances of `nanoatmega328new` to `nanoatmega328` in `plaformio.ini`.


## Thanks

-   Inspired by Hagiwo's modular builds: https://www.youtube.com/channel/UCxErrnnVNEAAXPZvQFwobQw 
-   Mozzi audio library: https://sensorium.github.io/Mozzi/ 
-   Inkscape for vector graphics: https://inkscape.org/ 
-   Laser-cutting by Perth Creative Industries https://www.pcilasercutting.com.au/
-   Fritzing for circuit design: https://fritzing.org/ 
-   Great Scott for electronics tips! https://www.youtube.com/channel/UC6mIxFTvXkWQVEHPsEdflzQ

