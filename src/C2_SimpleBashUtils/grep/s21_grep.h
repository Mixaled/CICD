#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct eb {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
  char **patterns;
  char **filename;
  int pattern_count;
  int file_count;
};

void find_words(struct eb st1);

void func();

void read_file(char *name, char **patterns, int *pattern_count);