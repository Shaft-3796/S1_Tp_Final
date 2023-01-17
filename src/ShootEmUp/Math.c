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
    Vec2 ret = { .x = v1.x + v2.x, .y = v1.y + v2.y };
    return ret;
}

Vec2 Vec2_Sub(Vec2 v1, Vec2 v2)
{
    Vec2 ret = { .x = v1.x - v2.x, .y = v1.y - v2.y };
    return ret;
}

Vec2 Vec2_Scale(Vec2 v, float s)
{
    Vec2 ret = { .x = v.x * s, .y = v.y * s };
    return ret;
}

float Vec2_Length(Vec2 v)
{
    float ret = sqrtf(v.x * v.x + v.y * v.y);
    return ret;
}

Vec2 Vec2_Normalize(Vec2 v)
{
    Vec2 ret = Vec2_Scale(v, 1.0f / Vec2_Length(v));
    return ret;
}

float Vec2_Distance(Vec2 v1, Vec2 v2)
{
    Vec2 delta = Vec2_Sub(v1, v2);
    float ret = Vec2_Length(delta);
    return ret;
}
