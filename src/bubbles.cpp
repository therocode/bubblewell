#include "bubbles.hpp"

void Bubbles::create(const glm::vec2& position, float radius)
{
    mPositions.push_back(position);
    mVelocities.push_back(glm::vec2());
    mRadiuses.push_back(radius);
}

BubbleData Bubbles::bubbleData()
{
    return
    {
        mPositions.size(),
        mPositions.data(),
        mVelocities.data(),
        mRadiuses.data()
    };
}

ConstBubbleData Bubbles::bubbleData() const
{
    return
    {
        mPositions.size(),
        mPositions.data(),
        mVelocities.data(),
        mRadiuses.data()
    };
}
