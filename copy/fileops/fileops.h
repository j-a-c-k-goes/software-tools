/*
  file:        fileops.h
  context:     file operations module
  description: defines file management functions for opening and closing files
*/

#ifndef FILEOPS_H
#define FILEOPS_H

#include "copy.h"

CopyContext* initialize_copy_context(const char *source_path, const char *dest_path);
void cleanup_copy_context(CopyContext *ctx);

#endif
