#ifndef FILES_H
#define FILES_H

#include <stdlib.h>

typedef struct {
  float seconds;
  char* title;
} Timestamp;

Timestamp* read_file(const char* filepath, size_t* count);

#endif // FILES_H
