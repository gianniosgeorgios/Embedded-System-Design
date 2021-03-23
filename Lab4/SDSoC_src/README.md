### Files
* main.cpp: Calls Generator model in SW and HW and measures performance
* network.cpp: It is the core code of the application. He is optimized with HLS to run on HW.
* weight_definitions.h: Contains the trained weights of the generator.
* tanh.h: Stores the pre-computed values of the Tanh mathematical function for HW.
* network.h: Contains various arguments for generator (datatypes, loop limits, etc.)
* data.txt: Contains the input dataset (the upper half of the images).
