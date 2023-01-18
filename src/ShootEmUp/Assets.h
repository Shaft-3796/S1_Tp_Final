#pragma once

#include "Settings.h"

/// @brief Structure contenant l'ensemble des assets du jeu.
/// Cela correspond aux ressources utilis�es (textures, musiques, sons...)
typedef struct Assets_s
{
    /// @brief Tableau des diff�rents calques de fond.
    SDL_Texture *layers[3];

    /// @brief Texture du vaisseau du joueur de base.
    SDL_Texture *base_player;

    /// @brief Texture du vaisseau du joueur de base en mouvement.
    SDL_Texture *moving_base_player;

    /// @brief Texture du tir de base du joueur.
    SDL_Texture *base_player_bullets;

    /// @brief Texture du vaisseau ennemi.
    SDL_Texture *fighter;

    /// @brief Texture du tir d'un ennemi.
    SDL_Texture *fighterBullet;

    /* --- Perk --- */
    /// @brief Texture de l'astor
    SDL_Texture *astro;

    /* --- Ui --- */
    /// @brief Barre de vie
    SDL_Texture *lifeBar;

    /* --- Easter egg --- */
    /// @brief Texture du meilleur professeur du monde (en toute objectivité)
    SDL_Texture *bodin;

    /* --- GamePlay --- */
    /// @brief Texture des astéroïdes
    SDL_Texture *asteroid;



} Assets;

/// @brief Cr�e la structure contenant les assets du jeu.
/// @param renderer le moteur de rendu.
/// @return La structure contenant les assets du jeu.
Assets *Assets_New(SDL_Renderer *renderer);

/// @brief D�truit la structure contenant les assets du jeu.
/// @param self les assets.
void Assets_Delete(Assets *self);
