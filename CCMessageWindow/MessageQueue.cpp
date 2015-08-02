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
    , _remainTime(0)
    , _textDuration(0.2)
    , _messageDelay(1.0)
    , _enabled(false)
    , _label(nullptr)
    {
        
    }
    
    MessageQueue::~MessageQueue()
    {        
        CC_SAFE_RELEASE_NULL(_label);
    }
    
    bool MessageQueue::init()
    {
        auto scheduler = Director::getInstance()->getScheduler();
        scheduler->scheduleUpdate(this, 0, false);
        return true;
    }
    
    void MessageQueue::update(float dt)
    {
        if (!_enabled) return;
        _remainTime -= dt;
        if (_remainTime < 0) {
            if (this->isEndOfMessage()) {
                // 次のメッセージ
                this->updateNextMessage();
            } else if (!_messages.empty()) {
                // 次のテキスト
                this->updateNextText();
            } else {
                
            }
        }
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
    
    void MessageQueue::start()
    {
        _enabled = true;
        if (_messages.size() > 0 && _currentWholeUnits.empty()) {
            this->updateNextMessage();
        }
    }
    
    void MessageQueue::updateNextMessage()
    {
        if (!_messages.empty()) {
            auto message = _messages.front();
            _currentWholeUnits = Unit::parseUnits(message.c_str());
            _remainTime = _textDuration;
        }
    }
    
    void MessageQueue::updateNextText()
    {
        _textIndex += _textSpeed;
        long maxTextLength = this->getCurrentMessageLength() - 1;
        log("textIndex = %d", _textIndex);
        if (_textIndex > maxTextLength) {
            // 次のメッセージに
            _messages.pop_back();
            _textIndex = (int)maxTextLength;
            if (_messageDelay > 0) {
                _remainTime = _messageDelay;
            }
        } else {
            _remainTime = _textDuration;
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
    
    void MessageQueue::nextMessage()
    {
        
    }
    
    long MessageQueue::getCurrentMessageLength()
    {
        auto length = StringUtils::getCharacterCountInUTF8String(this->getCurrentWholeMessage());
        return length;
    }
}