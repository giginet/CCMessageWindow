#ifndef __CCMessageWindow__MessageQueue__
#define __CCMessageWindow__MessageQueue__

#include "cocos2d.h"
#include "Unit.h"
#include "AttributeString.h"

namespace CCMessageWindow {
    class MessageQueue :public cocos2d::Ref {
    CC_CONSTRUCTOR_ACCESS:
        MessageQueue();
        virtual ~MessageQueue();
        bool init();
        CREATE_FUNC(MessageQueue);
    private:
        void onMessageDidFinished();
        void onTextDidUpdated(int startedIndex, const char* updatedString);
        void updateText();
        bool _isAutoSeekEnabled;
        
        cocos2d::Vector<Unit *> _currentWholeUnits;
        long getCurrentMessageLength();
    public:
        void pushMessage(const char* message);
        void pushMessage(AttributeString * attributeString);
        
        std::string getCurrentWholeMessage();
        std::string getCurrentMessage();
        cocos2d::Vector<Unit *> getCurrentUnits();
        
        void finishMessage();
        
        bool isCurrentMessageFinished();
        bool isAllMessagesFinished();
        void update(float dt);
        
        void endMessage();
        
        void start();
        void pause();
        void seekMessage();
        void clear();
        
        void setAutoSeekEnabled(bool val)
        {
            _isAutoSeekEnabled = val;
        }
        
        bool isAutoSeekEnabled()
        {
            return _isAutoSeekEnabled;
        }
        
        CC_SYNTHESIZE(int, _textSpeed, TextSpeed);
        CC_SYNTHESIZE_READONLY(float, _remainTime, RemainTime);
        CC_SYNTHESIZE(float, _textUpdateDelay, textUpdateDelay);
        CC_SYNTHESIZE(float, _messageUpdateDelay, messageUpdateDelay);
        CC_SYNTHESIZE(bool, _enabled, Enabled);
        CC_SYNTHESIZE(Attribute, _defaultAttribute, DefaultAttribute);
        CC_SYNTHESIZE_READONLY(int, _textIndex, TextIndex);
        CC_SYNTHESIZE_PASS_BY_REF(cocos2d::Vector<AttributeString *>, _messages, Messages);
        CC_SYNTHESIZE_RETAIN(cocos2d::Label *, _label, Label);
    };
}

#endif /* defined(__CCMessageWindow__MessageQueue__) */
