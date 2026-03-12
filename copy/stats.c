/*
  file:        stats.c
  context:     statistics tracking module
  description: implements character, line, and word counting functionality
*/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "stats.h"

StatsContext* initialize_stats_context(void) {
  printf("%s\n", "allocating memory for stats context");
  StatsContext *stats = malloc(sizeof(StatsContext));
  if (!stats) {
    printf("%s\n", "memory allocation for stats context failed");
    return NULL;
  }

  printf("%s\n", "initializing character count to 0");
  printf("%s\n", "initializing line count to 0");
  printf("%s\n", "initializing word count to 0");
  stats->character_count = 0;  
  stats->line_count      = 0;
  stats->word_count      = 0;
  printf("%s\n", "stats context initialization complete");
  return stats;
}

void update_stats(StatsContext *stats, int current_character) {
  if (!stats) {
    printf("%s\n", "stats context is null, cannot update");
    return;
  }

  // increment character count
  stats->character_count++;
  
  // increment line count on newline
  if (current_character == '\n') { stats->line_count++; }

  // increment word count on whitespace transitions
  static int previous_character_is_whitespace = 1;
  int current_character_is_whitespace         = isspace(current_character);
  if (previous_character_is_whitespace && !current_character_is_whitespace) {
    stats->word_count++;
  }
  previous_character_is_whitespace = current_character_is_whitespace;
}

void display_stats(StatsContext *stats) {
  if (!stats) {
    printf("%s\n", "stats context is null, cannot display");
    return;
  }

  printf("%s\n", "displaying file statistics");
  printf("%-20s %lu\n", "characters:", stats->character_count);
  printf("%-20s %lu\n", "lines:", stats->line_count);
  printf("%-20s %lu\n", "words:", stats->word_count);
}

void cleanup_stats_context(StatsContext *stats) {
  printf("%s\n", "beginning cleanup of stats context");
  if (!stats) {
    printf("%s\n", "stats context is null, returning");
    return;
  }

  printf("%s\n", "freeing stats context memory");
  free(stats);
  printf("%s\n", "stats context cleanup complete");
}
