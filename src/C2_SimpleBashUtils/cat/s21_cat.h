#include <ctype.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_file(FILE *f, char sym);
void numeric(FILE *f, char sym);
void efunct(FILE *f, char sym);
void tfunct(FILE *f, char sym);
void bfunct(FILE *f, char sym);
void sfunct(FILE *f, char sym);
void tvfunct(FILE *f, char sym);
void evfunct(FILE *f, char sym);