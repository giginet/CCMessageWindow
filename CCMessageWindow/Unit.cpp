//
//  Unit.cpp
//  CCMessageWindow
//
//  Created by giginet on 8/2/15.
//
//

#include "Unit.h"

USING_NS_CC;

namespace CCMessageWindow {
    
    Unit::Unit()
    : _text()
    , _fontName("Helvetica")
    , _color(Color3B::WHITE)
    {
        
    }
    
    cocos2d::Vector<Unit *> Unit::parseUnits(const char *message)
    {
        cocos2d::Vector<Unit *> units;
        
        std::u16string utf16String;
        StringUtils::UTF8ToUTF16(message, utf16String);
        auto splitted = StringUtils::getChar16VectorFromUTF16String(utf16String);
        
        for (auto c : splitted) {
            auto unit = Unit::create();
            unit->setText(&c);
        }
        
        return std::move(units);
    }
    
}