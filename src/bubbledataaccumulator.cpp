#include "bubbledataaccumulator.hpp"
#include "bubbles.hpp"

BubbleDataAccumulator::BubbleDataAccumulator(const BubbleData& bubbleData):
    mBubbleData(bubbleData)
{
}

std::vector<glm::vec2> BubbleDataAccumulator::positions() const
{
    return std::vector<glm::vec2>();
}

std::vector<glm::vec2> BubbleDataAccumulator::velocities() const
{
    return std::vector<glm::vec2>();
}
