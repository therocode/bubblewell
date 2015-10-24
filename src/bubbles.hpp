#pragma once
#include "glm.hpp"
#include <vector>

struct BubbleData
{
    size_t bubbleAmount;
    glm::vec2* positions;
    glm::vec2* velocities;
    float* radiuses;
};

struct ConstBubbleData
{
    size_t bubbleAmount;
    const glm::vec2* positions;
    const glm::vec2* velocities;
    const float* radiuses;
};

class Bubbles
{
    public:
        void create(const glm::vec2& position, float radius);
        BubbleData bubbleData();
        ConstBubbleData bubbleData() const;
    private:
        std::vector<glm::vec2> mPositions;
        std::vector<glm::vec2> mVelocities;
        std::vector<float> mRadiuses;
};
