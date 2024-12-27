#ifndef FREQUENCIES_H
#define FREQUENCIES_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

typedef u_int64_t Freqs[256];

bool totalFrequncies(Freqs f, const char *path);

#endif
