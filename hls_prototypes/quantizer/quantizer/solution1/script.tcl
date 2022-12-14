############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
############################################################
open_project quantizer
set_top q_sample
add_files q_sample.c
add_files -tb ../q_lvls.dat
add_files -tb ../q_ref.dat
add_files -tb q_sample_test.c
add_files -tb ../raw.dat
open_solution "solution1" -flow_target vivado
set_part {xczu9eg-ffvb1156-2-e}
create_clock -period 10 -name default
#source "./quantizer/solution1/directives.tcl"
csim_design -clean
csynth_design
cosim_design
export_design -format ip_catalog
