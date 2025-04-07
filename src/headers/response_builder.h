#ifndef RESPONSE_BUILDER_H_
#define RESPONSE_BUILDER_H_

#include <microhttpd.h>

void HTTP_build_response_JSON(struct MHD_Response **response,
                              const char *message);

#endif
