# ISVA-anchor-sim

ISVA Anchor Simulation (v0.2)

This repository contains an early prototype of anchoring logic for ISVA (Instrument-Synthesiser Video Automation)

v0.2 simulates pitch proximity matching between a MIDI first note and segments of an audio track. A temporal anchor offset is computed when sufficient pitch matches are detected within a fixed tolerance range.

Structs Overview
- midi_fnote – represents a single MIDI note
- audioSlice – represents a fixed-size segment of track pitches
- audioTrack – represents the full track and computed anchor

Current Implementation (v0.2)
- Takes user inputs
- Multiple pitches per slice and track (Array-based representation) 
- Each valid proximity check within fixed epsilon increments a match
- Slice considered valid when more than 2 pitch values fall within epsilon tolerance of the MIDI pitch
- Anchor time is derived from the temporal relationship between the matching slice start time and the MIDI note start time.
- Simulates slice advances deterministically along a track for insufficient matches

Algorithm Flow
- Initialise first slice from track pitch array
- Compare MIDI pitch against slice pitches
- If match threshold not met, advance slice
- If threshold met, compute anchor offset
- Terminate when track is exhausted or match is found


Limitations
- Fixed-sized arrays
- Single-note MIDI matching
- Manual input only
- Static epsilon macro
- Recursive implementation
- Track duration is only used a replacement for TIME_WINDOW macro from v0.1

Future Improvements
- Dynamic allocation for arbitrary track length
- Multiple MIDI note support
- Deterministic test harness
- Adjustable tolerance neighbourhood
- Iterative implementation
- Better anchor formalisation
