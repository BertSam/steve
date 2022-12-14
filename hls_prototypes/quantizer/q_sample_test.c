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
 * Description : This file is used to test the quantizer on an x86 platform
 */

#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "q_sample.h"





int main() {

  const unsigned int SAMPLES=1000;
  unsigned long qlvls[NB_LVL], RAW_in_samples[SAMPLES];
  unsigned int QZD_out_index;

  FILE	*in_file;
  FILE	*out_file;
  FILE	*config_file;

  config_file=fopen("./q_lvls.dat","r");
  memset(qlvls, 0, sizeof(qlvls));

  unsigned int count=0;
  while(!feof(config_file) && count<NB_LVL){
	  fscanf(config_file, "%lu", &(qlvls[count++]));
  }
  fclose(config_file);

  in_file=fopen("./raw.dat","r");
  memset(RAW_in_samples, 0, sizeof(RAW_in_samples));

  count=0;
  while(!feof(in_file) && count<SAMPLES){
	  fscanf(in_file, "%lu", &(RAW_in_samples[count++]));
  }
  fclose(in_file);

  out_file=fopen("./q_out.dat","w");
  for (unsigned int i=0; i<SAMPLES; i++) {
	q_sample(&QZD_out_index, RAW_in_samples[i], qlvls); // Execute the function with latest input
	fprintf(out_file,"%u\n", QZD_out_index);
  }
  fclose(out_file);

  printf ("Comparing against output data \n");
  if (system("diff -w q_out.dat q_ref.dat")) {

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

