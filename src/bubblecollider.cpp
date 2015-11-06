#include "bubblecollider.hpp"
#include <iostream>

void BubbleCollider::resolveCollisions(BubbleData bubbleData, const std::vector<glm::vec2>& lastPositions, const std::vector<glm::vec2>& lastVelocities) const
{
    for(int32_t bubbleAIndex = 0; bubbleAIndex < bubbleData.bubbleAmount; bubbleAIndex++)
    {
        glm::vec2 lastPosA = lastPositions[bubbleAIndex];
        glm::vec2 lastVelA = lastVelocities[bubbleAIndex];
        float radiusA = bubbleData.radiuses[bubbleAIndex];
        for(int32_t bubbleBIndex = bubbleAIndex + 1; bubbleBIndex < bubbleData.bubbleAmount; bubbleBIndex++)
        {
            glm::vec2 lastPosB = lastPositions[bubbleBIndex];
            glm::vec2 lastVelB = lastVelocities[bubbleBIndex];
            float radiusB = bubbleData.radiuses[bubbleBIndex];

            //We need the velocity of A as relative to B's velocity so that B can be considered static
            //this is done by adding the reverse velocity of B to A

            glm::vec2 relativeVelA = lastVelA + -lastVelB;

            //step 1: Check that A travelled far enough to even possibly hit B
            //
            // If the movement vector of A is shorter than the distance of the spheres minus their radiuses, there can be no collision
            float centerDistance = glm::distance(lastPosA, lastPosB);

            if(glm::length(relativeVelA) < centerDistance - radiusA - radiusB)
            {
                std::cout << "no collision possible\n";
                continue;
            }


        }
    }
}
