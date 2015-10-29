#pragma once
#include <vector>
#include "bubble.hpp"

struct BubbleData
{
    size_t bubbleAmount;
    glm::vec2* positions;
    glm::vec2* velocities;
    float* radiuses;
    fea::Color* colors;
    int8_t* staticBodyBools;
};

struct ConstBubbleData
{
    size_t bubbleAmount;
    const glm::vec2* positions;
    const glm::vec2* velocities;
    const float* radiuses;
    const fea::Color* colors;
    const int8_t* staticBodyBools;
};

class Bubbles
{
    public:
        void add(const Bubble& bubble);
        BubbleData bubbleData();
        ConstBubbleData bubbleData() const;
    private:
        std::vector<glm::vec2> mPositions;
        std::vector<glm::vec2> mVelocities;
        std::vector<float> mRadiuses;
        std::vector<fea::Color> mColors;
        std::vector<int8_t> mStaticBodyBools;
};
