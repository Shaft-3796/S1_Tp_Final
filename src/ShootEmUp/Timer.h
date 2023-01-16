#pragma once

#include "Settings.h"

/// @brief Structure représentant un chronomètre.
typedef struct Timer_s
{
    /// @brief Temps de départ.
    float startTime;

    /// @brief Temps du dernier appel à Timer_Update().
    float currentTime;

    /// @brief Temps de l'avant dernier appel à Timer_Update().
    float previousTime;

    /// @brief Echelle de temps appliquée.
    /// Si ce membre vaut 0.5f, le temps s'écoule deux fois moins rapidement.
    float scale;

    /// @brief Ecart entre les deux derniers appels à Timer_Update().
    float delta;

    /// @brief Ecart entre les deux derniers appels à Timer_Update()
    /// sans prendre en compte le facteur d'échelle de temps.
    float unscaledDelta;

    /// @brief Ecart de temps maximal du timer.
    float maxDelta;

    /// @brief Temps écoulé entre le lancement du timer et le dernier appel à
    /// Timer_Update().
    float elapsed;

    /// @brief Temps écoulé entre le lancement du timer et le dernier appel à
    /// Timer_Update() sans prendre en compte le facteur d'échelle de temps.
    float unscaledElapsed;
} Timer;

/// @brief Crée un nouveau timer.
/// @return Le timer créé ou NULL en cas d'erreur.
Timer* Timer_New();

/// @brief Détruit un timer préalablement alloué avec Timer_New().
/// @param[in,out] self le timer.
void Timer_Delete(Timer* self);

/// @brief Lance le timer.
/// @param[in,out] self le timer.
void Timer_Start(Timer* self);

/// @brief Met à jour le timer en fonction du temps actuel.
/// Cette fonction est typiquement appelée à chaque tour de la boucle de rendu.
/// @param[in,out] self le timer.
void Timer_Update(Timer* self);

/// @brief Définit l'écart de temps maximal d'un timer.
/// @param self le timer.
/// @param maxDelta l'écart de temps maximal.
INLINE void Timer_SetMaximumDeltaTime(Timer *self, float maxDelta)
{
    self->maxDelta = maxDelta;
}

/// @brief Définit le facteur d'échelle de temps appliquée à un timer.
/// Si l'échelle vaut 0.5f, le temps s'écoule deux fois moins rapidement.
/// @param self le timer.
/// @param scale le facteur d'échelle.
INLINE void Timer_SetTimeScale(Timer *self, float scale)
{
    assert(scale >= 0.0f);
    self->scale = scale;
}

/// @brief Renvoie le facteur d'échelle de temps d'un timer.
/// @param self le timer.
/// @return Le facteur d'échelle de temps d'un timer.
INLINE float Timer_GetTimeScale(Timer *self)
{
    return self->scale;
}

/// @brief Renvoie l'écart de temps (en secondes) entre les deux derniers
/// appels à la fonction Timer_Update().
/// @param[in] self le timer.
/// @return L'écart de temps entre les deux dernières mises à jour.
INLINE float Timer_GetDelta(Timer *self)
{
    return self->delta;
}

/// @brief Renvoie l'écart de temps (en secondes) entre les deux derniers
/// appels à la fonction Timer_Update().
/// Cette méthode en tient pas compte de l'échelle de temps du timer.
/// @param[in] self le timer.
/// @return L'écart de temps entre les deux dernières mises à jour
/// (sans échelle de temps).
INLINE float Timer_GetUnscaledDelta(Timer *self)
{
    return self->unscaledDelta;
}

/// @brief Renvoie l'écart de temps (en secondes) entre le lancement du timer
/// avec Timer_Start() et le dernier appel à Timer_Update().
/// @param[in] self le timer.
/// @return Le nombre de secondes écoulées depuis le lancement du timer et la
/// dernière mise à jour.
INLINE float Timer_GetElapsed(Timer *self)
{
    return self->elapsed;
}

/// @brief Renvoie l'écart de temps (en secondes) entre le lancement du timer
/// avec Timer_Start() et le dernier appel à Timer_Update().
/// Cette méthode en tient pas compte de l'échelle de temps du timer.
/// @param[in] self le timer.
/// @return Le nombre de secondes écoulées depuis le lancement du timer et la
/// dernière mise à jour  (sans échelle de temps).
INLINE float Timer_GetUnscaledElapsed(Timer *self)
{
    return self->unscaledElapsed;
}
