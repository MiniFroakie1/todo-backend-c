#ifndef PG_H_
#define PG_H_

#include <libpq-fe.h>
#define PG_DB_NAME "todo"
#define PG_USER "todo"
#define PG_PASSWORD "todo"
#define PG_HOST "127.0.0.1"
#define PG_PORT "5432"

void setup();
void **getAllIssues();

#endif
