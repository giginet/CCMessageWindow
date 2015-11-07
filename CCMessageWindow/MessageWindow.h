//
//  MessageWindow.h
//  CCMessageWindow
//
//  Created by giginet on 8/2/15.
//
//

#ifndef __CCMessageWindow__MessageWindow__
#define __CCMessageWindow__MessageWindow__

#include "MessageQueue.h"

namespace CCMessageWindow {
    typedef std::function<void (MessageWindow *, int index, std::string)> CCMessageWindowOnTextUpdatedCallback;
    typedef std::function<void (MessageWindow *, std::string)> CCMessageWindowOnMessageWillFinishCallback;
    
    class MessageWindow :public cocos2d::Node
    {
    CC_CONSTRUCTOR_ACCESS:
        bool init() override;
        MessageWindow();
        virtual ~MessageWindow();
    private:
        void renderUnits(cocos2d::Vector<Unit *> units);
        cocos2d::Label * createLabelWithUnit(Unit *unit);
        cocos2d::Vec2 getPositionByIndex(int index);
    public:
        void updateMessage();
        void update(float dt) override;
        CC_SYNTHESIZE(CCMessageWindowOnTextUpdatedCallback, _onTextUpdatedCallback, OnTextUpdatedCallback);
        CC_SYNTHESIZE(CCMessageWindowOnMessageWillFinishCallback, _onMessageWillFinishCallback, OnMessageWillFinishCallback);
        CC_SYNTHESIZE_RETAIN(MessageQueue *, _queue, Queue);
        CREATE_FUNC(MessageWindow);
    };
}

#endif /* defined(__CCMessageWindow__MessageWindow__) */
