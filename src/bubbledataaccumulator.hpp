#pragma once
#include <vector>
#include "glm.hpp"

class BubbleData;

class BubbleDataAccumulator
{
    public:
       BubbleDataAccumulator(const BubbleData& bubbleData);
       std::vector<glm::vec2> positions() const;
       std::vector<glm::vec2> velocities() const;
       //add more if needed
    private:
       const BubbleData& mBubbleData;
};
