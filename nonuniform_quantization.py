#  * MIT License
#  *
#  * Copyright (c) 2022 SLAC National Accelerator Laboratory
#  *
#  * Permission is hereby granted, free of charge, to any person obtaining a copy
#  * of this software and associated documentation files (the "Software"), to deal
#  * in the Software without restriction, including without limitation the rights
#  * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#  * copies of the Software, and to permit persons to whom the Software is
#  * furnished to do so, subject to the following conditions:
#  *
#  * The above copyright notice and this permission notice shall be included in all
#  * copies or substantial portions of the Software.
#  *
#  * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#  * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#  * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#  * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#  * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#  * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#  * SOFTWARE.
#  *
#  * Authors : Berthié Gouin-Ferland
#  * Last update : 2022-12-06
#  *
#  * Description : This notebook describes the quantization method.



import numpy as np
from sklearn.metrics import mean_squared_error
import h5py

import generalized_lloyd_LBG


class quantizer():
    
    def __init__(self, Nb_bits):
        self.Nb_bits = Nb_bits
        self.Nb_QLvls = 2**Nb_bits


    def training(self, raw_x):
        np.random.shuffle(raw_x)
        init_assignment_pts = np.linspace(raw_x.min(), raw_x.max(), num=self.Nb_QLvls)
        QLvls, _,  _, _, _ = generalized_lloyd_LBG.compute_quantization(raw_x, init_assignment_pts)

        return QLvls

    def quantization(self, raw_x, QLvls, return_cluster_assignments=False):

        bin_edges = (QLvls[:-1] + QLvls[1:]) / 2
        quantized_x_as_index = np.digitize(raw_x, bin_edges)

        if return_cluster_assignments:
            return QLvls[quantized_x_as_index], quantized_x_as_index
        else:
            return QLvls[quantized_x_as_index]

    def msqe(self, raw_x, quantized_x):
        return mean_squared_error(raw_x, quantized_x)

    def to_pfd(self, x, normalized = True):
        symbs, counts = np.unique(x, return_counts=True)
        pdf = counts/len(counts)
        if normalized: pdf = pdf/np.sum(pdf)
        return pdf, symbs

    def entropy1(self, x):
        pdf, _ = self.to_pfd(x, normalized = True)
        return -1*np.sum(pdf*np.log2(pdf))



