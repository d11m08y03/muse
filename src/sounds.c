#include <ncurses.h>
#include <string.h>
#include <unistd.h>

#include "miniaudio.h"
#include "sounds.h"

ma_decoder decoder;
ma_device device;
ma_uint64 current_frame = 0;

void data_callback(ma_device *p_device, void *p_output, const void *p_input,
                   ma_uint32 frame_count) {
  (void)p_input;
  (void)p_device;
  ma_decoder_read_pcm_frames(&decoder, p_output, frame_count, &current_frame);
}

void seek_to_position(ma_uint64 target_frame) {
  ma_uint64 frame_count = (ma_uint64)(target_frame * decoder.outputSampleRate);
  ma_device_stop(&device);
  ma_decoder_seek_to_pcm_frame(&decoder, frame_count);
  current_frame = target_frame;
  ma_device_start(&device);
}

void start_playing_and_wait(void) {
  ERR_EXIT_DEALLOCATE2(ma_device_start(&device));
}

void testbed(Timestamp *timestamps, size_t size) {
  (void)size;
  size_t curr_song = 0;

  start_playing_and_wait();

  WINDOW *window = initscr();
  keypad(window, TRUE);
  nodelay(window, TRUE);
  wclear(window);
  noecho();

  int rows, cols;
  getmaxyx(window, rows, cols);

  while (TRUE) {
    int key = wgetch(window);
    if (key == KEY_DOWN) {
      break;
    } else if (key == KEY_RIGHT) {
      curr_song = curr_song + 1 > size - 1 ? 0 : curr_song + 1;
      seek_to_position((ma_uint64)timestamps[curr_song].seconds);
    } else if (key == KEY_LEFT) {
      curr_song = curr_song - 1 < 0 ? size - 1 : curr_song - 1;
      seek_to_position((ma_uint64)timestamps[curr_song].seconds);
    }

    // Displays song title
    int title_y_pos = (cols - strlen(timestamps[curr_song].title)) / 2;
    mvprintw(rows / 2, title_y_pos, "%s", timestamps[curr_song].title);
  }

  endwin();
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
