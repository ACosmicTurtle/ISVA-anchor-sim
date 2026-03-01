#include <stdio.h>
#include <math.h>
#define TIME_WINDOW 10.0

/*
Early-stage simulation of anchor-based logic for the IVSA project.

This version models deterministic slice sliding using hardcoded numerical values
without external DSP libraries. The program prints values before and after 
checkSlice() to verify whether the algorithm matches the intended design.
*/ 

struct midi_fnote {
	double pitch;
	double duration;
	double start_time;
};

struct audioSlice {
	double pitch;
	double duration;
	double start_time;
};

int checkSlice (struct midi_fnote *n, struct audioSlice *s){

	while (s->start_time < TIME_WINDOW) {
		if(fabs(n->pitch - s->pitch) < 1.0) {
			return 1; //True
		} else {
			s->start_time += s->duration; //Deterministic and rigid audio sliding
		}
	}
	
	return 0; //False
}

int main(void){
	struct midi_fnote m1 = {2.4, 3.3, 1.2};
	struct audioSlice s1 = {5.7, m1.duration, 0};
	
	struct midi_fnote *n = &m1;
	struct audioSlice *s = &s1;

	printf("Initial Values of m1: Pitch: %f Hz, Duration: %f s, Time: %f s\n", m1.pitch, m1.duration, m1.start_time);
        printf("Initial Values of s1: Pitch: %f Hz, Duration: %f s, Time: %f s\n", s1.pitch, s1.duration, s1.start_time);


	if (checkSlice(n,s) == 1) {
		printf("Match");
	} else {
		printf("No match");
	}
	
	printf("\n");

        printf("Final Values of m1: Pitch: %f Hz, Duration: %f s, Time: %f s\n", m1.pitch, m1.duration, m1.start_time); //Should stay constant
        printf("Final Values of s1: Pitch: %f Hz, Duration: %f s, Time: %f s\n", s1.pitch, s1.duration, s1.start_time); //Subject to change

	return 0;
} 
