# ISVA-anchor-sim

ISVA Anchor Simulation (v0.1)

This repository contains an early prototype of anchoring logic for ISVA (Instrument-Synthesiser Video Automation)

The objective is to detect the first approximate pitch match between a MIDI sequence’s initial note and segments of an audio track. Once detected, a deterministic temporal offset can be computed to synchronise the MIDI and audio timelines.

Current Implementation (v0.1)
- Simulates audio using fixed-duration slices
- Compares a single pitch per slice against a MIDI pitch
- Proximity check within specified tolerance
- Advances slices deterministically until a match is found or a time bound is reached
- Does not use any external DSP libraries to validate core logic independently

Limitations
- Only one pitch per audio slice evaluated 
- Fixed duration on slices
- No secondary validation to reduce false positives

Planned Improvements (v0.2)
- Multiple pitches per slice (array-based representation)
- Adjustable tolerance neighbourhood
- Proportional validation checks to reduce false positives
- Explicit temporal offset computation for synchronised sequencing 
