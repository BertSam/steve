
//#include <iostream>
#include <string.h>
#include <math.h>
#include <stdio.h>

#ifndef Q_SAMPLE_
#define Q_SAMPLE_
#define NB_LVL 32 // Now Hardcoded but has to be adapted with a class, a constructor and a config file (MAX = 2^5)


void q_sample(
		unsigned int *output_index,
		unsigned long input,
		unsigned long Q_LVL[NB_LVL]);

#endif


// For debug
/*void q_sample(
//		unsigned int *output_index,
//		float *output,	//output=Q(input)
//		float input,
		float Q_LVL[NB_LVL]);*/
