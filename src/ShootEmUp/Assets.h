#pragma once

#include "Settings.h"

/// @brief Structure contenant l'ensemble des assets du jeu.
/// Cela correspond aux ressources utilis�es (textures, musiques, sons...)
typedef struct Assets_s
{
    /// @brief Tableau des diff�rents calques de fond.
    SDL_Texture *layers[4];

    /// @brief Texture du vaisseau du joueur de base.
    SDL_Texture *base_player;

    /// @brief Texture du vaisseau du joueur de base en mouvement.
    SDL_Texture *moving_base_player;

    /// @brief Texture du vaisseau du joueur de base en mouvement frame 2.
    SDL_Texture *moving_base_player_2;

    /// @brief Texture du tir de base du joueur.
    SDL_Texture *base_player_bullets;
    SDL_Texture *base_player_bullets_corrupted;

    /* --- Enemies --- */
    /// @brief Texture du vaisseau ennemi.
    SDL_Texture *fighter;
    SDL_Texture *fighterBullet;
    SDL_Texture *base_enemy;
    SDL_Texture *revert_enemy;
    SDL_Texture *auto_enemy;
    SDL_Texture *bomb_enemy;
    SDL_Texture *sin_enemy;
    SDL_Texture *teleport_enemy;
    SDL_Texture *rafale_enemy;
    SDL_Texture *triangle_enemy;

    /* --- Bullets --- */
    SDL_Texture *base_enemy_bullet;
    SDL_Texture *sin_enemy_rocket;
    SDL_Texture *arc_enemy_bullet;
    SDL_Texture *auto_bullet;
    SDL_Texture *boss1;
    SDL_Texture *boss2;
    SDL_Texture *bomb;

    /* --- Perk --- */
    /// @brief Texture de l'astor
    SDL_Texture *astro;
    SDL_Texture *shield;
    SDL_Texture *shield_render;
    SDL_Texture *lifeup;
    SDL_Texture *powershoot;

    /* --- Ui --- */
    /// @brief Barre de vie
    SDL_Texture *player_life_bar_frame;
    SDL_Texture *player_life_bar_content;
    SDL_Texture *enemy_life_bar_frame;
    SDL_Texture *enemy_life_bar_content;
    SDL_Texture *waves;


    /* --- Easter egg --- */
    /// @brief Texture du meilleur professeur du monde (en toute objectivité)
    SDL_Texture *bodin;

    /* --- GamePlay --- */
    /// @brief Texture des astéroïdes
    SDL_Texture *asteroid;

    /* --- Scenes --- */
    /// @brief Texture du menu
    SDL_Texture *menu;
    SDL_Texture *death;
    SDL_Texture *black_hole;
    SDL_Texture *game_over_layer;



} Assets;

/// @brief Cr�e la structure contenant les assets du jeu.
/// @param renderer le moteur de rendu.
/// @return La structure contenant les assets du jeu.
Assets *Assets_New(SDL_Renderer *renderer);

/// @brief D�truit la structure contenant les assets du jeu.
/// @param self les assets.
void Assets_Delete(Assets *self);
