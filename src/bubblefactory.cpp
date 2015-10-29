#include "bubblefactory.hpp"

Bubble BubbleFactory::generate(const glm::vec2& position, float radius)
{
    Bubble newBubble;

    newBubble.position = position;
    newBubble.radius = radius;
    newBubble.color = fea::Color::Red;

    return newBubble;
}
