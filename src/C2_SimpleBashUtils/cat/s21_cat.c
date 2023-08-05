#include "s21_cat.h"

int main(int argc, char *argv[]) {
  FILE *f = NULL;
  char sym = ' ';
  int i = 0;
  int n = 0;
  int E = 0;
  int e = 0;
  int t = 0;
  int T = 0;
  int b = 0;
  int s = 0;
  struct option options[] = {{"number-nonblank", 0, NULL, 'b'},
                             {"show-ends", 0, NULL, 'E'},
                             {"number", 0, NULL, 'n'},
                             {"squeeze-blank", 0, NULL, 's'},
                             {"show-tabs", 0, NULL, 'T'}};
  int c;
  int res = 1;
  while ((c = getopt_long(argc, argv, "beEnstT", options, &i)) != -1) {
    switch (c) {
      case 'b': {
        b = 1;
        break;
      }
      case 'n': {
        n = 1;
        break;
      }
      case 'E': {
        E = 1;
        break;
      }
      case 'e': {
        e = 1;
        break;
      }
      case 't': {
        t = 1;
        break;
      }
      case 'T': {
        T = 1;
        break;
      }
      case 's': {
        s = 1;
        break;
      }
      default:
        res = 0;
    }
  }
  for (int q = optind; (q < argc) && res; q++) {
    if ((f = fopen(argv[q], "r")) == NULL) {
      fprintf(stderr, "cat: %s: No such file or directory\n", argv[q]);
    } else {
      if (s == 1) {
        sfunct(f, sym);
      } else if (b == 1) {
        bfunct(f, sym);
      } else if (n == 1) {
        numeric(f, sym);
      } else if (E == 1) {
        efunct(f, sym);
      } else if (e == 1) {
        evfunct(f, sym);
      } else if (t == 1) {
        tvfunct(f, sym);
      } else if (T == 1) {
        tfunct(f, sym);
      } else {
        read_file(f, sym);
      }
      fclose(f);
    }
  }
  return 0;
}
void read_file(FILE *f, char sym) {
  while ((sym = fgetc(f)) != EOF) {
    printf("%c", sym);
  }
}

void numeric(FILE *f, char sym) {
  int number = 2;
  char prev = ' ';
  printf("%6d\t", 1);
  while ((sym = fgetc(f)) != EOF) {
    if (prev == '\n') {
      printf("%6d\t", number);
      number++;
    }
    printf("%c", sym);
    prev = sym;
  }
}

void efunct(FILE *f, char sym) {
  while ((sym = fgetc(f)) != EOF) {
    if (sym == '\n') {
      printf("%c", '$');
    }
    printf("%c", sym);
  }
}

void tfunct(FILE *f, char sym) {
  while ((sym = fgetc(f)) != EOF) {
    if (sym == '\t') {
      printf("%c%c", '^', 'I');
    }
    printf("%c", sym);
  }
}

void bfunct(FILE *f, char sym) {
  char prev = ' ';
  int number = 2;
  printf("%6d\t", 1);
  while ((sym = fgetc(f)) != EOF) {
    if (prev == '\n') {
      if (sym != '\n') {
        printf("%6d\t", number);
        number++;
      }
    }
    printf("%c", sym);
    prev = sym;
  }
}

void sfunct(FILE *f, char sym) {
  char prev = ' ';
  int skip = 0;
  while ((sym = fgetc(f)) != EOF) {
    if (prev == '\n') {
      if (sym == '\n') {
        if (skip) {
          continue;
        }
        skip = 1;
      } else {
        skip = 0;
      }
    }
    printf("%c", sym);
    prev = sym;
  }
}

void tvfunct(FILE *f, char sym) {
  while ((sym = fgetc(f)) != EOF) {
    if (sym < 32 && sym != '\t' && sym != '\n') {
      printf("^%c", sym + 64);
    } else if (sym == 127) {
      printf("^?");
    } else if (sym == '\t') {
      printf("^I");
    } else {
      printf("%c", sym);
    }
  }
}

void evfunct(FILE *f, char sym) {
  while ((sym = fgetc(f)) != EOF) {
    if (sym < 32 && sym != '\t' && sym != '\n') {
      printf("^%c", sym + 64);
    } else if (sym == 127) {
      printf("^?");
    } else if (sym == '\n') {
      printf("$%c", sym);
    } else {
      printf("%c", sym);
    }
  }
}
