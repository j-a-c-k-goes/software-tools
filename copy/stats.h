/*
  file:        stats.h
  context:     statistics tracking module
  description: defines StatsContext struct and statistics tracking functions
*/

#ifndef STATS_H
#define STATS_H

typedef struct {
  unsigned long character_count;  // total characters read
  unsigned long line_count;       // total lines read
  unsigned long word_count;       // total words read
  unsigned long sentence_count;   // total sentences read
  int enable_sentence_count;      // flag to enable sentence counting
} StatsContext;

StatsContext* initialize_stats_context(int enable_sentence_count);
void update_stats(StatsContext *stats, int current_character);
void display_stats(StatsContext *stats);
void cleanup_stats_context(StatsContext *stats);

#endif
