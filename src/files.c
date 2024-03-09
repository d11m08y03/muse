#include "files.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Timestamp *read_file(const char *filepath, size_t *count) {
  FILE *file;
  file = fopen(filepath, "r");
  if (file == NULL) {
    fprintf(stderr, "Could not open file.");
    exit(EXIT_FAILURE);
  }

  size_t bufferSize = 128;
  char lineBuffer[128];
  Timestamp *timestamps = malloc(sizeof(Timestamp) * ++(*count));

  while (fgets(lineBuffer, bufferSize, file)) {
    if (lineBuffer[strlen(lineBuffer) - 1] == '\n') {
      lineBuffer[strlen(lineBuffer) - 1] = '\0';
    }

    float time;
    if (sscanf(lineBuffer, "%f", &time) != 1) {
      fprintf(stderr, "Wrong time format.");
      exit(EXIT_FAILURE);
    }

    if (fgets(lineBuffer, bufferSize, file) == NULL) {
      fprintf(stderr, "Wrong record format.");
      exit(EXIT_FAILURE);
    }

    char *title = malloc(strlen(lineBuffer));
    if (title == NULL) {
      fprintf(stderr, "Error allocating memory.");
      exit(EXIT_FAILURE);
    }
    strcpy(title, lineBuffer);

    timestamps[*count - 1].seconds = time;
    timestamps[*count - 1].title = title;
    *count = *count + 1;
    timestamps = realloc(timestamps, sizeof(Timestamp) * (*count));
  }
  (*count)--;
  timestamps = realloc(timestamps, sizeof(Timestamp) * (*count));

  fclose(file);

  return timestamps;
}
