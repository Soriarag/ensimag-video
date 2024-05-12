#include <SDL2/SDL.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <threads.h>

#include "oggstream.h"
#include "stream_common.h"

int main(int argc, char *argv[]) {

  int res;
  thrd_t theora_pid, vorbis_pid;
  if (argc != 2) {
    fprintf(stderr, "Usage: %s FILE", argv[0]);
    exit(EXIT_FAILURE);
  }
  assert(argc == 2);

  // Initialisation de la SDL
  res = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS);
  atexit(SDL_Quit);
  assert(res == 0);

  // Your code HERE
  // start the two stream readers (theoraStreamReader and vorbisStreamReader)
  // each in a thread
  
  thrd_create(&theora_pid, theoraStreamReader, argv[0]);
  thrd_create(&vorbis_pid, vorbisStreamReader, argv[0]);

  // wait for vorbis thread

  thrd_join(vorbis_pid, NULL);
  // 1 seconde of sound in advance, thus wait 1 seconde
  // before leaving
  sleep(1);

  // Wait for theora and theora2sdl threads

  // TODO
  /* liberer des choses ? */

  exit(EXIT_SUCCESS);
}
