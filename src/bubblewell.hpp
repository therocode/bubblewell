#include <fea/structure.hpp>
#include <fea/render2d.hpp>
#include <fea/util.hpp>
#include <fea/userinterface.hpp>
#include "inputhandler.hpp"
#include "messages.hpp"
#include "audioplayer.hpp"

class Bubblewell : public fea::Application,
    public fea::MessageReceiver<QuitMessage>
{
    public:
        Bubblewell();
        ~Bubblewell();
        void handleMessage(const QuitMessage& message) override;
    protected:
        virtual void loop() override;
    private:
        fea::MessageBus mBus;
        fea::Window mWindow;
        fea::Renderer2D mRenderer;
        fea::InputHandler mFeaInputHandler;

        InputHandler mInputHandler;
        AudioPlayer mAudioPlayer;
};
