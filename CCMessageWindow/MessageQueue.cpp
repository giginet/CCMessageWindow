//
//  MessageQueue.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/10/20.
//
//

#include "MessageQueue.h"
#include <sstream>

USING_NS_CC;

namespace CCMessageWindow {
    MessageQueue::MessageQueue()
    : _textSpeed(1)
    , _textIndex(0)
    , _textDuration(0.1)
    , _messageDelay(0)
    , _enabled(true)
    , _label(nullptr)
    {
        
    }
    
    MessageQueue::~MessageQueue()
    {        
        CC_SAFE_RELEASE_NULL(_label);
    }
    
    bool MessageQueue::init()
    {
        return true;
    }
    
    void MessageQueue::pushMessage(const char *message)
    {
        _messages.push_back(message);
    }
    
    std::string MessageQueue::getCurrentMessage()
    {
        return _messages.front();
    }
    
    std::string MessageQueue::getCurrentWholeMessage()
    {
        return _messages.front();
    }
    
    void MessageQueue::onMessageFinished()
    {
        
    }
    
    void MessageQueue::onMessageUpdated()
    {
        
    }
    
    cocos2d::Vector<Unit *> MessageQueue::getCurrentUnits()
    {
        cocos2d::Vector<Unit *> units;
        for (int i = 0; i < _textIndex; ++i) {
            units.pushBack(_currentWholeUnits.at(i));
        }
        return units;
    }
    
    void MessageQueue::updateQueue()
    {
        if (this->isEnd()) {
            return;
        }
        if (this->isEndOfMessage()) {
            this->updateNextMessage();
        } else {
            this->updateNextText();
        }
        
    }
    
    void MessageQueue::start()
    {
        this->updateQueue();
    }
    
    void MessageQueue::updateNextMessage()
    {
        
        _currentWholeUnits = Unit::parseUnits(message);
    }
    
    void MessageQueue::updateNextText()
    {
        _textIndex += _textSpeed;
        long maxTextLength = this->getCurrentMessageLength() - 1;
        if (_textIndex > maxTextLength) {
            _textIndex = (int)maxTextLength;
            if (_messageDelay > 0) {
                this->updateNextMessage();
            }
        } else {
            this->scheduleUpdateText();
        }
    }
    
    bool MessageQueue::isEndOfMessage()
    {
        auto length = this->getCurrentMessageLength();
        return _textIndex == (length - 1);
    }
    
    bool MessageQueue::isEnd()
    {
        return _messages.empty();
    }
    
    void MessageQueue::scheduleUpdateText()
    {
        auto scheduler = Director::getInstance()->getScheduler();
        scheduler->schedule([this](float dt) {
            this->updateNextText();
        }, 
                            this, 
                            0, 
                            0, 
                            _textDuration, 
                            false, 
                            "updateNextText");
    }
    
    void MessageQueue::scheduleUpdateMessage()
    {
        auto scheduler = Director::getInstance()->getScheduler();
        scheduler->schedule([this](float dt) {
            this->updateNextMessage();
        }, 
                            this, 
                            0, 
                            0, 
                            _messageDelay, 
                            false, 
                            "updateNextMessage");
    }
    
    void MessageQueue::nextMessage()
    {
        
    }
    
    long MessageQueue::getCurrentMessageLength()
    {
        auto length = StringUtils::getCharacterCountInUTF8String(this->getCurrentWholeMessage());
        return length;
    }
}