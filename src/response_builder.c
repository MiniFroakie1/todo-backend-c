#include "headers/response_builder.h"
#include <microhttpd.h>
#include <stdio.h>
#include <string.h>
void HTTP_build_response_JSON(struct MHD_Response **response,
                              const char *message) {
  *response = MHD_create_response_from_buffer(strlen(message), (void *)message,
                                              MHD_RESPMEM_PERSISTENT);

  if (!response) {
    printf("why?!?!\n");
    return;
  }

  MHD_add_response_header(*response, "Content-Type", "application/json");
  MHD_add_response_header(*response, "Access-Control-Allow-Origin", "*");
  if (!response) {
    printf("?\n");
  }
}
