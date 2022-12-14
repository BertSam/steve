# steve
Various tools and tutorials for nonuniform quantization and neural networks applied to TOF spectroscopy. 

## Installation

Use the package manager [pip](https://pip.pypa.io/en/stable/) and [venv](https://docs.python.org/3/library/venv.html) to setup your virtual environments.

```bash
python3 -m venv /path/to/new/virtual/environment
python3 pip install -r requirements.txt
```

## Description 

The notebooks contain use cases for data processing using nonuniform quantization, but also to play with data representation for better fpga implementation.

The "hls_prototypes" folder contains vitis HLS project with working examples for quantizing a stream of data with a pre-trained quantizer. "q_sample_test.c" shows how to load the pre-trained quantizer and how to use it. "hist_test.c" shows how to make the histogram with known quantized data. Because the data are quantized, there's no "bins". The histogram only increments by 1 the count of the corresponding quantized value when receiving it. Note that the quantizer and histogram c code only work as a "stream" at the moment. Metadata, such as "channel, "adresses" and "nedge" are needed to make the histogram. The data for testing the c code are generated using the "Sample_maker_for_hls_fpga_code_prototypes.ipynb" notebook.