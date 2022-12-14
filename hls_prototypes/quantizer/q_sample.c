

#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "q_sample.h"


void q_sample(
		unsigned int *output_index,
		unsigned long input,
		unsigned long Q_LVL[NB_LVL]) {


	float diff_list[NB_LVL];
	unsigned int output_index_temp=0;

	quantization_loop:for(unsigned int i = 0; i < NB_LVL; i++)
	{
		// this comparison is faster than abs() or pow() for positive difference only

		if(Q_LVL[i] >= input){diff_list[i] = Q_LVL[i] - input;}
		if(Q_LVL[i] < input){diff_list[i] = input - Q_LVL[i];}

		//diff_list[i] = pow((Q_LVL[i] - input), 2);
		//diff_list[i] = abs((Q_LVL[i] - input));

		if(diff_list[i] < diff_list[output_index_temp]){
			output_index_temp = i;
		}
	}
	*output_index = output_index_temp;
}





