#include "bubblewell.hpp"
#include <fea/ui/sdl2windowbackend.hpp>
#include <fea/ui/sdl2inputbackend.hpp>
#include "texturemaker.hpp"
#include "randomselector.hpp"
#include "bubblefactory.hpp"
#include "bubbledataaccumulator.hpp"

Bubblewell::Bubblewell() :
    mWindow(new fea::SDL2WindowBackend(), fea::VideoMode(768, 768), "Bubblewell"),
    mRenderer(fea::Viewport({768, 768}, {0, 0}, fea::Camera({768 / 2.0f, 768 / 2.0f}, {0.25f, 0.25f}))),
    mFeaInputHandler(new fea::SDL2InputBackend()),
    mInputHandler(mBus, mFeaInputHandler),
    mSimulate(false),
    mGravitate(false),
    mNoiseAnimation({0, 0}, {64, 64}, 4, 12, true),
    mNoiseQuad({768.0f, 768.0f}),
    mCoronaQuad({768.0f, 768.0f})
{
    mWindow.setVSyncEnabled(false);
    mWindow.setFramerateLimit(60);

    subscribe(mBus, *this, false);

    mBubbleTexture = makeTexture("data/textures/bubble.png");

    float startX = -784.0f;
    float startY = -784.0f;

    for(int32_t x = 0; x < 30; ++x)
    {
        for(int32_t y = 0; y < 30; ++y)
        {
            mBubbles.add(BubbleFactory::generate(glm::vec2(startX + static_cast<float>(x) * 80.0f, startY + static_cast<float>(y) * 80.0f)));
        }
    }

    //mBubbles.add(BubbleFactory::generate({ 300.0f, 300.0f}));
    //mBubbles.add(BubbleFactory::generate({ 700.0f, 700.0f}));

    mNoiseTexture = makeTexture("data/textures/noise.png");
    mNoiseQuad.setTexture(mNoiseTexture);  
    mNoiseQuad.setAnimation(mNoiseAnimation);  
    mNoiseQuad.setTileSize({64.0f, 64.0f});
    mNoiseQuad.setColor({41, 80, 155, 150});

    mCoronaTexture = makeTexture("data/textures/corona.png");
    mCoronaQuad.setTexture(mCoronaTexture);
    mCoronaQuad.setOrigin(mCoronaQuad.getSize() / 2.0f);
    mCoronaQuad.setPosition({384.0f, 384.0f});

    mIntegrator.setGravityPoint({384.0f, 384.0f});

    mBubbles.add(BubbleFactory::generateStatic({384.0f, 384.0f}));

    //mIntegrator.setGravityPoint({1000000.0f, 2323423423.0f});
}

void Bubblewell::handleMessage(const QuitMessage& message)
{
    (void)message;
    quit();
}

void Bubblewell::handleMessage(const MouseMoveMessage& message)
{
    if(mGravitate)
        mIntegrator.setGravityPoint(static_cast<glm::vec2>(message.position));

    xCent = static_cast<float>(message.position.x) / 768.0f;
    yCent = static_cast<float>(message.position.y) / 768.0f;
}

void Bubblewell::handleMessage(const KeyPressedMessage& message)
{
    if(message.key == fea::Keyboard::SPACE)
        mSimulate = !mSimulate;
    if(message.key == fea::Keyboard::G)
    {
        mGravitate = !mGravitate;
        if(!mGravitate)
            mIntegrator.setGravityPoint({1000000.0f, 2323423423.0f});
    }
}

void Bubblewell::loop()
{
    mInputHandler.process();

    if(mSimulate)
    {
        BubbleDataAccumulator accumulator(mBubbles.bubbleData());
        auto lastPositions = accumulator.positions();
        auto lastVelocities = accumulator.velocities();
        mIntegrator.integrate(mBubbles.bubbleData());
        mCollider.resolveCollisions(mBubbles.bubbleData(), lastPositions, lastVelocities);
    }

    mRenderer.clear();

    mRenderer.queue(mNoiseQuad);

    mRenderer.setBlendMode(fea::BlendMode::MULTIPLY);
    mRenderer.queue(mCoronaQuad);
    mRenderer.setBlendMode(fea::BlendMode::ALPHA);

    fea::Quad bubble;
    bubble.setTexture(mBubbleTexture);

    BubbleData bubbleData = mBubbles.bubbleData();

    for(int32_t index = 0; index < bubbleData.bubbleAmount; index++)
    {
        bubble.setPosition(bubbleData.positions[index]);
        float radius = bubbleData.radiuses[index];
        //float speed = glm::length(bubbleData.velocities[index]);
        const fea::Color& color = bubbleData.colors[index];

        bubble.setSize(glm::vec2(radius, radius) * 2.0f);
        bubble.setOrigin(glm::vec2(radius, radius));
        bubble.setColor(color);

        mRenderer.queue(bubble);
    }

    mRenderer.render();

    mWindow.swapBuffers();

    mNoiseQuad.tick();

    //timer
    if(mFrameTimer.frameCount() % 60 == 0)
    {
        std::cout << "frame " << mFrameTimer.frameCount() << ":\n";

        std::cout << "fps: " << mFrameTimer.fps() << "\n";
        std::cout << "avg: " << mFrameTimer.avgFrameTime() << "\n";
        std::cout << "last: " << mFrameTimer.lastFrameTime() << "\n";
        std::cout << "dev: " << mFrameTimer.avgDeviation() << "\n";
        std::cout << "\n";
    }

    mFrameTimer.sample();
}
