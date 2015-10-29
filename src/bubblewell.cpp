#include "bubblewell.hpp"
#include <fea/ui/sdl2windowbackend.hpp>
#include <fea/ui/sdl2inputbackend.hpp>
#include "texturemaker.hpp"
#include "randomselector.hpp"
#include "bubblefactory.hpp"

Bubblewell::Bubblewell() :
    mWindow(new fea::SDL2WindowBackend(), fea::VideoMode(1366, 768), "Bubblewell"),
    mRenderer(fea::Viewport({1366, 768}, {0, 0}, fea::Camera({1366 / 2.0f, 768 / 2.0f}))),
    mFeaInputHandler(new fea::SDL2InputBackend()),
    mInputHandler(mBus, mFeaInputHandler),
    mSimulate(false),
    mNoiseAnimation({0, 0}, {64, 64}, 4, 12, true),
    mNoiseQuad({1366.0f, 768.0f})
{
    mWindow.setVSyncEnabled(true);
    mWindow.setFramerateLimit(60);

    subscribe(mBus, *this, false);

    mBubbleTexture = makeTexture("data/textures/bubble.png");

    float startX = 500.0f;
    float startY = 300.0f;

    for(int32_t index = 0; index < 100; index++)
    {
        float floatIndex = static_cast<float>(index);
        mBubbles.add(BubbleFactory::generate(glm::vec2(startX + (floatIndex / 10.0f) * 30.0f, startY + static_cast<float>(index % 10) * 30.0f)));
    }

    mNoiseTexture = makeTexture("data/textures/noise.png");
    mNoiseQuad.setTexture(mNoiseTexture);  
    mNoiseQuad.setAnimation(mNoiseAnimation);  
    mNoiseQuad.setTileSize({64.0f, 64.0f});
    mNoiseQuad.setColor({41, 80, 155, 150});
}

void Bubblewell::handleMessage(const QuitMessage& message)
{
    (void)message;
    quit();
}

void Bubblewell::handleMessage(const MouseMoveMessage& message)
{
    mIntegrator.setGravityPoint(static_cast<glm::vec2>(message.position));

    xCent = static_cast<float>(message.position.x) / 1366.0f;
    yCent = static_cast<float>(message.position.y) / 768.0f;
}

void Bubblewell::handleMessage(const KeyPressedMessage& message)
{
    if(message.key == fea::Keyboard::SPACE)
        mSimulate = !mSimulate;
}

void Bubblewell::loop()
{
    mInputHandler.process();

    if(mSimulate)
        mIntegrator.integrate(mBubbles.bubbleData());

    mRenderer.clear();

    mRenderer.queue(mNoiseQuad);

    fea::Quad bubble;
    bubble.setTexture(mBubbleTexture);

    BubbleData bubbleData = mBubbles.bubbleData();

    for(size_t index = 0; index < bubbleData.bubbleAmount; index++)
    {
        bubble.setPosition(bubbleData.positions[index]);
        float radius = bubbleData.radiuses[index];
        //float speed = glm::length(bubbleData.velocities[index]);
        const fea::Color& color = bubbleData.colors[index];

        bubble.setSize({radius, radius});
        bubble.setOrigin(glm::vec2(radius, radius) / 2.0f);
        bubble.setColor(color);

        mRenderer.queue(bubble);
    }

    mRenderer.render();

    mWindow.swapBuffers();

    mNoiseQuad.tick();

    mNoiseQuad.tick();
}
