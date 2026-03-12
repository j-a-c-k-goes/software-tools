/*
  file: main.c
  context: entry point
  description: orchestrates file operations, copy logic, and error reporting
*/

#include <stdlib.h>
#include "copy.h"
#include "fileops.h"
#include "errors.h"

#define EXPECTED_ARG_COUNT 3
int main(int argc, char *argv[]) {
  printf("%s\n", "copy program started");
  printf("%s %d\n", "argument count:", argc);
  
  if (argc != EXPECTED_ARG_COUNT) {
    printf("%s\n", "invalid argument count, expected 3");
    report_error("usage: copy <source> <destination>");
    exit(EXIT_FAILURE);
  }
  const char *source_file      = argv[1]; // declare arg to char pointer
  const char *destination_file = argv[2]; // declare arg to char pointer

  printf("%s %s\n", "source file:", source_file);
  printf("%s %s\n", "destination file:", destination_file);
  printf("%s\n", "initializing copy context");

  CopyContext *copy_context = initialize_copy_context(source_file, destination_file);
  
  if (!copy_context) {
    printf("%s\n", "copy context initialization failed");
    exit(EXIT_FAILURE);
  }

  printf("%s\n", "starting copy stream operation");
  if (copy_stream(copy_context) != 0) {
    printf("%s\n", "copy stream operation failed");
    report_error("copy operation failed");
    cleanup_copy_context(copy_context);
    exit(EXIT_FAILURE);
  }

  printf("%s\n", "copy stream operation succeeded");
  printf("%s\n", "cleaning up copy context");
  cleanup_copy_context(copy_context);
  report_success("file copied successfully");
  printf("%s\n", "copy program completed successfully");
  exit(EXIT_SUCCESS);
}