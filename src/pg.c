#include "headers/pg.h"
#include <libpq-fe.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *conninfo;

void setup() {
  size_t conninfo_size = strlen("dbname= user= password= host= port=") +
                         strlen(PG_DB_NAME) + strlen(PG_USER) +
                         strlen(PG_PASSWORD) + strlen(PG_HOST) +
                         strlen(PG_PORT) + 1;
  conninfo = malloc(conninfo_size);
  snprintf(conninfo, conninfo_size,
           "dbname=%s user=%s password=%s host=%s port=%s", PG_DB_NAME, PG_USER,
           PG_PASSWORD, PG_HOST, PG_PORT);
}

void **getAllIssues() {
  PGconn *conn = PQconnectdb(conninfo);
  if (PQstatus(conn) != CONNECTION_OK) {
    fprintf(stderr, "Error connection to database server %s\n",
            PQerrorMessage(conn));
    PQfinish(conn);
  }
  printf("connected to databse server\n");
  PGresult *res = PQexec(conn, "SELECT * FROM test1");
  if (PQresultStatus(res) == PGRES_TUPLES_OK) {
    printf("Query executed\n");
    const int rows = PQntuples(res);
    const int cols = PQnfields(res);
    printf("%d\n", rows);

    void **ret = malloc(sizeof(char *) * (rows + 1));
    ret[0] = malloc(sizeof(rows));
    memcpy(ret[0], &rows, sizeof(rows));

    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        const char *value = PQgetvalue(res, i, j);
        ret[i + 1] = malloc(strlen(value) + 1);
        strcpy(ret[i + 1], value);
      }
    }

    return ret;
  } else {
    printf("Error while executing query: %s\n", PQerrorMessage(conn));
  }
  PQfinish(conn);

  return NULL;
}
