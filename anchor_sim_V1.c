#include <stdio.h>
#include <math.h>
#define epsilon 5.00

/*
Early-stage simulation of anchor-based logic for the IVSA project.

This version models deterministic slice sliding using hardcoded numerical values
without external DSP libraries. The program prints values before and after 
checkSlice() to verify whether the algorithm matches the intended design.

v0.2 
Aim: add pitch array, proportion sanity check, user inputs, temporal offset computation
*/ 

struct midi_fnote {
	double pitch;
	double duration;
	double start_time;
};

struct audioSlice {
	double pitch[5];
	double duration;
	double start_time;
	int pitchCount;
};

struct audioTrack{
	double duration;
	double anchor;
	double pitch[15];
};

int checkSlice(struct midi_fnote *n, struct audioSlice *s, struct audioTrack *t){
	if(s->start_time < t->duration){
       int length = sizeof(s->pitch) / sizeof(s->pitch[0]);
		int matches = 0;
		for(int i = 0; i < length; i++){
			if(fabs((n->pitch - s->pitch[i])) < epsilon || n->pitch == s->pitch[i]) {
				matches++;
			}
		}

		if (matches > 2){
			t->anchor = s->start_time - n->start_time;
            return 1;
		} else {
			if(s->pitchCount < 15){
				s->start_time += s->duration;
                int base = s->pitchCount;
				for (int i = 0; i < length; i++){
					s->pitch[i] = t->pitch[base + i];
				}
                s->pitchCount+=5;
				return checkSlice(n,s,t);
			} else {
				return 0;
			}	
		}
	}
	return 0;
}

int main(void){
	struct midi_fnote m1;
	struct audioSlice s1;
	struct audioTrack t1;

	struct midi_fnote *n = &m1;
	struct audioSlice *s = &s1;
	struct audioTrack *t = &t1;
	
	printf("Enter duration of audio track: ");
	scanf("%lf", &t1.duration);

	printf("Enter 15 pitches for your track: ");
	for (int i = 0; i < 15; i++)
	{
		scanf("%lf", &t1.pitch[i]);
	}
	
	printf("Enter duration, pitch and start time of MIDI first note: ");
	scanf("%lf %lf %lf", &m1.duration, &m1.pitch, &m1.start_time);
	
	printf("Initial values of audioTrack (t1): Duration: %fs, Pitches: ", t1.duration);
	for(int i = 0; i < 15; i++){
		printf("%fHz ", t1.pitch[i]);
	}
	printf("\nInitial Values of midi_fnote (m1): Duration: %fs, Time: %fs, Pitch: %fHz", m1.duration, m1.start_time, m1.pitch);
	
	s1.pitchCount = 5;
	s1.duration = m1.duration;
	printf("\nInitial Values of audioSlice (s1): Duration: %fs, Time: %fs, Pitch: ", s1.duration, s1.start_time);
	
    for(int i = 0; i < 5; i++){
		s1.pitch[i] = t1.pitch[i];
        printf("%fHz ", s1.pitch[i]);
	}
	printf("\n");
	
	if(checkSlice(n,s,t) == 1){
		printf("Match");
	} else{
		printf("No Match");
	}

	printf("\nFinal Values of midi_fnote (m1): Duration: %fs, Time: %fs, Pitch: %fHz\n", m1.duration, m1.start_time, m1.pitch);
	
	printf("Final Values of audioTrack (t1): Duration: %fs, Anchor Time: %fs, Pitch: ", t1.duration, t1.anchor);
	for(int i = 0; i < 15; i++){
		printf("%fHz ", t1.pitch[i]);
	}

	printf("\nFinal Values of audioSlice (s1): Duration: %fs, Time: %fs, pitchCount: %d, Pitch: ", s1.duration, s1.start_time, s1.pitchCount);
	for(int i = 0; i < 5; i++){
		printf("%fHz ", s1.pitch[i]);
	}
	printf("\n");
    
	return 0;
}
