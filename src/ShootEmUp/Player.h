#pragma once

#include "Settings.h"
#include "Math.h"

typedef struct Scene_s Scene;

/// @brief Enum�ration repr�sentant les �tats possibles du joueur.
typedef enum PlayerState_e
{
    /// @brief Etat par d�faut du joueur.
    PLAYER_FLYING,

    /// @brief Etat du joueur quand il joue l'animation de destruction.
    PLAYER_DYING,

    /// @brief Etat du joueur quand il est mort et que son animation de
    /// destruction est termin�e.
    PLAYER_DEAD,
} PlayerState;

/// @brief Structure repr�sentant le joueur.
typedef struct Player_s
{
    /// @brief Sc�ne associ�e.
    Scene *scene;

    /// @brief Texture utilis�e pour le rendu.
    SDL_Texture *texture;

    /// @brief Position du joueur exprim�e dans le r�f�rentiel monde.
    Vec2 position;

    /// @brief Etat du joueur.
    /// Les valeurs possibles sont d�finies dans PlayerState.
    int state;

    /// @brief Rayon du joueur exprim� dans le r�f�rentiel monde.
    /// Il est utilis� dans le moteur physique pour tester les collisions.
    float radius;

    /// @brief Vitesse du joueur exprim�e dans le r�f�rentiel monde.
    int speed;

    ///@brief vie du joueur
    int life;
    ///@brief vie max du joueur
    int max_life;

    /* --- Perks --- */
    /// @brief Perk Astro active.
    bool perk_astro;

    /// @brief Temps écoulé depuis le début de l'effet de la Perk Astro.
    float perk_astro_timer;

    /// @brief Perk Shield active.
    bool perk_shield;

    /// @brief Temps écoulé depuis le début de l'effet de la Perk Shield.
    float perk_shield_timer;

    /// @brief Rayon du bouclié.
    float shield_radius;

    /// @brief True si le prochain tir sera un power tir
    bool power_shoot;


    /* --- Animation --- */
    /// @brief Temps �coul� depuis le dernier changement de frame de l'animation.
    float animation_timer;
    int animation_frame;
    bool animating;

} Player;

/// @brief Cr�e un nouveau joueur.
/// @param scene la sc�ne.
/// @return Le joueur cr��.
Player *Player_New(Scene *scene);

/// @brief D�truit un joueur.
/// @param self le joueur.
void Player_Delete(Player *self);

/// @brief Met � jour le joueur.
/// @param self le joueur.
void Player_Update(Player *self);

/// @brief Dessine le joueur dans le moteur de rendu.
/// @param self le joueur.
void Player_Render(Player *self);

/// @brief Inflige des dommages au joueur.
/// @param self le joueur.
/// @param damage la quantit� de dommages (nombre de points de vie � perdre).
void Player_Damage(Player *self, int damage);
