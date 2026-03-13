/*
  file:        copy.h
  context:     core copy operation module
  description: defines CopyContext struct and core character-level copy functions
*/

#ifndef COPY_H
#define COPY_H

#include <stdio.h>
#include "stats.h"
#include "tab_handler.h"
#define BUFFER_SIZE 4096

typedef struct {
  FILE    *source;              // source file
  FILE    *dest;                // destination file
  char    buffer[BUFFER_SIZE];  // char buffer @ 4096 bytes
  size_t  buffer_pos;           // buffer position
  size_t  buffer_len;           // buffer length
  int     error;                // error integer
} CopyContext;

int get_character(CopyContext *copy_context);
int put_character(CopyContext *copy_context, int character_to_write);
int copy_stream(CopyContext *copy_context, StatsContext *stats, TabContext *tab_context);

#endif