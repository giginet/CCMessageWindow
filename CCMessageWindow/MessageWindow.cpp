//
//  MessageWindow.cpp
//  CCMessageWindow
//
//  Created by giginet on 8/2/15.
//
//

#include "MessageWindow.h"

USING_NS_CC;

namespace CCMessageWindow {
    
    MessageWindow::MessageWindow()
    : _queue(nullptr)
    {
        
    }
    
    MessageWindow::~MessageWindow()
    {
        CC_SAFE_RELEASE_NULL(_queue);
    }
    
    bool MessageWindow::init()
    {
        if (!Node::create()) {
            return false;
        }
        auto queue = MessageQueue::create();
        this->setQueue(queue);
        
        this->scheduleUpdate();
        
        return true;
    }
    
    void MessageWindow::update(float dt)
    {
        
    }
    
    void MessageWindow::updateMessage()
    {
        this->removeAllChildren();
        auto units = _queue->getCurrentUnits();
        this->renderUnits(units);
    }
    
    void MessageWindow::renderUnits(cocos2d::Vector<Unit *> units)
    {
        int index = 0;
        for (auto unit : units) {
            auto label = this->createLabelWithUnit(unit);
            this->addChild(label);
            auto width = 64;
            // 今は固定で1列に並ぶ
            label->setPosition(Vec2(width * index, 0));
            ++index;
        }
    }
    
    cocos2d::Label * MessageWindow::createLabelWithUnit(CCMessageWindow::Unit *unit)
    {
        auto text = unit->getText();
        std::string utf8String;
        StringUtils::UTF16ToUTF8(unit->getText(), utf8String);
        auto label = Label::createWithSystemFont(utf8String.c_str(), unit->getFontName(), 64);
        return label;
    }
    
    
}