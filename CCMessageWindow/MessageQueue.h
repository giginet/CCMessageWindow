//
//  MessageQueue.h
//  CCMessageWindow
//
//  Created by giginet on 2012/10/20.
//
//

#ifndef __CCMessageWindow__MessageQueue__
#define __CCMessageWindow__MessageQueue__

#include "cocos2d.h"
#include "Unit.h"

namespace CCMessageWindow {
    class MessageQueue :public cocos2d::Ref {
    CC_CONSTRUCTOR_ACCESS:
        MessageQueue();
        virtual ~MessageQueue();
        bool init();
    private:
        void onMessageFinished();
        void onMessageUpdated();
        void updateNextMessage();
        void updateNextText();
        
        float _remainTime;
        bool _endMessage;
        bool _isAutoSeekEnabled;
        
        cocos2d::Vector<Unit *> _currentWholeUnits;
        long getCurrentMessageLength();
    public:
        void pushMessage(const char* message);
        std::string getCurrentWholeMessage();
        std::string getCurrentMessage();
        cocos2d::Vector<Unit *> getCurrentUnits();
        
        void finishMessage();
        
        bool isEndOfMessage();
        bool isEnd();
        void update(float dt);
        
        void start();
        void nextMessage();
        
        void setIsAutoSeekEnabled(bool val)
        {
            _isAutoSeekEnabled = true;
        }
        
        bool isAutoSeekEnabled()
        {
            return _isAutoSeekEnabled;
        }
        
        CC_SYNTHESIZE(int, _textSpeed, TextSpeed);
        CC_SYNTHESIZE(float, _textDuration, TextDuration);
        CC_SYNTHESIZE(float, _messageDelay, MessageDelay);
        CC_SYNTHESIZE(bool, _enabled, Enabled);
        CC_SYNTHESIZE_READONLY(int, _textIndex, TextIndex);
        CC_SYNTHESIZE_PASS_BY_REF(std::queue<std::string>, _messages, Messages);
        CC_SYNTHESIZE_RETAIN(cocos2d::Label *, _label, Label);
        CREATE_FUNC(MessageQueue);
    };
    
}

#endif /* defined(__CCMessageWindow__MessageQueue__) */
