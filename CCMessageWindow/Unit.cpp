//
//  Unit.cpp
//  CCMessageWindow
//
//  Created by giginet on 8/2/15.
//
//

#include "Unit.h"
#include <iostream>
#include <vector>

USING_NS_CC;

namespace CCMessageWindow {
    
    Unit::Unit()
    : _text()
    , _fontName("Helvetica")
    , _color(Color3B::WHITE)
    , _fontSize(64) // FIX ME
    {
        
    }
    
    bool Unit::init()
    {
        return true;
    }
    
    cocos2d::Vector<Unit *> Unit::parseUnits(const char *message)
    {
        cocos2d::Vector<Unit *> units;
        
        // TODO 現在はタグを考慮しない
        std::u16string utf16String;
        StringUtils::UTF8ToUTF16(message, utf16String);
        
        auto splitted = StringUtils::getChar16VectorFromUTF16String(utf16String);
        
        for (char16_t c : splitted) {
            auto unit = Unit::create();
            const char16_t array[] = {c, 0};
            std::u16string utf16Str(array);
            unit->setText(utf16Str);
            units.pushBack(unit);
        }
        
        return std::move(units);
    }
    
}