#pragma once

#include "Settings.h"
#include "Timer.h"

/// @brief Initialise les librairies utilisées par le jeu.
/// @param sdlFlags les flags pour la SDL.
/// @param imgFlags les flags pour la SDL Image.
void Game_Init(int sdlFlags, int imgFlags);

/// @brief Quitte les librairies utilisées par le jeu.
void Game_Quit();

/// @brief Temps global du jeu.
extern Timer *g_time;
