#include <iostream>
#include <stdlib.h>
#include <stdint.h>
#include "sds_lib.h"
#include "network.h"
#include "software_weight_definitions.h"
#include <math.h>
#include <sys/time.h>

// process only 1K images of 10K images of the dataset
#define INPUT_IMAGES 1000

class perf_counter
{
public:
     uint64_t tot, cnt, calls, time_cnt;
     struct timeval T0,T1,res;
     struct timezone otinanai;
     perf_counter() : tot(0), cnt(0), calls(0), time_cnt(0) {};
     inline void reset()
     {
    	 tot = cnt = calls = 0;
     }
     inline void start()
     {
    	 cnt = sds_clock_counter();
    	 calls++;
     };
     inline void stop()
     {
    	 tot += (sds_clock_counter() - cnt);
     };
     inline uint64_t avg_cpu_cycles()
     {
    	 return ((tot+(calls>>1)) / calls);
     };
};

static inline float ReLu(float value)
{
	if (value < 0)
		return 0;
	return value;
}

void sw_forward_propagation(float *input, float *output)
{
	float layer_1_out[M1];
	float layer_2_out[M2];

	// Layer 1
	for (int i=0; i<M1; i++)
	{
		float result = 0;
		for (int j=0; j<N1; j++)
		{
			float term = input[j] * W1_sw[i][j];
			result += term;
		}
		layer_1_out[i] = ReLu(result);
	}

	// Layer 2
	for (int i=0; i<M2; i++)
	{
		float result = 0;
		for (int j=0; j<N2; j++)
		{
			float term = layer_1_out[j] * W2_sw[i][j];
			result += term;
		}
		layer_2_out[i] = ReLu(result);
	}

	// Layer 3
	for (int i=0; i<M3; i++)
	{
		float result = 0;
		for (int j=0; j<N3; j++)
		{
			float term = layer_2_out[j] * W3_sw[i][j];
			result += term;
		}
		output[i] = tanh(result);
	}
}

void flush_array(char *ar, int size)
{
    for(int i=0; i<size; i++)
    {
        ar[i] = '\0';
    }
}

void copy_ar(float *source, float *dest)
{
	for (int i=0; i<392; i++)
		dest[i] = source[i];
}

void parse_dataset(float *input, int batch_number)
{
	 /* Parse CSV file containing in each row pixel values for half
	 cut MNIST images from the whole test set */

	FILE *fp;
	fp = fopen("data.txt", "r");

	int c;
	char number[20] = {'\0'};
	int i = 0;
	int I = 0;

	do
	{
		c = fgetc(fp);
		if (c != ';' && c != '\n')
		{
			number[i] = c;
			i++;
		}
		else
		{
			float value = atof(number);
			input[I] = value;
			I++;
			i=0;
			flush_array(number,20);
		}

	}while ( c != EOF && I<batch_number*392);

	fclose(fp);
}



using namespace std;
int main()
{
	float *x, *y_hw, *y_sw;

	x = (float *)malloc(N1 * INPUT_IMAGES * sizeof(float));
	y_hw = (float *)malloc(M3 * INPUT_IMAGES * sizeof(float));
	y_sw = (float *)malloc(M3 * INPUT_IMAGES * sizeof(float));

	perf_counter hw_ctr, sw_ctr;

	cout << "Starting dataset parsing..." << endl;
	parse_dataset(x, INPUT_IMAGES);
	cout << "Parsing finished..." << endl;

	float *input, *output;

	float *fpga_in, *fpga_out;
	fpga_in = (float *)sds_alloc(N1 * sizeof(float));
	fpga_out = (float *)sds_alloc(M3 * sizeof(float));

	cout << "Starting hardware calculations..." << endl;

	for (int i=0; i<INPUT_IMAGES; i++)
	{

		input = x + i*N1;
		output = y_hw + i*N1;
		copy_ar(input, fpga_in);

		hw_ctr.start();
		forward_propagation(fpga_in, fpga_out);
		hw_ctr.stop();

		copy_ar(fpga_out, output);
	}

	cout << "Hardware calculations finished." << endl;

	cout << "Starting software calculations..." << endl;

	for (int i=0; i<INPUT_IMAGES; i++)
	{
		input = x + i*N1;
		output = y_sw + i*N1;
		sw_ctr.start();
		sw_forward_propagation(input, output);
		sw_ctr.stop();
	}
	cout << "Software calculations finished." << endl;


	uint64_t hw_cycles = hw_ctr.avg_cpu_cycles();
	uint64_t sw_cycles = sw_ctr.avg_cpu_cycles();

	double speedup = ((double) sw_cycles) / ((double) hw_cycles);

	cout << "Hardware cycles : " << hw_cycles << endl;
	cout << "Software cycles : " << sw_cycles << endl;
	cout << "Speed-Up        : " << speedup  << endl;

	// Save results to output.txt file

	FILE *fp;
	fp = fopen("output.txt", "w");

	fprintf(fp, "Software Results;Hardware Results\n");

	cout << "Saving results to output.txt..." << endl;
	for(int i=0 ; i<INPUT_IMAGES * M3; i++)
	{
		fprintf(fp, "%f;%f\n",y_sw[i], y_hw[i]);
	}
	fclose(fp);


	free(x);
	free(y_hw);
	free(y_sw);
	sds_free(fpga_in);
	sds_free(fpga_out);
}
