#include "MessageQueue.h"
#include "MessageWindow.h"
#include <sstream>
#include "Utils.h"
#include "Event.h"

USING_NS_CC;

const char* CCMessageWindowOnTextDidUpdatedEventName = "CCMessageWindowOnTextDidUpdated";
const char* CCMessageWindowOnMessageDidFinishedEventName = "CCMessageWindowOnMessageDidFinished";

namespace CCMessageWindow {
    MessageQueue::MessageQueue()
    : _textSpeed(1)
    , _textIndex(0)
    , _remainTime(0)
    , _textUpdateDelay(0.2)
    , _messageUpdateDelay(1.0)
    , _isAutoSeekEnabled(true)
    , _enabled(false)
    , _label(nullptr)
    {
        _defaultAttribute = Attribute::defaultAttribute();
    }
    
    MessageQueue::~MessageQueue()
    {
        auto scheduler = Director::getInstance()->getScheduler();
        scheduler->unscheduleUpdate(this);
        CC_SAFE_RELEASE_NULL(_label);
    }
    
    bool MessageQueue::init()
    {
        return true;
    }
    
    void MessageQueue::update(float dt)
    {
        if (!_enabled) return;
        if (_messages.empty()) return;
        std::string currentMessage = this->getCurrentWholeMessage();
        _remainTime -= dt;
        if (_remainTime <= 0) {
            _remainTime = 0;
            if (this->isCurrentMessageFinished()) {
                // 次のメッセージ
                if (_isAutoSeekEnabled) {
                    this->seekMessage();
                }
            } else {
                // 次のテキスト
                updateText();
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
    
    void MessageQueue::onMessageDidFinished()
    {
        auto event = EventMessageFinished(CCMessageWindowOnMessageDidFinishedEventName);
        event.setUserData(this);
        cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
    }
    
    void MessageQueue::onTextDidUpdated(int startedIndex, const char *updatedString)
    {
        auto event = EventTextUpdated(CCMessageWindowOnTextDidUpdatedEventName);
        event.startedIndex = startedIndex;
        event.updatedString = updatedString;
        event.setUserData(this);
        cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
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
        auto scheduler = Director::getInstance()->getScheduler();
        scheduler->scheduleUpdate(this, 0, false);
        _enabled = true;
        if (_messages.size() > 0 && _currentWholeUnits.empty()) {
            auto nextMessage = _messages.front();
            _currentWholeUnits = nextMessage->getUnitsByCharacters();
            _remainTime = _textUpdateDelay;
            _textIndex = 0;
        }
    }
    
    void MessageQueue::pause()
    {
        auto scheduler = Director::getInstance()->getScheduler();
        scheduler->pauseTarget(this);
        _enabled = false;
    }
    
    void MessageQueue::updateText()
    {
        int preIndex = _textIndex;
        long textLength = this->getCurrentMessageLength();
        int speed = MIN(this->getTextSpeed(), (int)textLength - _textIndex);
        
        _textIndex += speed;
        std::string substring = Utils::substringUTF8(this->getCurrentWholeMessage().c_str(), preIndex, speed);
        this->onTextDidUpdated(preIndex, substring.c_str());
        if (_textIndex >= textLength) {
            // 次のメッセージに
            _textIndex = (int)textLength;
            this->onMessageDidFinished();
            if (this->getmessageUpdateDelay() > 0) {
                _remainTime = this->getmessageUpdateDelay();
            }
        } else {
            _remainTime = this->gettextUpdateDelay();
        }
    }
    
    bool MessageQueue::isCurrentMessageFinished()
    {
        if (this->isAllMessagesFinished()) return true;
        auto length = this->getCurrentMessageLength();
        return _textIndex == length;
    }
    
    bool MessageQueue::isAllMessagesFinished()
    {
        return _messages.empty();
    }
    
    void MessageQueue::seekMessage()
    {
        if (!this->isAllMessagesFinished()) {
            _messages.erase(0);
            
            auto nextMessage = _messages.front();
            _currentWholeUnits = nextMessage->getUnitsByCharacters();
            _remainTime = _textUpdateDelay;
            _textIndex = 0;
        }
    }
    
    void MessageQueue::clear()
    {
        _messages.clear();
        _currentWholeUnits.clear();
        _enabled = false;
        _textIndex = 0;
        _remainTime = 0;
    }
    
    long MessageQueue::getCurrentMessageLength()
    {
        auto length = StringUtils::getCharacterCountInUTF8String(this->getCurrentWholeMessage());
        return length;
    }
}