#ifndef HANDLER_H_
#define HANDLER_H_

#include <microhttpd.h>

enum MHD_Result handler(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls);
void *cleanup(void *cls, struct MHD_Connection *connection, void **con_cls,
              enum MHD_RequestTerminationCode toe);
#endif
