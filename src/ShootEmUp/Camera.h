#pragma once

#include "Settings.h"
#include "Math.h"

/// @brief Structure représentant une caméra.
typedef struct Camera_s
{
    /// @brief Rectangle représentant la vue de la caméra.
    /// Ces coordonnées sont dans le référentiel monde.
    AABB m_worldView;

    /// @brief Largeur (en pixels) du référentiel vue de la caméra.
    int m_width;

    /// @brief Hauteur (en pixels) du référentiel vue de la caméra.
    int m_height;
} Camera;

/// @brief Crée une nouvelle caméra.
/// @param width largeur en pixels de la caméra.
/// @param height hauteur en pixels de la caméra.
/// @return La caméra créée.
Camera *Camera_New(int width, int height);

/// @brief Détruit une caméra.
/// @param self la caméra.
void Camera_Delete(Camera *self);

/// @brief Renvoie le rectangle vu par la caméra.
/// Les coordonnées sont exprimées dans le référentiel monde.
/// @param self la caméra.
/// @return Le rectangle vu par la caméra.
INLINE AABB Camera_GetWorldView(Camera *self)
{
    return self->m_worldView;
}

/// @brief Définit le rectangle vu par la caméra.
/// Les coordonnées sont exprimées dans le référentiel monde.
/// @param self la caméra.
/// @param worldView le rectangle.
INLINE void Camera_SetWorldView(Camera *self, AABB worldView)
{
    self->m_worldView = worldView;
}

/// @brief Déplace le rectangle vu par la caméra.
/// Les coordonnées sont exprimées dans le référentiel monde.
/// @param self la caméra.
/// @param displacement le vecteur de translation (dans le référentiel monde).
void Camera_TranslateWorldView(Camera *self, Vec2 displacement);

/// @brief Renvoie la largeur en pixels de la caméra.
/// @param self la caméra.
/// @return La largeur en pixels de la caméra.
int Camera_GetWidth(Camera *self);

/// @brief Renvoie la hauteur en pixels de la caméra.
/// @param self la caméra.
/// @return La hauteur en pixels de la caméra.
int Camera_GetHeight(Camera *self);

/// @brief Renvoie le facteur d'échelle par lequel il faut multiplier des
/// distances exprimées dans le reférentiel monde pour obtenir des distances
/// exprimées dans le référentiel vue (en pixels).
/// @param self la caméra.
/// @return Le facteur d'échelle monde vers vue (en pixels).
float Camera_GetWorldToViewScale(Camera *self);

/// @brief Transforme des coordonnées exprimées dans le référentiel monde vers
/// le référentiel vue (en pixels).
/// @param[in] self la caméra.
/// @param[in] position la position d'un point dans le référentiel monde.
/// @param[out] x l'abscisse du point dans la vue (en pixels).
/// @param[out] y l'ordonnée du point dans la vue (en pixels).
void Camera_WorldToView(Camera *self, Vec2 position, float *x, float *y);

/// @brief Transforme des coordonnées exprimée dans le référentiel de la vue
/// (en pixels) vers le référentiel monde.
/// @param[in] self camera la caméra.
/// @param[in] x l'abscisse d'un point dans le référentiel vue (en pixels).
/// @param[in] y l'ordonnée d'un point dans le référentiel vue (en pixels).
/// @param[out] position la position du point dans le référentiel monde.
void Camera_ViewToWorld(Camera *self, float x, float y, Vec2 *position);
