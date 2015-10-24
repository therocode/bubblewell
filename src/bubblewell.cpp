#include "bubblewell.hpp"
#include <fea/ui/sdl2windowbackend.hpp>
#include <fea/ui/sdl2inputbackend.hpp>

Bubblewell::Bubblewell() :
    mWindow(new fea::SDL2WindowBackend(), fea::VideoMode(1366, 768), "Bubblewell"),
    mRenderer(fea::Viewport({1366, 768}, {0, 0}, fea::Camera({1366 / 2.0f, 768 / 2.0f}))),
    mFeaInputHandler(new fea::SDL2InputBackend()),
    mInputHandler(mBus, mFeaInputHandler),
    mAudioPlayer(mBus)
{
    mWindow.setVSyncEnabled(true);
    mWindow.setFramerateLimit(60);

    mBus.addSubscriber<QuitMessage>(*this);
}

Bubblewell::~Bubblewell()
{
    mBus.removeSubscriber<QuitMessage>(*this);
}

void Bubblewell::handleMessage(const QuitMessage& message)
{
    (void)message;
    quit();
}

void Bubblewell::loop()
{
    mInputHandler.process();
    mAudioPlayer.update();

    mWindow.swapBuffers();
}
