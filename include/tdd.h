#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#ifndef __TESTING_H__
#define __TESTING_H__

#define test_Success 0

#define test_start() int __INIT_TEST = test_Success

#define test_check(condition)                                                  \
  do {                                                                         \
    if ((condition) == 0 && __INIT_TEST == 0) {                                \
      __INIT_TEST = __LINE__;                                                  \
    }                                                                          \
  } while (false)

#define test_run(function)                                                     \
  do {                                                                         \
    if ((function()) == 0) {                                                   \
      printf("\x1b[32mTest passed: %s \x1b[0m\n", #function);                  \
    } else {                                                                   \
      printf("\x1b[31mTest failed %s at line %d \x1b[0m\n", #function,         \
             function());                                                      \
    }                                                                          \
  } while (false)

#define test_end() return (__INIT_TEST)

#define test_string_equal(str1, str2) test_check(strcmp(str1, str2) == 0)

#endif
