#include "Camera.h"

Camera *Camera_New(int width, int height)
{
    Camera *self = (Camera *)calloc(1, sizeof(Camera));
    AssertNew(self);

    float worldW = 16.0f;
    float worldH = 9.0f;

    self->m_width = width;
    self->m_height = height;
    self->m_worldView = AABB_Set(0.0f, 0.0f, worldW, worldH);

    return self;
}

void Camera_Delete(Camera *self)
{
    if (!self) return;
    free(self);
}

void Camera_WorldToView(Camera *self, Vec2 position, float *x, float *y)
{
    float w = self->m_worldView.upper.x - self->m_worldView.lower.x;
    float h = self->m_worldView.upper.y - self->m_worldView.lower.y;
    float xScale = (float)self->m_width  / w;
    float yScale = (float)self->m_height / h;
    *x = (position.x - self->m_worldView.lower.x) * xScale;
    *y = (position.y - self->m_worldView.lower.y) * yScale;
    *y = (float)self->m_height - *y;
}

void Camera_ViewToWorld(Camera *self, float x, float y, Vec2 *position)
{
    y = self->m_height - y;
    float ratioX = (float)x / (float)self->m_width;
    float ratioY = (float)y / (float)self->m_height;
    float w = self->m_worldView.upper.x - self->m_worldView.lower.x;
    float h = self->m_worldView.upper.y - self->m_worldView.lower.y;
    position->x = self->m_worldView.lower.x + ratioX * w;
    position->y = self->m_worldView.lower.y + ratioY * h;
}

void Camera_TranslateWorldView(Camera *self, Vec2 displacement)
{
    AABB_Translate(&self->m_worldView, displacement);
}

int Camera_GetWidth(Camera *self)
{
    return self->m_width;
}

int Camera_GetHeight(Camera *self)
{
    return self->m_height;
}

float Camera_GetWorldToViewScale(Camera *self)
{
    float w = self->m_worldView.upper.x - self->m_worldView.lower.x;
    return (float)self->m_width / w;
}