/*
  file:        copy.c
  context:     core copy operation module
  description: implements character-level copy functions with buffering
*/

#include "copy.h"
#include "stats.h" // in copy.h but include here too for explicit clarity

int get_character(CopyContext *copy_context) {
  if (!copy_context || !copy_context->source) {
    printf("%s\n", "not copy context or context source");
    if (copy_context) {
      printf("%s\n", "setting context error integer to 1 (indicates error)");
      copy_context->error = 1;
    }
    return EOF;
  }

  if (copy_context->buffer_pos >= copy_context->buffer_len) {
    printf("%s\n", "buffer position greater than buffer length");
    copy_context->buffer_len = fread(
      copy_context->buffer,  // param: copy context buffer
      1,                     // error integer
      BUFFER_SIZE,           // param: buffer size
      copy_context->source   // param: source to copy to (destination)
    );
    // printf("%s\n", "setting buffer position to 0");
    copy_context->buffer_pos = 0;
    if (copy_context->buffer_len == 0) {
      printf("%s\n", "ok to return end of file");
      return EOF;
    }
  }
  return (unsigned char)copy_context->buffer[copy_context->buffer_pos++];
}

int put_character(CopyContext *copy_context, int character_to_write) {
  printf("%s\n", "validating copy context and destination file");
  if (!copy_context || !copy_context->dest) {
    printf("%s\n", "invalid copy context or destination file");
    if (copy_context) {
      printf("%s\n", "setting context error integer to 1 (indicates error)");
      copy_context->error = 1;
    }
    return -1;
  }
  // printf("%s\n", "writing character to destination file");
  if (fputc(character_to_write, copy_context->dest) == EOF) {
    printf("%s\n", "error writing character to destination file");
    copy_context->error = 1;
    return -1;
  }
  return 0;
}

int copy_stream(CopyContext *copy_context, StatsContext *stats) {
  printf("%s\n", "beginning copy stream operation");
  int current_character;
  while ((current_character = get_character(copy_context)) != EOF) {
    //printf("%s\n", "reading character from source, writing to destination");
    if (put_character(copy_context, current_character) != 0) {
      printf("%s\n", "error during put_character operation");
      return -1;
    }
    //printf("%s\n", "updating statistics for current character");
    update_stats(stats, current_character);
  }
  printf("%s\n", "end of file reached, copy stream operation complete");
  return copy_context->error ? -1 : 0;
}