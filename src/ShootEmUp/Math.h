#pragma once

#include "Settings.h"

/// @brief Structure représentant un vecteur en 2D.
typedef struct Vec2_s
{
    /// @brief La composante x du vecteur/point (abscisse).
    float x;

    /// @brief La composante y du vecteur/point (ordonnée).
    float y;
} Vec2;

extern const Vec2 Vec2_Up;
extern const Vec2 Vec2_Down;
extern const Vec2 Vec2_Left;
extern const Vec2 Vec2_Right;
extern const Vec2 Vec2_Zero;
extern const Vec2 Vec2_One;

/// @brief Construit un vecteur à partir de ses composantes.
/// @param[in] x la composante x.
/// @param[in] y la composante y.
/// @return Le vecteur ayant les composantes données.
Vec2 Vec2_Set(float x, float y);

/// @brief Additionne deux vecteurs.
/// @param[in] v1 le premier vecteur.
/// @param[in] v2 le second vecteur.
/// @return La somme de v1 et v2.
Vec2 Vec2_Add(Vec2 v1, Vec2 v2);

/// @brief Soustrait deux vecteurs.
/// @param[in] v1 le premier vecteur.
/// @param[in] v2 le second vecteur.
/// @return La différence de v1 par v2.
Vec2 Vec2_Sub(Vec2 v1, Vec2 v2);

/// @brief Multiplie un vecteur par un scalaire.
/// @param[in] v le vecteur.
/// @param[in] s le scalaire.
/// @return Le produit de s et v.
Vec2 Vec2_Scale(Vec2 v, float s);

/// @brief Calcule la longueur (norme euclidienne) d'un vecteur.
/// @param[in] v le vecteur.
/// @return La norme euclidienne de v.
float Vec2_Length(Vec2 v);

/// @brief Normalise un vecteur.
/// @param[in] v le vecteur.
/// @return Le vecteur unitaire de même direction.
Vec2 Vec2_Normalize(Vec2 v);

/// @brief Renvoie la distance entre deux points.
/// @param[in] v1 les coordonnées du premier point.
/// @param[in] v2 les coordonnées du second point.
/// @return La distance séparant les deux points.
float Vec2_Distance(Vec2 v1, Vec2 v2);

/// @brief Structure représentant une boîte englobante alignée sur les axes
/// (AABB : Aligned Axis Bounding Box)
typedef struct AABB_s {

    /// @brief Coordonnées du coin inférieur gauche de la boîte.
    Vec2 lower;

    /// @brief Coordonnées du coin supérieur droit de la boîte.
    Vec2 upper;
} AABB;

/// @brief Définit une AABB.
/// @param xLower composante x du coin inférieur gauche.
/// @param yLower composante y du coin inférieur gauche.
/// @param xUpper composante x du coin supérieur droit.
/// @param yUpper composante y du coin supérieur droit.
/// @return La boîte créée.
INLINE AABB AABB_Set(float xLower, float yLower, float xUpper, float yUpper)
{
    AABB aabb = { 0 };
    aabb.lower = Vec2_Set(xLower, yLower);
    aabb.upper = Vec2_Set(xUpper, yUpper);
    return aabb;
}

/// @brief Translate une AABB.
/// @param[in,out] aabb la boîte.
/// @param transform le vecteur de translation.
INLINE void AABB_Translate(AABB *aabb, Vec2 transform)
{
    aabb->lower = Vec2_Add(aabb->lower, transform);
    aabb->upper = Vec2_Add(aabb->upper, transform);
}
