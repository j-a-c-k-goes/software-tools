/*
  file:        fileops.c
  context:     file operations module
  description: implements file initialization and cleanup with error handling
*/

#include <stdlib.h>
#include "fileops.h"
#include "../errors/errors.h"

CopyContext* initialize_copy_context(const char *source_path, const char *dest_path) {
  printf("%s\n", "allocating memory for copy context");
  CopyContext *copy_context = malloc(sizeof(CopyContext));
  
  if (!copy_context) {
    printf("%s\n", "memory allocation failed");
    report_error("memory allocation failed");
    return NULL;
  }

  printf("%s\n", "opening source file for reading");
  copy_context->source = fopen(source_path, "rb");
  if (!copy_context->source) {
    printf("%s\n", "error opening source file");
    report_error("error opening source file");
    free(copy_context);
    return NULL;
  }

  printf("%s\n", "opening destination file for writing");
  copy_context->dest = fopen(dest_path, "wb");
  if (!copy_context->dest) {
    printf("%s\n", "error opening destination file");
    report_error("error opening destination file");
    fclose(copy_context->source);
    free(copy_context);
    return NULL;
  }

  printf("%s\n", "initializing buffer position to 0");
  printf("%s\n", "initializing buffer length to 0");
  printf("%s\n", "initializing error integer to 0");
  copy_context->buffer_pos = 0;
  copy_context->buffer_len = 0;
  copy_context->error      = 0;
  printf("%s\n", "copy context initialization complete");
  return copy_context;
}

void cleanup_copy_context(CopyContext *copy_context) {
  //printf("%s\n", "beginning cleanup of copy context");
  if (!copy_context) {
    printf("%s\n", "copy context is null, returning");
    return;
  }
  if (copy_context->source) {
    printf("%s\n", "closing source file");
    fclose(copy_context->source);
  }
  if (copy_context->dest) {
    printf("%s\n", "closing destination file");
    fclose(copy_context->dest);
  }
  printf("%s\n", "freeing copy context memory");
  free(copy_context);
  printf("%s\n", "cleanup complete");
}
