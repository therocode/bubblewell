#pragma once
#include "glm.hpp"
#include <fea/render2d.hpp>

struct Bubble
{
    glm::vec2 position;
    glm::vec2 velocity;
    float radius;
    fea::Color color;
    bool staticBody;
};
