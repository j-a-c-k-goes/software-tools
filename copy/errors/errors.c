/*
  file:        errors.c
  context:     error reporting module
  description: implements centralized error and status message output
*/

#include <stdio.h>

void report_error(const char *message) {
  printf("%s\n", "reporting error to stderr");
  fprintf(stderr, "%-8s %s\n", "ERROR", message);
}

void report_success(const char *message) {
  printf("%s\n", "reporting success to stdout");
  fprintf(stdout, "%-8s %s\n", "SUCCESS", message);
}
