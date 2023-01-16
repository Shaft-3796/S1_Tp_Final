#pragma once

#include "Settings.h"
#include "Math.h"

typedef struct Scene_s Scene;

/// @brief Enumération représentant les états possibles du joueur.
typedef enum PlayerState_e
{
    /// @brief Etat par défaut du joueur.
    PLAYER_FLYING,

    /// @brief Etat du joueur quand il joue l'animation de destruction.
    PLAYER_DYING,

    /// @brief Etat du joueur quand il est mort et que son animation de
    /// destruction est terminée.
    PLAYER_DEAD,
} PlayerState;

/// @brief Structure représentant le joueur.
typedef struct Player_s
{
    /// @brief Scène associée.
    Scene *scene;

    /// @brief Texture utilisée pour le rendu.
    SDL_Texture *texture;

    /// @brief Position du joueur exprimée dans le référentiel monde.
    Vec2 position;

    /// @brief Etat du joueur.
    /// Les valeurs possibles sont définies dans PlayerState.
    int state;

    /// @brief Rayon du joueur exprimé dans le référentiel monde.
    /// Il est utilisé dans le moteur physique pour tester les collisions.
    float radius;
} Player;

/// @brief Crée un nouveau joueur.
/// @param scene la scène.
/// @return Le joueur créé.
Player *Player_New(Scene *scene);

/// @brief Détruit un joueur.
/// @param self le joueur.
void Player_Delete(Player *self);

/// @brief Met à jour le joueur.
/// @param self le joueur.
void Player_Update(Player *self);

/// @brief Dessine le joueur dans le moteur de rendu.
/// @param self le joueur.
void Player_Render(Player *self);

/// @brief Inflige des dommages au joueur.
/// @param self le joueur.
/// @param damage la quantité de dommages (nombre de points de vie à perdre).
void Player_Damage(Player *self, int damage);
