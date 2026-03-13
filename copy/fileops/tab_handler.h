/*
  file:        tab_handler.h
  context:     tab handling module
  description: defines tab manipulation functions for file processing
*/

#ifndef TAB_HANDLER_H
#define TAB_HANDLER_H

#define TAB_STOP_WIDTH 4

typedef struct {
  int enable_tab_handler;  // flag to enable tab handling
  int tab_stop_width;      // spaces per tab stop
  int current_column;      // current column position
} TabContext;

TabContext* initialize_tab_context(int enable_tab_handler);
int de_tab(TabContext *tab_ctx, int current_character);
int set_tab(TabContext *tab_ctx, int current_character);
int tab_position(TabContext *tab_ctx);
void cleanup_tab_context(TabContext *tab_ctx);

#endif
