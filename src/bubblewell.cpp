#include "bubblewell.hpp"
#include <fea/ui/sdl2windowbackend.hpp>
#include <fea/ui/sdl2inputbackend.hpp>
#include "texturemaker.hpp"

Bubblewell::Bubblewell() :
    mWindow(new fea::SDL2WindowBackend(), fea::VideoMode(1366, 768), "Bubblewell"),
    mRenderer(fea::Viewport({1366, 768}, {0, 0}, fea::Camera({1366 / 2.0f, 768 / 2.0f}))),
    mFeaInputHandler(new fea::SDL2InputBackend()),
    mInputHandler(mBus, mFeaInputHandler),
    mSimulate(false)
{
    mWindow.setVSyncEnabled(true);
    mWindow.setFramerateLimit(60);

    mBus.addSubscriber<QuitMessage>(*this);
    mBus.addSubscriber<MouseMoveMessage>(*this);
    mBus.addSubscriber<KeyPressedMessage>(*this);

    mBubbleTexture = makeTexture("data/textures/bubble.png");

    float startX = 500.0f;
    float startY = 300.0f;

    for(int32_t index = 0; index < 100; index++)
    {
        float floatIndex = static_cast<float>(index);
        mBubbles.create(glm::vec2(startX + (floatIndex / 10.0f) * 30.0f, startY + static_cast<float>(index % 10) * 30.0f), 30.0f);
    }
}

Bubblewell::~Bubblewell()
{
    mBus.removeSubscriber<QuitMessage>(*this);
    mBus.removeSubscriber<MouseMoveMessage>(*this);
    mBus.removeSubscriber<KeyPressedMessage>(*this);
}

void Bubblewell::handleMessage(const QuitMessage& message)
{
    (void)message;
    quit();
}

void Bubblewell::handleMessage(const MouseMoveMessage& message)
{
    mIntegrator.setGravityPoint(static_cast<glm::vec2>(message.position));
}

void Bubblewell::handleMessage(const KeyPressedMessage& message)
{
    (void)message;
    mSimulate = !mSimulate;
}

void Bubblewell::loop()
{
    mInputHandler.process();

    if(mSimulate)
        mIntegrator.integrate(mBubbles.bubbleData());

    mRenderer.clear();

    fea::Quad bubble;
    bubble.setTexture(mBubbleTexture);

    BubbleData bubbleData = mBubbles.bubbleData();

    for(size_t index = 0; index < bubbleData.bubbleAmount; index++)
    {
        bubble.setPosition(bubbleData.positions[index]);
        float radius = bubbleData.radiuses[index];
        float speed = glm::length(bubbleData.velocities[index]);

        bubble.setSize({radius, radius});
        bubble.setOrigin(glm::vec2(radius, radius) / 2.0f);
        bubble.setColor(fea::Color(41 + static_cast<int32_t>(speed * 50.0f), 80, 155));
        //fea::Color(229, 45, 43)

        mRenderer.queue(bubble);
    }

    mRenderer.render();

    mWindow.swapBuffers();
}
