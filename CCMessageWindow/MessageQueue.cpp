//
//  MessageQueue.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/10/20.
//
//

#include "MessageQueue.h"
#include "MessageWindow.h"
#include "Utils.h"
#include <sstream>

USING_NS_CC;

namespace CCMessageWindow {
    MessageQueue::MessageQueue()
    : _textSpeed(1)
    , _textIndex(0)
    , _remainTime(0)
    , _textDuration(0.2)
    , _messageDelay(1.0)
    , _endMessage(false)
    , _isAutoSeekEnabled(true)
    , _enabled(false)
    , _label(nullptr)
    , _messageWindow(nullptr)
    {
        _defaultAttribute = Attribute::defaultAttribute();
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
            if (_endMessage) {
                this->onMessageFinished();
            } else if (!_messages.empty()) {
                // 次のテキスト
                this->updateNextText();
            } else {
                
            }
        }
    }
    
    void MessageQueue::pushMessage(const char *message)
    {
        auto attrStr = AttributeString::create(message, this->getDefaultAttribute());
        _messages.pushBack(attrStr);
    }
    
    void MessageQueue::pushMessage(CCMessageWindow::AttributeString *attributeString)
    {
        _messages.pushBack(attributeString);
    }
    
    std::string MessageQueue::getCurrentMessage()
    {
        auto wholeString = this->getCurrentWholeMessage();
        return Utils::substringUTF8(wholeString.c_str(), 0, _textIndex);
    }
    
    std::string MessageQueue::getCurrentWholeMessage()
    {
        auto attrStr = _messages.front();
        return attrStr->getText();
    }
    
    void MessageQueue::onMessageFinished()
    {
        auto callback = _messageWindow->getOnMessageFinishedCallback();
        if (callback) {
            callback(_messageWindow, this->getCurrentWholeMessage());
        }
        if (_isAutoSeekEnabled) {
            this->nextMessage();
        }
    }
    
    void MessageQueue::onTextUpdated(int startedIndex, const char *updatedString)
    {
        auto callback = _messageWindow->getOnTextUpdatedCallback();
        if (callback) {
            callback(_messageWindow, startedIndex, updatedString);
        }
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
    
    void MessageQueue::pause()
    {
        _enabled = false;
    }
    
    void MessageQueue::updateNextMessage()
    {
        if (!_messages.empty()) {
            auto message = _messages.front();
            _currentWholeUnits = message->getUnitsByCharacters();
            _remainTime = _textDuration;
            _textIndex = 0;
        }
    }
    
    void MessageQueue::updateNextText()
    {
        int preIndex = _textIndex;
        long maxTextLength = this->getCurrentMessageLength();
        int speed = _textSpeed;
        if (_textIndex + _textSpeed > maxTextLength) {
            speed = (int)maxTextLength - _textIndex;
        }
        
        _textIndex += speed;
        std::string substring = Utils::substringUTF8(this->getCurrentWholeMessage().c_str(), preIndex, speed);
        this->onTextUpdated(preIndex, substring.c_str());
        if (_textIndex >= maxTextLength) {
            // 次のメッセージに
            _endMessage = true;
            _messages.erase(0);
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
        _endMessage = false;
        // 次のメッセージ
        this->updateNextMessage();
    }
    
    long MessageQueue::getCurrentMessageLength()
    {
        auto length = StringUtils::getCharacterCountInUTF8String(this->getCurrentWholeMessage());
        return length;
    }
}