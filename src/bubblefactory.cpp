#include "bubblefactory.hpp"
#include <random>

Bubble BubbleFactory::generate(const glm::vec2& position)
{
    Bubble newBubble;
    newBubble.staticBody = false;

     static std::random_device rd;
     static std::mt19937 gen(rd());

     //values near the mean are the most likely
     //standard deviation affects the dispersion of generated values from the mean
     std::normal_distribution<float> sizeDistribution(0.25f, 0.15f);

     float sizeClass = std::max(std::min(1.0f, sizeDistribution(gen)), 0.1f);

    newBubble.position = position;
    newBubble.radius = 70.0f * sizeClass;

    fea::HSVColor color(0.90f + sizeClass * 0.1f, 0.74f, 0.61f);
    newBubble.color = color.toRGB();

    //fea::Color colorA(41, 80, 155);
    //fea::Color colorB(229, 45, 43);


    return newBubble;
}

Bubble BubbleFactory::generateStatic(const glm::vec2& position)
{
    Bubble newBubble;
    newBubble.staticBody = true;

    newBubble.position = position;
    newBubble.radius = 50.0f;
    newBubble.color = {61, 193, 170};

    return newBubble;
}
