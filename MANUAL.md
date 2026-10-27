# Freaq FM (Romix build) — Operation Manual

An 8-bit, two-voice FM synthesizer with a generative two-track sequencer, based on the open-source Meebleeps Freaq FM firmware and adapted to the Romix panel. This manual describes the firmware in this repository. It follows the layout of the Wirehead Instruments Freaq FM manual (v1.7), but only describes what this firmware actually does — see [Differences from the Wirehead Freaq FM](#differences-from-the-wirehead-freaq-fm).

## Contents

- [Quick start](#quick-start)
- [Panel overview](#panel-overview)
- [Display](#display)
- [Voices and sound](#voices-and-sound)
- [Sequencer](#sequencer)
- [Parameter locking](#parameter-locking)
- [Sync](#sync)
- [MIDI output](#midi-output)
- [Reference tables](#reference-tables)
- [Differences from the Wirehead Freaq FM](#differences-from-the-wirehead-freaq-fm)
- [Firmware and hardware notes](#firmware-and-hardware-notes)

---

## Quick start

1. Power the Freaq from 7–12 V DC (centre positive) or the Nano's USB port. The Meebleeps logo appears and fades.
2. Press **START**. A sequence is generated and starts playing at 130 BPM.
3. Turn **MUTATION** to let the sequence evolve; fully anticlockwise freezes it.
4. Turn **SEQ LEN** to set the number of steps (1–16) for the selected voice.
5. Shape the sound with **ATTACK**, **DECAY**, **DEPTH**, **FM RATIO** and **AMP DECAY**.
6. Press **VOICE** to switch the knobs between voice 1 and voice 2.
7. Hold **FUNC** to reach each control's second function (printed after the slash on the panel).

---

## Panel overview

### Buttons

| Button    | Press                              | Hold **FUNC** + press           | LED                                   |
| --------- | ---------------------------------- | ------------------------------- | ------------------------------------- |
| **START** | Start / stop the sequencer         | Tap tempo                       | Lit while the sequencer runs          |
| **SCALE** | Next musical scale                 | Next tonic (A → B → … → G)       | Lit while pressed                     |
| **ALGO**  | Next generative algorithm          | Same as press                   | Lit while pressed                     |
| **VOICE** | Switch between voice 1 and voice 2 | —                               | Lit while voice 2 is selected         |
| **REC**   | Hold + turn knobs: record parameter locks | Hold **FUNC** + **REC** + turn a knob: delete that knob's locks | Lit while recording / deleting |
| **FUNC**  | Hold for the second functions      | —                               | Lit while held                        |

Every button LED also lights while its button is pressed.

### Knobs

| Knob          | Turn                                          | Hold **FUNC** + turn                         |
| ------------- | --------------------------------------------- | -------------------------------------------- |
| **MUTATION**  | How often the sequence changes                | **Density**: how likely each step plays a note |
| **ATTACK**    | Modulation envelope attack *(voice)*          | **Carrier** waveform *(voice)*               |
| **AMP DECAY** | Note length, both voices                      | **Octave** (see [Octave](#octave))           |
| **SEQ LEN**   | Number of steps, 1–16 *(voice)*               | Number of steps for both voices              |
| **DECAY**     | Modulation envelope decay *(voice)*           | **Modulator** waveform *(voice)*             |
| **FM RATIO**  | Modulator-to-carrier frequency ratio *(voice)* | FM ratio **mode** *(voice)*                  |
| **DEPTH**     | Modulation envelope depth *(voice)*           | **LFO** waveform *(voice)*                   |
| **LFO DEPTH** | Amount of LFO on the modulation level *(voice)* | LFO **rate** *(voice)*                     |

*(voice)* = applies to the voice selected with **VOICE**.

Knobs only take effect when they are moved: a setting keeps its value until you turn the knob that controls it. After using a knob's FUNC function, the next turn without FUNC jumps the primary parameter to the knob position.

---

## Display

The 8×8 display normally shows the sequencer state (rows numbered 1–8 from the top, columns 1–8 from the left):

| Row | Shows |
| --- | ----- |
| 1   | Column 8: sync input — lights while a pulse is present on SYNC IN. The rest of the row is not used. |
| 2   | Selected voice: columns 1–4 lit = voice 1, columns 5–8 lit = voice 2 |
| 3   | LFO positions: one moving dot in columns 1–4 for voice 1, one in columns 5–8 for voice 2 (shown once the sequencer has been started) |
| 4   | Not used |
| 5–6 | Voice 1 sequence: steps 1–8 on row 5, steps 9–16 on row 6 |
| 7–8 | Voice 2 sequence: steps 1–8 on row 7, steps 9–16 on row 8 |

In the sequence rows the current step lights when it plays a note, and the last step of the sequence is shown inverted so you can see the sequence length.

When you change a setting the display shows an icon for about a third of a second:

- **Scale / octave offset**: a number (see [Scales](#scales)).
- **Tonic and base octave**: the note letter (A–G) with the octave number next to it, e.g. `A1`.
- **Algorithm**, **waveform** and **FM mode**: an icon (see [Reference tables](#reference-tables)).

---

## Voices and sound

The Freaq has two independent voices. Each is a two-operator FM voice: a **modulator** oscillator modulates the phase of a **carrier** oscillator. Each voice has its own waveforms, FM ratio and mode, modulation envelope and LFO. Press **VOICE** to choose which voice the knobs control (the VOICE LED is lit for voice 2).

### Note length — AMP DECAY

**AMP DECAY** sets how long each note sounds, from a few milliseconds up to about 16 seconds (the first half of the knob covers up to about half a second). It applies to both voices.

### Octave

Hold **FUNC** and turn **AMP DECAY**:

- **Voice 2 selected**: sets the **base octave** (0–6). Both voices follow it. The display shows the tonic and octave, e.g. `A3`.
- **Voice 1 selected**: sets how many octaves (0–3) **voice 1 plays above voice 2** — handy for a bass line on voice 2 and a lead on voice 1. The display shows the number.

### Modulation envelope — ATTACK, DECAY, DEPTH

Each note starts a modulation envelope that controls how much the modulator affects the carrier — in other words, how bright and harsh the note is over time.

- **ATTACK**: time for the modulation to rise.
- **DECAY**: time for the modulation to fall back.
- **DEPTH**: how much modulation the envelope applies.

### FM ratio and mode — FM RATIO

**FM RATIO** sets the modulator frequency relative to the carrier. Hold **FUNC** and turn **FM RATIO** to choose how the knob behaves:

| Mode                         | Icon               | Behaviour |
| ---------------------------- | ------------------ | --------- |
| Quantised multiple (default) | staircase          | Ratio snaps to fixed musical multiples (1/32 … 8×) — harmonic, predictable tones |
| Free multiple, high range    | steep diagonal     | Continuous ratio — clangorous, inharmonic tones |
| Free multiple, low range     | shallow diagonal   | Continuous ratio over a narrower range |
| Unrelated                    | flat line          | Modulator frequency doesn't follow the note — drones and metallic effects |

### Waveforms — FUNC + ATTACK / DECAY / DEPTH

Hold **FUNC** and turn:

- **ATTACK** to choose the **carrier** waveform,
- **DECAY** to choose the **modulator** waveform,
- **DEPTH** to choose the **LFO** waveform.

Available waveforms, in knob order from anticlockwise: **sine, saw, reverse saw, square, noise (pseudo-random), off**. Setting the carrier to *off* silences the voice; setting the modulator to *off* gives the plain carrier waveform.

### LFO — LFO DEPTH

Each voice has an LFO that varies the modulation level.

- **LFO DEPTH**: how much the LFO affects the sound.
- **FUNC + LFO DEPTH**: LFO rate, from very slow to about 10 Hz (about 1 Hz at the centre of the knob).
- **FUNC + DEPTH**: LFO waveform.

The LFO positions are shown on row 3 of the display.

---

## Sequencer

Both voices play from the **same note pattern**, but each voice has its own length (1–16 steps). With different lengths the voices drift against each other (polymetric patterns); with equal lengths they play in unison.

- **START**: start / stop. The first start generates a fresh 16-step pattern.
- **FUNC + START**: tap tempo. Tap in quarter notes (each tap = 4 steps).
- Default tempo: 130 BPM.

### Mutation and density — MUTATION

- **MUTATION**: how often notes in the pattern are replaced. Fully anticlockwise = never (the pattern is frozen); clockwise = more often.
- **FUNC + MUTATION** (density): how likely each step is to play a note rather than a rest.

### Sequence length — SEQ LEN

- **SEQ LEN**: number of steps for the selected voice (1–16).
- **FUNC + SEQ LEN**: sets both voices to the same length.

### Scales

Press **SCALE** to step through the scales. The display shows the scale number:

| No. | Scale |
| --- | ----- |
| 0   | Major (Ionian) |
| 1   | Minor (default) |
| 2   | Pentatonic |
| 3   | Phrygian ("GOA") |
| 4   | Octaves |
| 5   | Octaves + fifths |

### Tonic

Hold **FUNC** and press **SCALE** to step the tonic through the natural notes A → B → C → D → E → F → G. The display shows the note and the base octave. Default: A, octave 1.

### Algorithms — ALGO

Press **ALGO** to choose how the sequencer generates notes. The display shows the algorithm's icon.

| Order | Algorithm | What it does |
| ----- | --------- | ------------ |
| 1 | Standard (default) | Single notes from the current scale across several octaves, with a bias towards the tonic |
| 2 | Arp runs | Like Standard, but inserts short three-note runs up the scale |
| 3 | Drone | One tonic note at the start of the pattern; use long AMP DECAY and the LFO for evolving drones |
| 4 | Scale | Loops through the notes of the current scale, no randomness |

---

## Parameter locking

Parameter locks record knob movements into the sequence, step by step (Elektron style).

- **Record**: hold **REC** and turn a knob while the sequence plays. The value at each step is stored and played back on that step from then on.
- **Delete**: hold **FUNC** + **REC** and turn a knob. All recorded steps for that knob are deleted.

Lockable knobs: **ATTACK**, **AMP DECAY**, **DECAY**, **FM RATIO**, **DEPTH** and **LFO DEPTH** (their primary functions only — knob turns made while FUNC is held are not recorded).

Locks apply to **voice 1 only**. They are recorded over the longer of the two voice sequences, so with voice 1 at 5 steps and voice 2 at 16 steps the automation is 16 steps long. On steps without a lock, the parameter returns to the knob position.

---

## Sync

- **SYNC IN**: each rising 0–5 V pulse advances the sequencer **2 steps** (Korg Volca / Pocket Operator compatible) and re-synchronises the internal clock. The top-right pixel of the display lights with each pulse.
- **SYNC OUT**: a short 5 V pulse every 2 steps. Incoming sync pulses are also passed straight through to SYNC OUT.

---

## MIDI output

The Freaq sends the notes it plays on the **MIDI OUT** jack.

| Item | Value |
| ---- | ----- |
| Voice 1 | MIDI channel **1** |
| Voice 2 | MIDI channel **2** |
| Note numbers | The notes the voices play (standard MIDI note numbers) |
| Velocity | 100 |
| Note off | After the note length set with **AMP DECAY**, or when the next note on that channel starts, whichever comes first |
| Stop | Pressing **START** to stop sends note-offs for any sounding notes |
| Not sent | MIDI clock, start/stop messages, controllers |

The jack is a 3.5 mm TRS socket wired as **TRS type B** (tip = current source, ring = data), as used by Arturia, Novation and Behringer. Devices or adapters that use **type A** (Korg, Make Noise and the MIDI standard) need a type B → type A converter or a crossover cable.

MIDI uses the Nano's serial transmit line, so the MIDI data also appears on the USB serial port at 31250 baud, and the firmware sends no text debug output while MIDI is enabled.

---

## Reference tables

### Waveforms (carrier, modulator, LFO)

| Knob position (FUNC held) | Waveform |
| ------------------------- | -------- |
| 1 (anticlockwise) | Sine |
| 2 | Saw |
| 3 | Reverse saw |
| 4 | Square |
| 5 | Noise (pseudo-random) |
| 6 (clockwise) | Off (flat line icon) |

### Default settings at power-up

| Setting | Default |
| ------- | ------- |
| Tempo | 130 BPM |
| Scale | Minor |
| Tonic / octave | A / 1 |
| Voice 1 octave offset | 0 |
| Algorithm | Standard |
| Waveforms | Sine carrier, sine modulator, sine LFO |
| FM mode | Quantised |
| Knob parameters | Taken from the knob positions as the knobs are read at start-up |

Settings are not saved when the power is switched off.

---

## Differences from the Wirehead Freaq FM

This firmware does **not** have these Wirehead v1.7 features:

- Control-all mode (FUNC + VOICE)
- Voice mix volume (VOICE + AMP DECAY) and voice detune (VOICE + FM RATIO)
- Selectable LFO destinations
- Clock division (FUNC + SEQ LEN — here it sets both sequence lengths instead)
- Global settings at boot (display brightness, sync mode), EEPROM storage
- Patch save / load
- The Call/Response algorithm
- Recording and delete icons for parameter locks
- Parameter locks on voice 2

In return, this build has button LEDs that show status, and MIDI output.

---

## Firmware and hardware notes

- Build and upload with PlatformIO: `pio run -t upload` (close any serial monitor on the port first).
- Display test: `pio run -e displaytest -t upload` walks one lit pixel over every row; flash the synth again afterwards with `pio run -t upload`.
- Options in `src/MutantFMSynthOptions.h`:
  - `ENABLE_MIDI_OUTPUT` (on) — MIDI out; turn off to get text debug output at 115200 baud instead.
  - `DEBUG_SERIAL_UI` (off) — prints every button and knob change; needs MIDI off.
  - `ENABLE_BUTTON_LEDS` (on) — button LED drive.
  - `COMPILE_SMALLER_BINARY` (off) — frees about 2 KB of flash by dropping the noise waveform.
- Pin assignments and wiring notes are in `readme.md`.
