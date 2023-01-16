#pragma once

#include "Settings.h"
#include "Common.h"

#include "Assets.h"
#include "Camera.h"
#include "Input.h"
#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"

// Nombre maximal d'ennemis actifs dans un niveau.
#define ENEMY_CAPACITY 32

// Nombre maximal de projectiles actifs dans un niveau.
#define BULLET_CAPACITY 256

/// @brief Structure représentant la scène principale du jeu (niveau).
typedef struct Scene_s
{
    /// @brief Moteur de rendu.
    SDL_Renderer *renderer;

    /// @brief Assets de la scène (textures, musiques, sons...)
    Assets *assets;

    /// @brief Caméra par laquelle est vue la scène.
    Camera *camera;

    /// @brief Entrée utilisateur.
    Input *input;

    /// @brief Joueur principal.
    Player *player;

    /// @brief Tableau contenant les ennemis courrants.
    Enemy *enemies[ENEMY_CAPACITY];

    /// @brief Nombre d'ennemis courrants.
    int enemyCount;

    /// @brief Tableau contenant les projectiles courrants.
    Bullet *bullets[BULLET_CAPACITY];

    /// @brief Nombre de projectiles courrants.
    int bulletCount;

    /// @brief Indice de la vague d'ennemis courrante.
    /// Utilisé pour implémenter un niveau complet.
    int waveIdx;
} Scene;

/// @brief Crée la scène principale du jeu.
/// @param renderer moteur de rendu.
/// @return La scène créée.
Scene *Scene_New(SDL_Renderer *renderer);

/// @brief Détruit la scène principale.
/// @param self la scène.
void Scene_Delete(Scene *self);

/// @brief Met à jour la scène.
/// Cette fonction est appelée à chaque tour de la boucle de rendu.
/// @param self la scène.
/// @return true s'il faut quitter la boucle de rendu, false sinon.
bool Scene_Update(Scene *self);

/// @brief Dessine la scène dans le moteur de rendu.
/// @param self la scène.
void Scene_Render(Scene *self);

/// @brief Ajoute un nouveau projectile à la scène.
/// @param self la scène.
/// @param bullet le projectile à ajouter (correctement initialisé).
void Scene_AppendBullet(Scene *self, Bullet *bullet);

/// @brief Supprime un projectile de la scène.
/// @param self la scène.
/// @param index l'indice du projectile à supprimer dans le tableau self->bullets.
void Scene_RemoveBullet(Scene *self, int index);

/// @brief Ajoute un nouvel ennemi à la scène.
/// @param self la scène.
/// @param enemy l'ennemi à ajouter (correctement initialisé).
void Scene_AppendEnemy(Scene *self, Enemy *enemy);

/// @brief Supprime un ennemi de la scène.
/// @param self la scène.
/// @param index l'indice du l'ennemi à supprimer dans le tableau self->enemies.
void Scene_RemoveEnemy(Scene *self, int index);

/// @brief Renvoie le moteur de rendu de la scène.
/// @param self la scène.
/// @return Le moteur de rendu de la scène.
INLINE SDL_Renderer *Scene_GetRenderer(Scene *self)
{
    return self->renderer;
}

/// @brief Renvoie les assets de la scène.
/// @param self la scène.
/// @return Les assets de la scène.
INLINE Assets *Scene_GetAssets(Scene *self)
{
    return self->assets;
}

/// @brief Renvoie la caméra de la scène.
/// @param self la scène.
/// @return La caméra de la scène.
INLINE Camera *Scene_GetCamera(Scene *self)
{
    return self->camera;
}

/// @brief Renvoie les entrée utilisateur de la scène.
/// @param self la scène.
/// @return Les entrée utilisateur de la scène.
INLINE Input *Scene_GetInput(Scene *self)
{
    return self->input;
}
