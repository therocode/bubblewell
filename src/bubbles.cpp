#include "bubbles.hpp"

void Bubbles::add(const Bubble& bubble)
{
    mPositions.push_back(bubble.position);
    mVelocities.push_back(bubble.velocity);
    mRadiuses.push_back(bubble.radius);
    mColors.push_back(bubble.color);
}

BubbleData Bubbles::bubbleData()
{
    return
    {
        mPositions.size(),
        mPositions.data(),
        mVelocities.data(),
        mRadiuses.data(),
        mColors.data()
    };
}

ConstBubbleData Bubbles::bubbleData() const
{
    return
    {
        mPositions.size(),
        mPositions.data(),
        mVelocities.data(),
        mRadiuses.data(),
        mColors.data()
    };
}
