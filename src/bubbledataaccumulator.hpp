#pragma once
#include <vector>
#include "glm.hpp"
#include "bubbles.hpp"


class BubbleDataAccumulator
{
    public:
       BubbleDataAccumulator(BubbleData bubbleData);
       std::vector<glm::vec2> positions() const;
       std::vector<glm::vec2> velocities() const;
       //add more if needed
    private:
       BubbleData mBubbleData;
};
