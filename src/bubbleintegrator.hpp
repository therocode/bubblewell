#pragma once
#include "bubbles.hpp"

class BubbleIntegrator
{
    public:
        void integrate(BubbleData bubbleData) const;
        void setGravityPoint(const glm::vec2& position);
    private:
        glm::vec2 mGravityPoint;
};
