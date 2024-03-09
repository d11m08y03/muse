#ifndef SOUNDS_H
#define SOUNDS_H

#include <stdlib.h>

#include "./miniaudio.h"

#define ERR_EXIT(x)                                                            \
  if (x != MA_SUCCESS)                                                         \
    exit(EXIT_FAILURE);

#define ERR_EXIT_DEALLOCATE1(x)                                                \
  if (x != MA_SUCCESS) {                                                       \
    ma_decoder_uninit(&decoder);                                               \
    exit(EXIT_FAILURE);                                                        \
  }

#define ERR_EXIT_DEALLOCATE2(x)                                                \
  if (x != MA_SUCCESS) {                                                       \
    ma_device_uninit(&device);                                                 \
    ma_decoder_uninit(&decoder);                                               \
    exit(EXIT_FAILURE);                                                 \
  }

static void data_callback(ma_device *p_device, void *p_output,
                          const void *p_input, ma_uint32 frame_count);
void seek_to_position(ma_uint64 target_frame);
void start_playing_and_wait(void);
void init_audio(void);
void deallocate_audio(void);

#endif // SOUNDS_H
