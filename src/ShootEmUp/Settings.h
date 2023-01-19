#pragma once

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//#define FHD
//#define FULLSCREEN

#define PIX_TO_WORLD (1.0f / 48.0f)

#ifdef _WIN32
#  include "SDL.h"
#  include "SDL_image.h"
//#  include "SDL_ttf.h"
//#  include "SDL_mixer.h"
#else
#  include <SDL2/SDL.h>
#  include <SDL2/SDL_image.h>
//#  include <SDL2/SDL_ttf.h>
//#  include <SDL2/SDL_mixer.h>
#endif

#ifdef _WIN32
#  define INLINE inline
#else
#  define INLINE static inline
#endif

#define AssertNew(ptr) { if (ptr == NULL) { assert(false); abort(); } }

#define HD_WIDTH 1280
#define HD_HEIGHT 720

#define FHD_WIDTH 1920
#define FHD_HEIGHT 1080

#define QHD_WIDTH 2560
#define QHD_HEIGHT 1440


#ifdef FHD
#  define WINDOW_WIDTH   FHD_WIDTH
#  define WINDOW_HEIGHT  FHD_HEIGHT
#  define LOGICAL_WIDTH  FHD_WIDTH
#  define LOGICAL_HEIGHT FHD_HEIGHT
#else
#  define WINDOW_WIDTH   FHD_WIDTH
#  define WINDOW_HEIGHT  FHD_HEIGHT
#  define LOGICAL_WIDTH  FHD_WIDTH
#  define LOGICAL_HEIGHT FHD_HEIGHT
#endif


/* --- Custom settings --- */
#define BASE_PLAYER_SPEED_MULTIPLIER 4.f
#define PLAYER_SIZE_MULTIPLIER 75.f

/* --- Perks --- */
#define PERKS_SIZE_MULTIPLIER 75.f
#define PERKS_ROTATION_SPEED 0.01f // in seconds
#define ASTRO_SPEED_MULTIPLIER 1.5f
#define ASTRO_BUFF_DURATION 5.f // in seconds
#define SHIELD_BUFF_DURATION 5.f // in seconds
#define LIFEUP_PV_BUFF 3

#define LIFEUP_RESPAWN_TIME_MAX 25
#define LIFEUP_RESPAWN_TIME_MIN 10
#define SHIELD_RESPAWN_TIME_MAX 25
#define SHIELD_RESPAWN_TIME_MIN 10
#define ASTRO_RESPAWN_TIME_MAX 25
#define ASTRO_RESPAWN_TIME_MIN 10
#define powershoot_RESPAWN_TIME_MAX 25
#define powershoot_RESPAWN_TIME_MIN 10

/* --- Background --- */
#define BACKGROUND_WIDTH 7680
#define BACKGROUND_PERIOD 1920
#define BACKGROUND_0_SPEED_MULTIPLIER 250 // in pixels per second
#define BACKGROUND_1_SPEED_MULTIPLIER 500 // in pixels per second

/* --- UI --- */
#define LIFE_BAR_SIZE_MULTIPLIER 100.f

/* --- Formats for animations --- */
#define PLAYER_MOVING_ANIMATION_PERIOD 64 // in pixels
#define PLAYER_MOVING_ANIMATION_HEIGHT 64 // in pixels
#define PLAYER_MOVING_ANIMATION_FRAMES 2 // number of frames
#define PLAYER_MOVING_ANIMATION_DURATION 0.1f // in seconds

/* --- Enemies --- */
#define ENEMY_SIZE_MULTIPLIER 75.f

/* --- Gameplay --- */
#define ASTEROID_SPEED_MULTIPLIER 4.f
#define ASTEROID_SIZE_MULTIPLIER 25.f

/* --- Bullets --- */
#define BULLET_SIZE_MULTIPLIER 75.f