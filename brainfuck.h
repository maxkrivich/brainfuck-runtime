/*
 * File:   brainfuck.h
 * Author: maxkrivich
 *
 * Created on 08 March 2017 y.
 */

#ifndef _BRAINFUCK_H_

	#define _BRAINFUCK_H_
	#define ARR_SIZE 30000

	void parsearg(int, char**);
	void usage(void);
	int execute(void);
	void readfile(FILE*, char*, size_t*);
	void writefile(FILE*);
	void print(void);
	char mread(void);
	int syntaxcheker(const char*);
	void optimizer(void); //TODO: write this func
	void init(void);
	void onexit(void);

	size_t nsize;
	size_t ptr;
	char* arr = NULL;
	char* cmd = NULL;
	FILE* inFile = NULL;
	FILE* outFile = NULL;

#endif