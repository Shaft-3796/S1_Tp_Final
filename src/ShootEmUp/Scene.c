#include "Scene.h"
#include "Perks.h"

Scene *Scene_New(SDL_Renderer *renderer)
{
    Scene *self = (Scene *)calloc(1, sizeof(Scene));
    AssertNew(self);

    self->renderer = renderer;

    self->assets = Assets_New(renderer);
    self->camera = Camera_New(LOGICAL_WIDTH, LOGICAL_HEIGHT);
    self->input = Input_New();
    self->player = Player_New(self);
    self->waveIdx = 0;

    // Background
    SDL_Rect layer1Pos = { 0, 0, LOGICAL_WIDTH, LOGICAL_HEIGHT};
    self->layer1Pos = layer1Pos;
    SDL_Rect layer0Pos = { 0, 0, LOGICAL_WIDTH, LOGICAL_HEIGHT};
    self->layer0Pos = layer0Pos;
    self->backgroundSpeedMultiplier = 1.f;

    return self;
}

void Scene_Delete(Scene *self)
{
    if (!self) return;

    Assets_Delete(self->assets);
    Camera_Delete(self->camera);
    Input_Delete(self->input);
    Player_Delete(self->player);

    for (int i = 0; i < self->enemyCount; i++)
    {
        Enemy_Delete(self->enemies[i]);
        self->enemies[i] = NULL;
    }
    for (int i = 0; i < self->bulletCount; i++)
    {
        Bullet_Delete(self->bullets[i]);
        self->bullets[i] = NULL;
    }

    free(self);
}

void Scene_UpdateLevel(Scene *self)
{
    if (self->enemyCount > 0)
        return;

    if (self->waveIdx == 0)
    {
        Enemy *enemy = Enemy_New(self, ENEMY_FIGHTER, Vec2_Set(15.0f, 4.5f), 10);
        /* TEMP */
        Perk *Perk = Perk_New(self, 1, Vec2_Set(6.0f, 4.5f));
        Scene_AppendPerk(self, Perk);
        Scene_AppendEnemy(self, enemy);
        self->waveIdx++;
    }
}

bool Scene_Update(Scene *self)
{
    Player *player = self->player;

    // Met � jour les entr�es utilisateur
    Input_Update(self->input);

    // Met � jour la positions et les dimensions des calques du background
    int offset = Timer_GetDelta(g_time)*(float)BACKGROUND_1_SPEED_MULTIPLIER*self->backgroundSpeedMultiplier;
    self->layer1Pos.x += offset;
    if(self->layer1Pos.x+self->layer1Pos.w >= BACKGROUND_WIDTH)
    {
        self->layer1Pos.x -= BACKGROUND_PERIOD*2;
    }
    offset = Timer_GetDelta(g_time)*(float)BACKGROUND_0_SPEED_MULTIPLIER*self->backgroundSpeedMultiplier;
    self->layer0Pos.x += offset;
    if(self->layer0Pos.x+self->layer0Pos.w >= BACKGROUND_WIDTH)
    {
        self->layer0Pos.x -= BACKGROUND_PERIOD*2;
    }

    // -------------------------------------------------------------------------
    // Met � jour les tirs

    int i = 0;
    while (i < self->bulletCount)
    {
        Bullet *bullet = self->bullets[i];
        bool removed = false;

        Bullet_Update(bullet);

        bool outOfBounds =
            (bullet->position.x < -5.0f) ||
            (bullet->position.x > 20.0f) ||
            (bullet->position.y < -5.0f) ||
            (bullet->position.y > 20.0f);

        if (outOfBounds)
        {
            // Supprime le tir
            Scene_RemoveBullet(self, i);
            removed = true;
            continue;
        }

        if (bullet->fromPlayer)
        {
            // Teste les collisions avec les ennemis
            for (int j = 0; j < self->enemyCount; j++)
            {
                Enemy *enemy = self->enemies[j];
                float dist = Vec2_Distance(bullet->position, enemy->position);
                if (dist < bullet->radius + enemy->radius)
                {
                    // Inflige des dommages � l'ennemi
                    Enemy_Damage(enemy, 1);

                    // Supprime le tir
                    Scene_RemoveBullet(self, i);
                    removed = true;
                    break;
                }
            }
        }
        else
        {
            // Teste la collision avec le joueur
            float dist = Vec2_Distance(bullet->position, self->player->position);
            if (dist < bullet->radius + player->radius)
            {
                // Inflige des dommages au joueur
                Player_Damage(player, 1);

                // Supprime le tir
                Scene_RemoveBullet(self, i);
                removed = true;
            }
        }

        // Passe au prochain tir
        if (removed == false)
        {
            i++;
        }
    }

    // -------------------------------------------------------------------------
    // Met � jour les ennemis

    i = 0;
    while (i < self->enemyCount)
    {
        Enemy *enemy = self->enemies[i];
        bool removed = false;

        Enemy_Update(enemy);

        if (enemy->state == ENEMY_DEAD)
        {
            // Supprime l'ennemi
            Scene_RemoveEnemy(self, i);
            removed = true;
        }

        // Passe au prochain ennemi
        if (removed == false)
        {
            i++;
        }
    }

    // -------------------------------------------------------------------------
    // Met � jour le joueur

    Player_Update(self->player);

    // -------------------------------------------------------------------------
    // Met � jour les Perk

    i = 0;
    while (i < self->perkCount)
    {
        Perk *perk = self->perk[i];
        bool removed = false;

        Perk_Update(perk);

        // Check for Perk collision with player
        float dist = Vec2_Distance(perk->position, self->player->position);
        if (dist < perk->radius + player->radius)
        {
            // Applique l'effet de la Perk
            Perk_Apply_Effect(perk, self->player);
            Scene_RemovePerk(self, i);
            removed = true;

        }

        // Passe au prochain perk
        if (removed == false)
        {
            i++;
        }
    }

    // -------------------------------------------------------------------------
    // Met � jour le niveau

    Scene_UpdateLevel(self);

    return self->input->quitPressed;
}

void Scene_Render(Scene *self)
{
    // Affichage du fond
    SDL_Renderer *renderer = Scene_GetRenderer(self);
    Assets *assets = Scene_GetAssets(self);
    SDL_RenderCopy(renderer, assets->layers[0], &(self->layer0Pos), NULL);
    SDL_RenderCopy(renderer, assets->layers[1], &(self->layer1Pos), NULL);
    SDL_RenderCopy(renderer, assets->layers[2], &(self->layer1Pos), NULL);
    // SDL_RenderCopy(renderer, assets->layers[0], &selection_l2, NULL);


    // Affichage des bullets
    int bulletCount = self->bulletCount;
    for (int i = 0; i < bulletCount; i++)
    {
        Bullet_Render(self->bullets[i]);
    }

    // Affichage des ennemis
    int enemyCount = self->enemyCount;
    for (int i = 0; i < enemyCount; i++)
    {
        Enemy_Render(self->enemies[i]);
    }

    // Affichage du joueur
    Player_Render(self->player);

    // Affichage des Perk
    int perkCount = self->perkCount;
    for (int i = 0; i < perkCount; i++)
    {
        Perk_Render(self->perk[i]);
    }
}

void Scene_AppendObject(void *object, void **objectArray, int *count, int capacity)
{
    int index = *count;
    if (index >= capacity)
        return;

    if (objectArray[index] != NULL)
    {
        assert(false);
        abort();
    }

    objectArray[index] = object;
    (*count)++;
}

void Scene_AppendEnemy(Scene *self, Enemy *enemy)
{
    Scene_AppendObject(
        enemy,
        (void **)(self->enemies),
        &(self->enemyCount),
        ENEMY_CAPACITY
    );
}

void Scene_AppendBullet(Scene *self, Bullet *bullet)
{
    Scene_AppendObject(
        bullet,
        (void **)(self->bullets),
        &(self->bulletCount),
        BULLET_CAPACITY
    );
}

void Scene_RemoveObject(int index, void **objectArray, int *count)
{
    int lastIndex = *count - 1;
    assert(0 <= index && index < *count);

    if (objectArray[index] == NULL)
    {
        assert(false);
        abort();
    }

    if (index == lastIndex)
    {
        // Supprime le pointeur
        objectArray[index] = NULL;
    }
    else
    {
        // Remplace le pointeur par le dernier du tableau
        objectArray[index] = objectArray[lastIndex];
        objectArray[lastIndex] = NULL;
    }
    (*count)--;
}

void Scene_RemoveEnemy(Scene *self, int index)
{
    Enemy_Delete(self->enemies[index]);
    Scene_RemoveObject(index, (void **)(self->enemies), &(self->enemyCount));
}

void Scene_RemoveBullet(Scene *self, int index)
{
    Bullet_Delete(self->bullets[index]);
    Scene_RemoveObject(index, (void **)(self->bullets), &(self->bulletCount));
}

/* --- Perk --- */
void Scene_AppendPerk(Scene *self, Perk *perk)
{
    Scene_AppendObject(
        perk,
        (void **)(self->perk),
        &(self->perkCount),
        PERKS_CAPACITY
    );
}

void Scene_RemovePerk(Scene *self, int index)
{
    Perk_Delete(self->perk[index]);
    Scene_RemoveObject(index, (void **)(self->perk), &(self->perkCount));
}
