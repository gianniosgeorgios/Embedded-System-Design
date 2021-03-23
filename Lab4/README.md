# High-Level Synthesis for FPGA

## Description
The purpose of this exercise is to study High Level Synthesis (HLS) for FPGA programming. 
It is about optimizing and accelerating C code to run on hardware of **Xilinx Zybo FPGA**.

## Application
The application studied for optimization is related to neural networks and in particular **Generative Adversarial Networks** (GANs). 
Specifically, the application is about the reconstruction of half images from handwritten digits ([MNIST dataset](https://en.wikipedia.org/wiki/MNIST_database)). 
The ultimate goal is to accelerate this algorithm in relation to the software implementation, but also to measure the image reconstruction quality.

## SDSoC 2016.4 Tool
Using the [SDSoC](https://www.xilinx.com/support/download/index.html/content/xilinx/en/downloadNav/vitis/archive-sdsoc.html) tool, we developed the application for embedded Zybo FPGA. SDSoC provides an Eclipse type environment where we can develop an accelerator that will run in FPGA using HLS optimizations.
We can also estimate the performance and the resources, make the bitstream of the hardware and finally the *sd boot card* where the system will "boot".

## HLS Pragmas
The HLS compiler provides pragmas that can be used to optimize the design:
* Reduce latency
* Improve throughput performance
* Reduce area and device resources
* Control the I/O ports of the kernels

The pragmas we used are the following:
* Loop Pipelining (Shorter latency)
* Loop Unrolling (Higher parallelism)
* Partition of arrays (Increasing memory bandwidth)
* Allocation (Controlling resources)
* Tripcount (More accurate analysis)

## Part 1: Performance and Resources Measurement
* We estimate the performance with **no** optimizations.
* We create the *sd card* with the bitstream and we upload it on zybo. We run the app on board and we **compare** it with the previous estimation.
* We make **Design Space Exploration** to find the optimizations. We test different **HLS pragmas** and we estimate the performance.
* We upload the final - optimal *sd boot card* to zybo and we run the application.
* We save the results in `output.txt`.

Comparing the optimized with the original (unoptimized), we notice that the **Speed-Up** from 2.16 has reached 120.65, above than **55 times faster** than the original.

![Capture](https://user-images.githubusercontent.com/50949470/111984741-71377a00-8b14-11eb-8d8d-15eb2477bd00.PNG)

## Part 2: Quality Measurement
* We combine the half images given as input with the half images from ``output.txt` produced by software and hardware.
* We measure the image reconstruction quality via jupyter notebook with **Max Pixel Error** και **Peak Signal-to-Noise Ratio** (psnr).
* The original implementation uses datatypes of 8-bit. We try to make new designs with 4 and 10 bits and compare the differences.

![Capture1](https://user-images.githubusercontent.com/50949470/111987471-f1abaa00-8b17-11eb-8d97-6207584f00f5.PNG)

*For more information and extra comments about the application, the HLS pragmas, the tools and the results, go to report.*
