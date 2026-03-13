/*
  file:        main.c
  context:     entry point
  description: orchestrates file operations, copy logic, and error reporting
*/

#include <stdlib.h>
#include <string.h>
#include "copy.h"
#include "fileops.h"
#include "errors.h"
#include "stats.h"
#include "tab_handler.h"

#define EXPECTED_ARG_COUNT 3
#define SENTENCE_COUNT_FLAG "--sentence-count"
#define TAB_HANDLER_FLAG "--tab-handler"

int main(int argc, char *argv[]) {
  printf("%s\n", "copy program started");
  printf("%s %d\n", "argument count:", argc);
  
  int enable_sentence_count = 0;
  int enable_tab_handler    = 0;
  int arg_index             = 1;
  
  // parse optional flags
  printf("%s\n", "parsing command line arguments");
  while (arg_index < argc && argv[arg_index][0] == '-') {
    printf("%s %s\n", "processing flag:", argv[arg_index]);
    if (strcmp(argv[arg_index], SENTENCE_COUNT_FLAG) == 0) {
      printf("%s\n", "sentence counting enabled");
      enable_sentence_count = 1;
    } else if (strcmp(argv[arg_index], TAB_HANDLER_FLAG) == 0) {
      printf("%s\n", "tab handler enabled");
      enable_tab_handler = 1;
    }
    arg_index++;
  }
  
  // validate required arguments
  int remaining_args = argc - arg_index;
  if (remaining_args != 2) {
    printf("%s\n", "invalid argument count, expected 2 files after flags");
    report_error("usage: copy [--sentence-count] [--tab-handler] <source> <destination>");
    exit(EXIT_FAILURE);
  }
  
  const char *source_file      = argv[arg_index];     // declare arg to char pointer
  const char *destination_file = argv[arg_index + 1]; // declare arg to char pointer

  printf("%s %s\n", "source file:", source_file);
  printf("%s %s\n", "destination file:", destination_file);
  printf("%s\n", "initializing copy context");

  CopyContext *copy_context = initialize_copy_context(source_file, destination_file);
  
  if (!copy_context) {
    printf("%s\n", "copy context initialization failed");
    exit(EXIT_FAILURE);
  }

  printf("%s\n", "initializing stats context");
  StatsContext *stats = initialize_stats_context(enable_sentence_count);
  if (!stats) {
    printf("%s\n", "stats context initialization failed");
    cleanup_copy_context(copy_context);
    exit(EXIT_FAILURE);
  }

  printf("%s\n", "initializing tab context");
  TabContext *tab_ctx = initialize_tab_context(enable_tab_handler);
  if (!tab_ctx) {
    printf("%s\n", "tab context initialization failed");
    cleanup_copy_context(copy_context);
    cleanup_stats_context(stats);
    exit(EXIT_FAILURE);
  }

  printf("%s\n", "starting copy stream operation");
  if (copy_stream(copy_context, stats, tab_ctx) != 0) {
    printf("%s\n", "copy stream operation failed");
    report_error("copy operation failed");
    cleanup_copy_context(copy_context);
    cleanup_stats_context(stats);
    exit(EXIT_FAILURE);
  }

  printf("%s\n", "copy stream operation succeeded");
  printf("%s\n", "displaying file statistics");
  display_stats(stats);
  printf("%s\n", "cleaning up copy context");
  cleanup_copy_context(copy_context);
  printf("%s\n", "cleaning up stats context");
  cleanup_stats_context(stats);
  printf("%s\n", "cleaning up tab context");
  cleanup_tab_context(tab_ctx);
  report_success("file copied successfully");
  printf("%s\n", "copy program completed successfully");
  exit(EXIT_SUCCESS);
}