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
    
    Attribute::Attribute()
    : fontName("Helvetica")
    , fontSize(64)
    , color(Color3B::WHITE)
    {
    }
    
    Attribute Attribute::defaultAttribute()
    {
        auto attr = Attribute();
        return attr;
    }
    
    Unit::Unit()
    : _text("")
    {
    }

    
    bool Unit::init(const char *text, CCMessageWindow::Attribute attribute)
    {
        return true;
    }
    
    Unit * Unit::create(const char *text, CCMessageWindow::Attribute attribute)
    {
        Unit *unit = new Unit();
        if (unit && unit->init(text, attribute)) {
            unit->autorelease();
            return unit;
        }
        CC_SAFE_DELETE(unit);
        return nullptr;
    }
    
    Unit * Unit::create(const char *text)
    {
        Attribute attribute;
        return Unit::create(text, attribute);
    }
    
    cocos2d::Vector<Unit *> Unit::parseUnits(const char *message)
    {
        cocos2d::Vector<Unit *> units;
        
        // TODO 現在はタグを考慮しない
        std::u16string utf16String;
        StringUtils::UTF8ToUTF16(message, utf16String);
        
        auto splitted = StringUtils::getChar16VectorFromUTF16String(utf16String);
        
        for (char16_t c : splitted) {
            const char16_t array[] = {c, 0};
            std::string outUtf8;
            std::u16string utf16Str(array);
            StringUtils::UTF16ToUTF8(utf16Str, outUtf8);
            auto unit = Unit::create(outUtf8.c_str());
            units.pushBack(unit);
        }
        
        return std::move(units);
    }
}