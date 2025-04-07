#include "headers/handler.h"
#include "headers/pg.h"
#include <microhttpd.h>
#include <stdio.h>

#define PORT 8888

int main() {
  struct MHD_Daemon *daemon;
  daemon = MHD_start_daemon(MHD_USE_THREAD_PER_CONNECTION, PORT, NULL, NULL,
                            &handler, NULL, MHD_OPTION_NOTIFY_COMPLETED,
                            &cleanup, NULL, MHD_OPTION_END);
  if (!daemon)
    return 0;

  setup();

  getchar();

  MHD_stop_daemon(daemon);

  return 0;
}
