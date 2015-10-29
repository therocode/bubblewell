#include "bubbleintegrator.hpp"

const float gGravityPointMass = 1.6f;
const float gGravityConstant = 1.0f;

void BubbleIntegrator::integrate(BubbleData bubbleData) const
{
    glm::vec2 oldPosition;
    glm::vec2 directionToGravity;
    float distanceToGravity;
    float radius;

    for(size_t index = 0; index < bubbleData.bubbleAmount; index++)
    {
        if(!bubbleData.staticBodyBools[index])
        {
            radius =  bubbleData.radiuses[index];
            oldPosition = bubbleData.positions[index];
            distanceToGravity = glm::distance(oldPosition, mGravityPoint);
            directionToGravity = glm::normalize(mGravityPoint - oldPosition);

            float mass = radius * radius * glm::pi<float>();

            bubbleData.velocities[index] += directionToGravity * gGravityConstant * ((gGravityPointMass * mass) / std::pow(distanceToGravity, 2.0f));
            bubbleData.positions[index] += bubbleData.velocities[index];
        }
    }
}

void BubbleIntegrator::setGravityPoint(const glm::vec2& position)
{
    mGravityPoint = position;
}
