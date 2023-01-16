#include "Math.h"

const Vec2 Vec2_Up    = {  0.0f,  1.0f };
const Vec2 Vec2_Down  = {  0.0f, -1.0f };
const Vec2 Vec2_Left  = { -1.0f,  0.0f };
const Vec2 Vec2_Right = {  1.0f,  0.0f };
const Vec2 Vec2_Zero  = {  0.0f,  0.0f };
const Vec2 Vec2_One   = {  1.0f,  1.0f };

Vec2 Vec2_Set(float x, float y)
{
    Vec2 v = { .x = x, .y = y };
    return v;
}

Vec2 Vec2_Add(Vec2 v1, Vec2 v2)
{
    // TODO
    return Vec2_Zero;
}

Vec2 Vec2_Sub(Vec2 v1, Vec2 v2)
{
    // TODO
    return Vec2_Zero;
}

Vec2 Vec2_Scale(Vec2 v, float s)
{
    // TODO
    return Vec2_Zero;
}

float Vec2_Length(Vec2 v)
{
    // TODO
    return 0.0f;
}

Vec2 Vec2_Normalize(Vec2 v)
{
    // TODO
    return Vec2_Zero;
}

float Vec2_Distance(Vec2 v1, Vec2 v2)
{
    // TODO
    return 0.0f;
}
