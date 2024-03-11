#include <stdlib.h>

#include "files.h"
#include "sounds.h"

int main(void) {
  size_t count = 0;
  Timestamp* timestamps = read_file("./res/timestamps.txt", &count);

  init_audio();
  testbed(timestamps, count);
  deallocate_audio();
  free(timestamps);

  return EXIT_SUCCESS;
}
