#include <unistd.h>

#include "sounds.h"

static ma_decoder decoder;
static ma_device device;
static ma_uint64 current_frame = 0;

static void data_callback(ma_device *p_device, void *p_output,
                          const void *p_input, ma_uint32 frame_count) {
  (void) p_input;
  (void) p_device;
  ma_decoder_read_pcm_frames(&decoder, p_output, frame_count, &current_frame);
}

void seek_to_position(ma_uint64 target_frame) {
  ma_device_stop(&device);
  ma_decoder_seek_to_pcm_frame(&decoder, target_frame);
  current_frame = target_frame;
  ma_device_start(&device);
}

void start_playing_and_wait(void) {
  ERR_EXIT_DEALLOCATE2(ma_device_start(&device));
}

void init_audio(void) {
  ERR_EXIT(ma_decoder_init_file("./res/Maere.mp3", NULL, &decoder));

  ma_device_config device_config =
      ma_device_config_init(ma_device_type_playback);

  device_config.playback.format = decoder.outputFormat;
  device_config.playback.channels = decoder.outputChannels;
  device_config.sampleRate = decoder.outputSampleRate;
  device_config.dataCallback = data_callback;

  ERR_EXIT_DEALLOCATE1(ma_device_init(NULL, &device_config, &device));
}

void deallocate_audio(void) {
  ma_device_uninit(&device);
  ma_decoder_uninit(&decoder);
}
