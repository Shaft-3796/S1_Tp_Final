#pragma once

#include "Settings.h"

/// @brief Structure contenant l'ensemble des assets du jeu.
/// Cela correspond aux ressources utilisées (textures, musiques, sons...)
typedef struct Assets_s
{
    /// @brief Tableau des différents calques de fond.
    SDL_Texture *layers[2];

    /// @brief Texture du vaisseau du joueur.
    //SDL_Texture *player;

    /// @brief Texture du tir du joueur.
    SDL_Texture *playerBullet;

    /// @brief Texture du vaisseau ennemi.
    SDL_Texture *fighter;

    /// @brief Texture du tir d'un ennemi.
    SDL_Texture *fighterBullet;
} Assets;

/// @brief Crée la structure contenant les assets du jeu.
/// @param renderer le moteur de rendu.
/// @return La structure contenant les assets du jeu.
Assets *Assets_New(SDL_Renderer *renderer);

/// @brief Détruit la structure contenant les assets du jeu.
/// @param self les assets.
void Assets_Delete(Assets *self);
