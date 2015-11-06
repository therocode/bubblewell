#pragma once
#include "bubbles.hpp"

class BubbleCollider
{
    public:
        void resolveCollisions(BubbleData bubbleData, const std::vector<glm::vec2>& lastPositions, const std::vector<glm::vec2>& lastVelocities) const;
};
