#include <fea/structure.hpp>
#include <fea/render2d.hpp>
#include <fea/util.hpp>
#include <fea/userinterface.hpp>
#include "inputhandler.hpp"
#include "messages.hpp"
#include "bubbles.hpp"
#include "bubbleintegrator.hpp"
#include "bubblecollider.hpp"

class Bubblewell : public fea::Application,
    public fea::MessageReceiver<QuitMessage, MouseMoveMessage, KeyPressedMessage>
{
    public:
        Bubblewell();
        void handleMessage(const QuitMessage& message) override;
        void handleMessage(const MouseMoveMessage& message) override;
        void handleMessage(const KeyPressedMessage& message) override;
    protected:
        virtual void loop() override;
    private:
        fea::MessageBus mBus;
        fea::Window mWindow;
        fea::Renderer2D mRenderer;
        fea::InputHandler mFeaInputHandler;

        InputHandler mInputHandler;

        fea::Texture mBubbleTexture;
        Bubbles mBubbles;

        BubbleIntegrator mIntegrator;
        BubbleCollider  mCollider;
        bool mSimulate;
        bool mGravitate;

        float xCent;
        float yCent;

        fea::Texture mNoiseTexture;
        fea::Animation mNoiseAnimation;
        fea::RepeatedQuad mNoiseQuad;

        fea::Texture mCoronaTexture;
        fea::Quad mCoronaQuad;

        fea::FrameTimer mFrameTimer;
};
