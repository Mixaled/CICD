#include "s21_grep.h"

int main(int argc, char *argv[]) {
  struct eb st1 = {0};
  int index = 0;
  struct option options[] = {
      {"pattern", 0, NULL, 'e'},           {"ignore-uppercase", 0, NULL, 'i'},
      {"invert-match.", 0, NULL, 'v'},     {"output-count", 0, NULL, 'c'},
      {"output-matching ", 0, NULL, 'l'},  {"precede", 0, NULL, 'n'},
      {"without-preceding", 0, NULL, 'h'}, {"suppress-error", 0, NULL, 's'},
      {"take-regexes ", 0, NULL, 'f'},     {"matching-line", 0, NULL, 'o'}};
  int c;
  while ((c = getopt_long(argc, argv, "e:ivclnhsf:o", options, &index)) != -1) {
    switch (c) {
      case 'e':
        st1.pattern_count++;
        st1.patterns =
            realloc(st1.patterns, sizeof(char *) * st1.pattern_count);
        st1.patterns[st1.pattern_count - 1] =
            malloc((strlen(optarg) + 1) * sizeof(char));
        stpcpy(st1.patterns[st1.pattern_count - 1], optarg);
        st1.e = 1;
        break;
      case 'i':
        st1.i = 1;
        break;
      case 'v':
        st1.v = 1;
        break;
      case 'c':
        st1.c = 1;
        break;
      case 'l':
        st1.l = 1;
        break;
      case 'n':
        st1.n = 1;
        break;
      case 'h':
        st1.h = 1;
        break;
      case 's':
        st1.s = 1;
        break;
      case 'f':
        read_file(optarg, st1.patterns, &st1.pattern_count);
        st1.f = 1;
        break;
      case 'o':
        st1.o = 1;
        break;
      default:
        fprintf(stderr, "grep: No such flag\n");
    }
  }
  int pos_f = optind;
  while (pos_f < argc) {
    if (st1.e == 1) {
      st1.file_count++;
      st1.filename = realloc(st1.filename, sizeof(char *) * st1.file_count);
      st1.filename[st1.file_count - 1] =
          malloc((strlen(argv[pos_f]) + 1) * sizeof(char));
      stpcpy(st1.filename[st1.file_count - 1], argv[pos_f]);
    } else {
      st1.pattern_count++;
      st1.patterns = realloc(st1.patterns, sizeof(char *) * st1.pattern_count);
      st1.patterns[st1.pattern_count - 1] =
          malloc((strlen(argv[pos_f]) + 1) * sizeof(char));
      stpcpy(st1.patterns[st1.pattern_count - 1], argv[pos_f]);
      st1.e = 1;
    }
    pos_f++;
  }
  find_words(st1);
  for (int j = 0; j < st1.pattern_count; j++) {
    free(st1.patterns[j]);
  }
  for (int j = 0; j < st1.file_count; j++) {
    free(st1.filename[j]);
  }
  free(st1.filename);
  free(st1.patterns);
  return 0;
}

//???????????????????????????????????????????????????zxc??????????????????????????????????????????????????????????????????????
void read_file(char *name, char **patterns, int *pattern_count) {
  int p_count = *pattern_count;
  FILE *f;
  char *str = NULL;
  ssize_t len;
  if ((f = fopen(optarg, "r")) == NULL) {
    fprintf(stderr, "grep: %s: No such file or directory\n", optarg);
  } else {
    while (getline(&str, &len, f) != -1) {
      p_count++;
      patterns = realloc(patterns, sizeof(char *) * p_count);
      patterns[p_count - 1] = malloc((len + 1) * sizeof(char));
      stpcpy(patterns[p_count - 1], optarg);
    }
    if (str != NULL) {
      free(str);
    }
    fclose(f);
  }
}

void func(int i, struct eb st1, FILE *f) {
  ssize_t len = 0;
  int string_num = 0;
  int check = 0;
  int c_count = 0;
  char *str = NULL;
  while (getline(&str, &len, f) != -1) {
    string_num++;
    str[strcspn(str, "\n")] = '\0';
    for (int j = 0; j < st1.pattern_count; j++) {
      regex_t re;
      if (st1.i == 1) {
        regcomp(&re, st1.patterns[j], REG_ICASE);
      } else {
        regcomp(&re, st1.patterns[j], 0);
      }
      check = regexec(&re, str, 0, NULL, 0);
      regfree(&re);
      if (st1.c == 1 && check == 0) {
        c_count++;
      }
      if (st1.h == 1 && check == 0) {
        printf("%s\n", str);
      }
      if (st1.n == 1 && check == 0 && st1.file_count == 1) {
        printf("%d:%s\n", string_num, str);
      }
      if (st1.n == 1 && check == 0 && st1.file_count > 1) {
        printf("%s:%d:%s\n", st1.filename[i], string_num, str);
      }
      if (st1.v == 1 && check == 1) {
        if (st1.l) {
          printf("%s\n", st1.filename[i]);
          if (str != NULL) free(str);
          return;
        }
        if (st1.file_count > 1) {
          printf("%s:", st1.filename[i]);
        }

        printf("%s\n", str);
        break;
      } else if (check == 0 && st1.v != 1 && st1.c != 1 && st1.n != 1 &&
                 st1.h != 1) {
        if (st1.l) {
          printf("%s\n", st1.filename[i]);
          if (str != NULL) free(str);
          return;
        }
        if (st1.file_count > 1) {
          printf("%s:", st1.filename[i]);
        }
        printf("%s\n", str);
        break;
      }
    }
  }
  if (str != NULL) free(str);
  if (st1.c == 1) {
    printf("%d\n", c_count);
  }
}

void find_words(struct eb st1) {
  FILE *f = NULL;
  char *str = NULL;

  for (int i = 0; i < st1.file_count; i++) {
    if ((f = fopen(st1.filename[i], "r")) == NULL) {
      fprintf(stderr, "grep: %s: No such file or directory\n", st1.filename[i]);
    } else {
      func(i, st1, f);
      fclose(f);
    }
  }
}
