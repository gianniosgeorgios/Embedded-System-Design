#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
	FILE *input_file, *len_output_file, *concat_output_file, *sorted_output_file;
	int N=512, i, j, str_len;
	char tmp_str[65], concat_str[129], sort_str[N][65], output_file_name[128];
	
	/* Provide input file through argv. Input file must have at least 512 lines */
	if (argc != 2) {
		printf("Please provide input file\n");
		exit(-1);
	}		
	
	if ((input_file = fopen(argv[1], "r")) == NULL) {
		printf("Cannot open output file with file path %s",argv[1]);		
		perror("open input_file");
		exit(-1);
	}
	
	/* Create output files */
	strcpy(output_file_name, argv[1]);
	strcat(output_file_name, "_len_out");
	if ((len_output_file = fopen(output_file_name, "w")) == NULL) {
		printf("Cannot open output file with file path %s\n",output_file_name);		
		perror("open len_out");
		exit(-1);
	}
	
	strcpy(output_file_name, argv[1]);
	strcat(output_file_name, "_concat_out");
	if ((concat_output_file = fopen(output_file_name, "w")) == NULL) {
		printf("Cannot open output file with file path %s\n",output_file_name);		
		perror("open concat_out");
		exit(-1);
	}
	
	strcpy(output_file_name, argv[1]);
	strcat(output_file_name, "_sorted_out");
	if ((sorted_output_file = fopen(output_file_name, "w")) == NULL) {
		printf("Cannot open output file with file path %s\n",output_file_name);		
		perror("open sorted_out");
		exit(-1);
	}
	
	/* Data input */
	for (i=0; i<N; i++) {
			fscanf(input_file,"%s",tmp_str);
			strcpy(sort_str[i], tmp_str);
			
			str_len = strlen(tmp_str);
			fprintf(len_output_file,"%d\n",str_len);
					
			if (i % 2 == 0) 
				strcpy(concat_str,tmp_str);
			else {
				strcat(concat_str,tmp_str);
				fprintf(concat_output_file,"%s\n",concat_str);
			}					
	}		
	
	/* Sorting of strings - Bubble sort */
	for (i=0; i<N; i++) {
		
		for (j=N-1; j>i; j--)
			if (strcmp(sort_str[j], sort_str[j-1]) < 0) {
				strcpy(tmp_str, sort_str[j-1]);
				strcpy(sort_str[j-1], sort_str[j]);
				strcpy(sort_str[j],tmp_str);
			}	
		
		fprintf(sorted_output_file,"%s\n",sort_str[i]);
	}			
			
	fclose(input_file);
	fclose(len_output_file);
	fclose(concat_output_file);	
	fclose(sorted_output_file);
	
	return 0;
}
