#include "bubbledataaccumulator.hpp"
#include "bubbles.hpp"
#include <iostream>

BubbleDataAccumulator::BubbleDataAccumulator(BubbleData bubbleData):
    mBubbleData(std::move(bubbleData))
{
}

std::vector<glm::vec2> BubbleDataAccumulator::positions() const
{
    std::vector<glm::vec2> result(mBubbleData.bubbleAmount);

    for(int32_t i = 0; i < mBubbleData.bubbleAmount; ++i)
        result[i] = mBubbleData.positions[i];

    return result;
}

std::vector<glm::vec2> BubbleDataAccumulator::velocities() const
{
    std::vector<glm::vec2> result(mBubbleData.bubbleAmount);

    for(int32_t i = 0; i < mBubbleData.bubbleAmount; ++i)
    {
        result[i] = mBubbleData.velocities[i];
    }

    return result;
}
