#include "Scene.h"

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
        Enemy *enemy = Enemy_New(self, ENEMY_FIGHTER, Vec2_Set(15.0f, 4.5f));
        Scene_AppendEnemy(self, enemy);
        self->waveIdx++;
    }
}

bool Scene_Update(Scene *self)
{
    Player *player = self->player;

    // Met à jour les entrées utilisateur
    Input_Update(self->input);

    // -------------------------------------------------------------------------
    // Met à jour les tirs

    int i = 0;
    while (i < self->bulletCount)
    {
        Bullet *bullet = self->bullets[i];
        bool removed = false;

        Bullet_Update(bullet);

        bool outOfBounds =
            (bullet->position.x < -1.0f) ||
            (bullet->position.x > 17.0f) ||
            (bullet->position.y < -1.0f) ||
            (bullet->position.y > 10.0f);

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
                    // Inflige des dommages à l'ennemi
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
    // Met à jour les ennemis

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
    // Met à jour le joueur

    Player_Update(self->player);

    // -------------------------------------------------------------------------
    // Met à jour le niveau

    Scene_UpdateLevel(self);

    return self->input->quitPressed;
}

void Scene_Render(Scene *self)
{
    // Affichage du fond
    SDL_Renderer *renderer = Scene_GetRenderer(self);
    Assets *assets = Scene_GetAssets(self);
    SDL_RenderCopy(renderer, assets->layers[0], NULL, NULL);
    SDL_RenderCopy(renderer, assets->layers[1], NULL, NULL);

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
