#include "bubbleintegrator.hpp"

const float gGravityConstant = 1.6f;

void BubbleIntegrator::integrate(BubbleData bubbleData) const
{
    glm::vec2 oldPosition;
    glm::vec2 directionToGravity;
    float distanceToGravity;
    float mass = 50.0f;

    for(size_t index = 0; index < bubbleData.bubbleAmount; index++)
    {
        oldPosition = bubbleData.positions[index];
        distanceToGravity = glm::distance(oldPosition, mGravityPoint);
        directionToGravity = glm::normalize(mGravityPoint - oldPosition);

        bubbleData.velocities[index] += directionToGravity * gGravityConstant * ((mass * mass) / std::pow(distanceToGravity, 2.0f));
        bubbleData.positions[index] += bubbleData.velocities[index];
    }
}

void BubbleIntegrator::setGravityPoint(const glm::vec2& position)
{
    mGravityPoint = position;
}
