#include "bubblecollider.hpp"
#include <iostream>

void BubbleCollider::resolveCollisions(BubbleData bubbleData, const std::vector<glm::vec2>& lastPositions, const std::vector<glm::vec2>& lastVelocities) const
{
    for(size_t bubbleAIndex = 0; bubbleAIndex < bubbleData.bubbleAmount; bubbleAIndex++)
    {
        glm::vec2 lastPosA = lastPositions[bubbleAIndex];
        glm::vec2 lastVelA = lastVelocities[bubbleAIndex];
        for(size_t bubbleBIndex = bubbleAIndex + 1; bubbleBIndex < bubbleData.bubbleAmount; bubbleBIndex++)
        {
            glm::vec2 lastPosB = lastPositions[bubbleBIndex];
            glm::vec2 lastVelB = lastVelocities[bubbleBIndex];
            //step 1: Check that A travelled far enough to even possibly hit B
            //
            // If the movement vector of A is shorter than the distance of the spheres minus their radiuses, there can be no collision


        }
    }
}
