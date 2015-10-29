#pragma once
#include "bubble.hpp"

class BubbleFactory
{
    public: 
        static Bubble generate(const glm::vec2& position);
};
