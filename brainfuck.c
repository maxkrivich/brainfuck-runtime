/*
 * File:   brainfuck.c
 * Author: maxkrivich
 *
 * Created on 08 March 2017 y.
 */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

#include "brainfuck.h"

extern char* cmd;
extern char* arr;
extern size_t ptr;
extern size_t nsize;
extern FILE* inFile;
extern FILE* outFile;

int main(int argc, char** argv)
{
	parsearg(argc, argv);
	init();
	readfile(inFile, cmd, &nsize);
	execute();
	return EXIT_SUCCESS;
}

void usage(void)
{
	fprintf(stdout, "USAGE:\n\t-i or --ifile <source code file>\n\t-o or --ofile <output file>\n");
}


void parsearg(int argc, char** argv)
{
	if(1 == argc)
	{
		usage();
		exit(-1);
	}
	int res, ind;
	const char * short_opt = "hi:o:";
	const struct option long_opt[] = {
		{"help", no_argument, NULL, 'h'},
		{"ifile",required_argument, NULL, 'i'},
		{"ofile", required_argument, NULL, 'o'},
		{NULL, 0, NULL, 0}
	};

	outFile = stdout;

	while((res = getopt_long(argc, argv, short_opt, long_opt, &ind)) != -1)
	{
		switch(res)
		{
			case 'i': {
				inFile = fopen(optarg, "r");
				if(NULL == inFile)
				{
					#ifdef DEBUG
						fprintf(stderr, "Error opening file: %s\n", strerror(errno));
						assert(inFile);
					#endif
					//TODO: write warning
					exit(EXIT_FAILURE);
				}
				break;
			};
			case 'o': {
				outFile = fopen(optarg, "w+");
				if(NULL == outFile)
				{
					#ifdef DEBUG
					 	fprintf(stderr, "Error opening file: %s\n", strerror(errno));
						assert(outFile);
					#endif
					//TODO: write warning
					exit(EXIT_FAILURE);
				}
				break;
			};
			case '?':
			{
				usage();
				exit(-1);
				break;
			};
			default:
			{
				usage();
				exit(-1);
				break;
			};
		}
	}
}

void init(void)
{
	atexit(onexit);
	ptr = 0;
	arr = (char*) malloc(ARR_SIZE * sizeof(char));
	if(NULL == arr)
	{
		#ifdef DEBUG
			fprintf(stderr, "Error allocaiton: %s\n", strerror(errno));
			assert(arr);
		#endif
		//TODO: write warning
		exit(EXIT_FAILURE);
	}
	memset(arr, 0, ARR_SIZE);

	cmd = (char*) malloc(ARR_SIZE * sizeof(char));
	if(NULL == cmd)
	{
		#ifdef DEBUG
			fprintf(stderr, "Error allocaiton: %s\n", strerror(errno));
			assert(cmd);
		#endif
		//TODO: write warning
		exit(EXIT_FAILURE);
	}
	memset(cmd, 0, ARR_SIZE);

}

void onexit(void)
{
	free(arr);
	free(cmd);
	fclose(inFile);
	fclose(outFile);
}

int execute()
{
	int bracket = 0;
	for(int i = 0; i < nsize; i++)
	{
		switch(cmd[i])
		{
			case '>': ++ptr;
				break;
			case '<': --ptr;
				break;
			case '+': ++arr[ptr];
				break;
			case '-': --arr[ptr];
				break;
			case '.': print();
				break;
			case ',': arr[ptr] = mread();
				break;
			case '[':
			{
					if(!arr[ptr])
					{
						++bracket;
						while(bracket)
						{
							++i;
							if((i <  nsize) && (cmd[i] == '[')) ++bracket;
							if((i <  nsize) && (cmd[i] == ']')) --bracket;
						}
					}
					break;			
			}
			case ']':
			{	
					if(arr[ptr])
					{
	
	                		if(cmd[i] == ']') bracket++;
	                		while(bracket)
	                		{
	                	    	--i;
	                	    	if(cmd[i] == '[') bracket--;
	                	    	if(cmd[i] == ']') bracket++;
	                		}
	                		--i;
					}
					break;
			}
			default: 
				break;
		}


	}
}

void readfile(FILE* f, char* array, size_t* n)
{
	int i = 0;
	while(i < ARR_SIZE && (array[i] = getc(f)) != EOF) ++i;
	*n = i;
}

void print(void)
{
	fprintf(outFile, "%c", arr[ptr]);
}

char mread(void)
{
	char c;
	fscanf(inFile, "%c", &c);
	return c;
}