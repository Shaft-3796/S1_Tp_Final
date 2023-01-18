#pragma once

#include "Settings.h"
#include "Common.h"

#include "Assets.h"
#include "Camera.h"
#include "MenuInput.h"
#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"
#include "Perks.h"

/// @brief Structure repr�sentant la sc�ne principale du jeu (niveau).
typedef struct MenuScene_s
{
    /// @brief Moteur de rendu.
    SDL_Renderer *renderer;

    /// @brief Assets de la sc�ne (textures, musiques, sons...)
    Assets *assets;

    /// @brief Cam�ra par laquelle est vue la sc�ne.
    Camera *camera;

    /// @brief Entr�e utilisateur.
    MenuInput *input;


    /* --- Background rendering --- */
    /// @brief Position du calque de fond.
    SDL_Rect layer0Pos;

    /// @brief Position du calque de fond.
    SDL_Rect layer1Pos;

} MenuScene;

/// @brief Cr�e la sc�ne principale du jeu.
/// @param renderer moteur de rendu.
/// @return La sc�ne cr��e.
MenuScene *MenuScene_New(SDL_Renderer *renderer);

/// @brief D�truit la sc�ne principale.
/// @param self la sc�ne.
void MenuScene_Delete(MenuScene *self);

/// @brief Met � jour la sc�ne.
/// Cette fonction est appel�e � chaque tour de la boucle de rendu.
/// @param self la sc�ne.
/// @return true s'il faut quitter la boucle de rendu, false sinon.
bool MenuScene_Update(MenuScene *self);

/// @brief Dessine la sc�ne dans le moteur de rendu.
/// @param self la sc�ne.
void MenuScene_Render(MenuScene *self);

/// @brief Renvoie le moteur de rendu de la sc�ne.
/// @param self la sc�ne.
/// @return Le moteur de rendu de la sc�ne.
INLINE SDL_Renderer *MenuScene_GetRenderer(MenuScene *self)
{
    return self->renderer;
}

/// @brief Renvoie les assets de la sc�ne.
/// @param self la sc�ne.
/// @return Les assets de la sc�ne.
INLINE Assets *MenuScene_GetAssets(MenuScene *self)
{
    return self->assets;
}

/// @brief Renvoie la cam�ra de la sc�ne.
/// @param self la sc�ne.
/// @return La cam�ra de la sc�ne.
INLINE Camera *MenuScene_GetCamera(MenuScene *self)
{
    return self->camera;
}

/// @brief Renvoie les entr�e utilisateur de la sc�ne.
/// @param self la sc�ne.
/// @return Les entr�e utilisateur de la sc�ne.
INLINE MenuInput *MenuScene_GetInput(MenuScene *self)
{
    return self->input;
}
