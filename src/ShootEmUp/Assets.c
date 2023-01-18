#include "Assets.h"

typedef struct TextureSpec_s
{
    SDL_Texture **ptr;
    char *path;
} TextureSpec;

Assets *Assets_New(SDL_Renderer *renderer)
{
    Assets *self = (Assets *)calloc(1, sizeof(Assets));
    AssertNew(self);

    // -------------------------------------------------------------------------
    // Chargement des textures

    TextureSpec texSpecs[] = {
        { &self->layers[0],     "../Assets/Background/layer_00_wide.png"   },
        { &self->layers[1],     "../Assets/Background/layer_01_wide.png"   },
        { &self->layers[2],     "../Assets/Background/layer_02_wide.png"   },
        { &self->base_player_bullets,  "../Assets/Player/BaseBullets.png" },
        { &self->fighter,       "../Assets/Enemy/fighter.png"         },
        { &self->fighterBullet, "../Assets/Enemy/fighter_bullet.png"  },
        { &self->base_enemy, "../Assets/Enemy/BaseEnemy.png"  },
        { &self->base_enemy_bullet, "../Assets/Enemy/BaseEnemyBullet.png"  },
        { &self->base_player, "../Assets/Player/BasePlayer.png"  },
        { &self->moving_base_player, "../Assets/Player/MovingBasePlayer.png"  },
        { &self->astro, "../Assets/Perks/Perk_Astro.png"  },
        { &self->lifeBar, "../Assets/UI/LifeBar.png"  },
        { &self->bodin, "../Assets/Player/bodin.png"  },
        { &self->asteroid, "../Assets/Gameplay/Asteroid.png"  },
        {&self->menu, "../Assets/Menu/MenuLayer.png"}
    };
    int texSpecCount = sizeof(texSpecs) / sizeof(TextureSpec);

    for (int i = 0; i < texSpecCount; i++)
    {
        SDL_Texture **texPtr = texSpecs[i].ptr;
        char *path = texSpecs[i].path;

        *texPtr = IMG_LoadTexture(renderer, path);
        if (*texPtr == NULL)
        {
            printf("ERROR - Loading texture %s\n", path);
            printf("      - %s\n", SDL_GetError());
            assert(false);
            abort();
        }
    }

    return self;
}

void Assets_Delete(Assets *self)
{
    if (!self) return;

    // -------------------------------------------------------------------------
    // Lib�re les textures

    SDL_Texture **texPointers[] = {
        &self->layers[0],
        &self->layers[1],
        &self->base_player_bullets,
        &self->fighter,
        &self->fighterBullet,
        &self->base_player,
        &self->moving_base_player,
    };
    int count = sizeof(texPointers) / sizeof(SDL_Texture **);

    for (int i = 0; i < count; i++)
    {
        if (*texPointers[i])
            SDL_DestroyTexture(*(texPointers[i]));
    }

    free(self);
}