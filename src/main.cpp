#ifdef __WIN32
#include <windows.h>
#endif
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <fstream>
#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "world.h"
#include "keyboard.h"
#include "camera.h"
#include "log.h"
#include "player.h"
#include "timer.h"
#include "colbox.h"
#include "object.h"
#include "platform.h"
#include "sound_handler.h"

#include <iostream>
#include <future>
#include <chrono>
#include <thread>

using namespace std;

void funcionAsincrona() {
  std::cout << "Función ejecutada de manera asíncrona" << std::endl;
}

int main(int argc, char *argv[]) {
  // Allegro variables
  ALLEGRO_DISPLAY*       display     = NULL;
  ALLEGRO_EVENT_QUEUE*   event_queue = NULL;
  ALLEGRO_MOUSE_STATE    mouse_state;
  World*                 map_level1;
  Player*                player;
  Keyboard               keyboard;
  Camera                 camera;
  Timer                  timer;
  SoundHandler           sound_handler;


  // Check arguments
  if(argc != 1) {
    fprintf(stderr, "Error: wrong parameters. Usage: XXXX\n");
    exit(-1);
  }

  // allegro initializations
  if(!al_init()) {
    fprintf(stderr, "Error: failed to initialize allegro!\n");
    return -1;
  }

  if(!al_install_keyboard()) {
    fprintf(stderr, "Error: failed to initialize keyboard!\n");
    return -1;
  }

  if(!al_install_mouse()) {
    fprintf(stderr, "Error: failed to initialize keyboard!\n");
    return -1;
  }

  al_set_new_display_flags(ALLEGRO_WINDOWED);
  display = al_create_display(SCREEN_X, SCREEN_Y);
  if(!display) {
    fprintf(stderr, "Error: failed to create display!\n");
    return -1;
  }

  if(!al_init_image_addon()) {
    fprintf(stderr, "Error: failed to load image addon!\n");
    return -1;
  }

  if(!al_init_primitives_addon()) {
    fprintf(stderr, "Error: failed to initialize allegro primitives!\n");
    return -1;
  }

  al_init_font_addon();       // initialize the font addon
  al_init_ttf_addon();        // initialize the ttf (True Type Font) addon

  ALLEGRO_FONT *font = al_load_ttf_font("../fonts/verdana.ttf", 8,0 );

  if (!font) {
    fprintf(stderr, "Error: Could not load 'pirulen.ttf'\n");
    return -1;
  }

  if(!al_install_audio()) {
    fprintf(stderr, "Error: failed to initialize audio!\n");
    return -1;
  }

  if(!al_init_acodec_addon()) {
    fprintf(stderr, "Error: failed to initialize audio codecs!\n");
    return -1;
  }

  if(!al_reserve_samples(16)) {  // REVISIT: define this as a param?
    fprintf(stderr, "Error: failed to reserve samples!\n");
    return -1;
  }

  event_queue = al_create_event_queue();
  if(!event_queue) {
    fprintf(stderr, "Error: failted to create event_queue!\n");
    return -1;
  }

  al_register_event_source(event_queue, al_get_keyboard_event_source());

  // Game initializations  
  map_level1 = new World("../maps/level1_jump/Map_vertical_16x16.json", &sound_handler, false);
  camera.InitCamera(0, 0, CAMERA_X, CAMERA_Y, map_level1, display);
  player = new Player(map_level1, "../characters/rick.xml");
  player->RegisterCamera(&camera);
  player->RegisterSoundHandler(&sound_handler);

  // Start counter for first iteration
  timer.StartCounter();

  // Initialize sounds and start playing music for level 1 (the only implemented at this moment)
  sound_handler.InitializeSounds();
  sound_handler.PlayMusic(0);



  using namespace std::chrono;
  auto start = steady_clock::now();
  bool actionTriggered = false;


  // Main loop
  bool exit = false;
  do {
    keyboard.ReadKeyboard(event_queue);
    
    // REVISIT: added mouse to combine creation with main game
    al_get_mouse_state(&mouse_state);
    if (mouse_state.buttons & 1) jump_log("Mouse coord x = %d, y = %d\n", camera.GetPosX() + mouse_state.x/2, camera.GetPosY() + mouse_state.y/2);

    if(keyboard.PressedESC()) exit = true;
    if(keyboard.PressedK()) player->SetKilled(map_level1);

    // Perform an step of all elements belonging to the world level
    map_level1->WorldStep(player);

    // Handle player
    player->CharacterStep(map_level1, keyboard);

    camera.CameraStep(map_level1, player, font);

    // Check counter value for adding waiting time
    double delay = timer.GetCounter();

    if(delay < 20) {
#ifdef __WIN32
      Sleep(20 - delay);
#else
      sleep(0.00002 - delay);
#endif
    }

    // Move bitmap into display
    al_set_target_bitmap(al_get_backbuffer(display));
    al_flip_display();

    // Start counter again for next iteration
    timer.StartCounter();
  } while(!exit);

  al_destroy_display(display);

  delete(player);
  delete(map_level1);

  return 0;
}

