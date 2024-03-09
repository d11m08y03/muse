#include <stdlib.h>

#include "sounds.h"

int main(void) {
  init_audio();
  start_playing_and_wait();
  deallocate_audio();

  return EXIT_SUCCESS;
}
