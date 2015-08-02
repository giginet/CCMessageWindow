//
//  MessageQueue.h
//  CCMessageWindow
//
//  Created by giginet on 2012/10/20.
//
//

#ifndef __CCMessageWindow__MessageWindow__
#define __CCMessageWindow__MessageWindow__

#include "cocos2d.h"

namespace CCMessageQueue {
    class MessageQueue :public cocos2d::Ref {
    CC_CONSTRUCTOR_ACCESS:
        MessageQueue();
        virtual ~MessageQueue();
        bool init();
    private:
        void onMessageFinished();
        void onMessageUpdated();
        void update(float dt);
        void updateNextMessage(cocos2d::Ref * sender);
        void updateNextText(cocos2d::Ref * sender);
    public:
        void pushMessage(const wchar_t* message);
        void setMessageSpeed(float speed);
        
        void start();
        void stop();
        
        void finishMessage();
        
        CC_SYNTHESIZE(int, _textSpeed, TextSpeed);
        CC_SYNTHESIZE(float, _messageDuration, MessageDuration);
        CC_SYNTHESIZE(bool, _enabled, Enabled);
        CC_SYNTHESIZE_READONLY(int, _textIndex, TextIndex);
        CC_SYNTHESIZE_READONLY(int, _messageIndex, MessageIndex);
        CC_SYNTHESIZE_RETAIN(cocos2d::Label *, _label, Label);
        CREATE_FUNC(MessageQueue);
    };

}

#endif /* defined(__CCMessageWindow__MessageWindow__) */
