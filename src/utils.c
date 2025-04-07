#include "headers/utils.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *simple_message(const char *message) {
  size_t formatted_message_size = strlen(message) + 20;
  char *formatted_message = malloc(formatted_message_size);

  if (formatted_message) {
    snprintf(formatted_message, formatted_message_size, "{\"message\": \"%s\"}",
             message);
  }

  return formatted_message;
}

char *list_message(void **message) {
  size_t formatted_message_size = 3;
  size_t message_length = *((int *)message[0]);

  for (int i = 0; i < message_length; ++i)
    formatted_message_size += strlen(message[i + 1]) + 3;

  --formatted_message_size;
  char *formatted_message = malloc(formatted_message_size);
  strcpy(formatted_message, "[");
  for (int i = 0; i < message_length; ++i) {
    strcat(formatted_message, "\"");
    strcat(formatted_message, message[i + 1]);
    strcat(formatted_message, "\",");
  }
  formatted_message[formatted_message_size - 2] = ']';

  return formatted_message;
}
