/*
  file:        errors.h
  context:     error reporting module
  description: defines error and status message functions
*/

#ifndef ERRORS_H
#define ERRORS_H

void report_error(const char *message);
void report_success(const char *message);

#endif