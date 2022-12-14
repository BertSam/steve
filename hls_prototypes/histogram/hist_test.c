/*
 * MIT License
 *
 * Copyright (c) 2022 SLAC National Accelerator Laboratory
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Authors : Berthié Gouin-Ferland
 * Last update : 12-13-2022
 *
 * Description : This file is used to test the histogram on an x86 platform
 */

#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "hist.h"



int main() {

  const unsigned int	SAMPLES=1000;
  unsigned int Q_in_samples[SAMPLES], hist_out[NB_LVL];
  unsigned int QZD_out_index;


  FILE	*in_file;
  FILE	*out_file;

  for(unsigned int i = 0; i < NB_LVL; i++) // init loop
  {
	  hist_out[i] = 0;
  }


  in_file=fopen("./q_ref.dat","r");
  memset(Q_in_samples, 0, sizeof(Q_in_samples));

  unsigned int count=0;
  while(!feof(in_file) && count<SAMPLES){
	  fscanf(in_file, "%u", &(Q_in_samples[count++]));
  }
  fclose(in_file);

  // Making the histogram
  out_file=fopen("./hist_out.dat","w");
  for (i=0; i<SAMPLES; i++) {
	  hist(&hist_out[Q_in_samples[i]]);
  }
  for(i = 0; i < NB_LVL; i++) // writing loop
  {
	  fprintf(out_file,"%u\n", hist_out[i]);
  }
  fclose(out_file);

  printf ("Comparing against output data \n");
  if (system("diff -w hist_out.dat cpp_hist_ref.dat")) {

  	fprintf(stdout, "*******************************************\n");
  	fprintf(stdout, "FAIL: Output DOES NOT match the ref output\n");
  	fprintf(stdout, "*******************************************\n");
    return 0;
  } else {
  	fprintf(stdout, "*******************************************\n");
  	fprintf(stdout, "PASS: The output matches the ref output!\n");
  	fprintf(stdout, "*******************************************\n");
     return 0;
  }
  return 1;
}

