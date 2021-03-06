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
        this->updateMessage();
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
            auto pos = this->getPositionByIndex(index);
            label->setPosition(pos);
            ++index;
        }
    }
    
    cocos2d::Vec2 MessageWindow::getPositionByIndex(int index)
    {
        // FIX ME 実際の_widthより広いエリアに描画されてしまう
        auto units = _queue->getCurrentUnits();
        int x = 0;
        int y = 0;
        float width = this->getContentSize().width;
        for (int i = 0; i < index; ++i) {
            auto unit = units.at(i);
            x += unit->getAttribute().fontSize;
            if (width > 0 && x > width) {
                // line breal;
                x = 0;
                // TODO フォントサイズが全て同じという前提に成り立っている
                y -= unit->getAttribute().fontSize;
            }
        }
        return Vec2(x, y);
    }
    
    cocos2d::Label * MessageWindow::createLabelWithUnit(CCMessageWindow::Unit *unit)
    {
        auto text = unit->getText();
        auto label = Label::createWithSystemFont(text.c_str(), unit->getAttribute().fontName, unit->getAttribute().fontSize);
        label->setColor(unit->getAttribute().color);
        return label;
    }
    
    
}