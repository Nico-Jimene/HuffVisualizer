#include "../include/frequencies.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool totalFrequncies(Freqs f, const char *path) {
  FILE *fp = fopen(path, "r");
  unsigned char ch;

  if (fp == NULL) {
    return false;
  } else {

    for (ch = fgetc(fp); !feof(fp); ch = fgetc(fp)) {
      if (ch != '\n' && ch != ' ') {

        f[ch] += 1;
      }
    }
    fclose(fp);
    return true;
  }
}
