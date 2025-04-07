#include "headers/handler.h"
#include "headers/pg.h"
#include "headers/response_builder.h"
#include "headers/utils.h"
#include <microhttpd.h>
#include <setjmp.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

jmp_buf exeption_buffer;

#define TRY if (setjmp(exeption_buffer) == 0)
#define CATCH else

void log_api(const char *url, const char *method) {
  printf("[%s] %s\n", method, url);
}

enum MHD_Result handler(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls) {
  char *url_str = (char *)url;
  char *method_str = (char *)method;
  int ret;

  struct MHD_Response *response;
  HTTP_response response_api;

  log_api(url_str, method_str);

  TRY {
    if (strcmp(url_str, "/") == 0) {
      response_api =
          (HTTP_response){.body = simple_message("Hello World!"), .status = OK};
    } else if (strcmp(url_str, "/database") == 0) {
      void **values = getAllIssues();
      response_api =
          (HTTP_response){.body = list_message(values), .status = OK};
    } else {
      response_api = (HTTP_response){.body = simple_message("Not Found"),
                                     .status = NOT_FOUND};
    }
  }
  CATCH {
    response_api = (HTTP_response){.body = "Internal Server Error",
                                   .status = INTERNAL_SERVER_ERROR};
  }

  HTTP_build_response_JSON(&response, response_api.body);
  if (!response)
    return MHD_NO;

  ret = MHD_queue_response(connection, response_api.status, response);
  MHD_destroy_response(response);

  return ret;
}

void *cleanup(void *cls, struct MHD_Connection *connection, void **con_cls,
              enum MHD_RequestTerminationCode toe) {
  printf("cleanup time\n");
  return cls;
}
