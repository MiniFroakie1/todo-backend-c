#ifndef UTILS_H_
#define UTILS_H_

typedef enum {
  OK = 200,
  BAD_REQUEST = 400,
  NOT_FOUND = 404,
  INTERNAL_SERVER_ERROR = 500,
  NOT_IMPLEMENTED = 501,
} HTTP_staus;

typedef struct {
  char *body;
  HTTP_staus status;
} HTTP_response;

char *simple_message(const char *message);
char *list_message(void **message);

#endif
