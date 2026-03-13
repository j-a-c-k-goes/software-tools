/*
  file:        tab_handler.c
  context:     tab handling module
  description: implements tab expansion, setting, and position tracking
*/

#include <stdlib.h>
#include <stdio.h>
#include "tab_handler.h"

TabContext* initialize_tab_context(int enable_tab_handler) {
  printf("%s\n", "allocating memory for tab context");
  TabContext *tab_context = malloc(sizeof(TabContext));
  if (!tab_context) {
    printf("%s\n", "memory allocation for tab context failed");
    return NULL;
  }

  printf("%s\n", "initializing tab handler enable flag");
  printf("%s\n", "initializing tab stop width to 4");
  printf("%s\n", "initializing current column to 0");
  tab_context->enable_tab_handler = enable_tab_handler;
  tab_context->tab_stop_width     = TAB_STOP_WIDTH;
  tab_context->current_column     = 0;
  printf("%s\n", "tab context initialization complete");
  return tab_context;
}

int de_tab(TabContext *tab_context, int current_character) {
  if (!tab_context) {
    printf("%s\n", "tab context is null, cannot de-tab");
    return current_character;
  }

  if (!tab_context->enable_tab_handler) {
    printf("%s\n", "tab handler disabled, returning character unchanged");
    if (current_character == '\n') {
      tab_context->current_column = 0;
    } else {
      tab_context->current_column++;
    }
    return current_character;
  }

  // convert tab to spaces
  if (current_character == '\t') {
    printf("%s\n", "converting tab to spaces");
    int spaces_to_next_stop = tab_context->tab_stop_width - (tab_context->current_column % tab_context->tab_stop_width);
    tab_context->current_column += spaces_to_next_stop;
    return ' ';  // return first space, caller handles remaining spaces
  }

  // track column position
  if (current_character == '\n') {
    printf("%s\n", "resetting column position on newline");
    tab_context->current_column = 0;
  } else {
    tab_context->current_column++;
  }

  return current_character;
}

int set_tab(TabContext *tab_context, int current_character) {
  if (!tab_context) {
    printf("%s\n", "tab context is null, cannot set tab");
    return current_character;
  }

  if (!tab_context->enable_tab_handler) {
    printf("%s\n", "tab handler disabled, returning character unchanged");
    if (current_character == '\n') {
      tab_context->current_column = 0;
    } else {
      tab_context->current_column++;
    }
    return current_character;
  }

  // convert spaces to tabs at tab stops
  if (current_character == ' ' && tab_position(tab_context) == 1) {
    printf("%s\n", "converting spaces to tab at tab stop");
    tab_context->current_column += tab_context->tab_stop_width;
    return '\t';
  }

  // track column position
  if (current_character == '\n') {
    printf("%s\n", "resetting column position on newline");
    tab_context->current_column = 0;
  } else {
    tab_context->current_column++;
  }

  return current_character;
}

int tab_position(TabContext *tab_context) {
  if (!tab_context) {
    printf("%s\n", "tab context is null, cannot determine tab position");
    return 0;
  }

  // return 1 if at tab stop, 0 otherwise
  int at_tab_stop = (tab_context->current_column % tab_context->tab_stop_width) == 0;
  if (at_tab_stop) {
    printf("%s %d\n", "at tab stop position:", tab_context->current_column);
  }
  return at_tab_stop;
}

void cleanup_tab_context(TabContext *tab_context) {
  printf("%s\n", "beginning cleanup of tab context");
  if (!tab_context) {
    printf("%s\n", "tab context is null, returning");
    return;
  }

  printf("%s\n", "freeing tab context memory");
  free(tab_context);
  printf("%s\n", "tab context cleanup complete");
}
