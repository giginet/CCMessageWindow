#include "AttributeString.h"
#include "Utils.h"

USING_NS_CC;

namespace CCMessageWindow {
    
    AttributeString::AttributeString()
    {
    }
    
    AttributeString::~AttributeString()
    {
    }

    bool AttributeString::init(UnitVector units)
    {
        _units = units;
        return true;
    }
    
    AttributeString * AttributeString::create(const char *text, CCMessageWindow::Attribute attribute)
    {
        UnitVector units;
        Unit * unit = Unit::create(text, attribute);
        units.pushBack(unit);
        return AttributeString::create(units);
    }
    
    AttributeString * AttributeString::create(const char *text)
    {
        Attribute attribute = Attribute::defaultAttribute();
        return AttributeString::create(text, attribute);
    }
    
    AttributeString * AttributeString::create(UnitVector units)
    {
        AttributeString *str = new AttributeString();
        if (str && str->init(units)) {
            str->autorelease();
            return str;
        }
        CC_SAFE_DELETE(str);
        return nullptr;
    }
    
    void AttributeString::addUnit(CCMessageWindow::Unit *unit)
    {
        _units.pushBack(unit);
    }
    
    size_t AttributeString::getLength()
    {
        int length = 0;
        for (Unit * unit : _units) {
            length += unit->getText().size();
        }
        return length;
    }
    
    std::string AttributeString::getCharacter(int index)
    {
        Unit * unit = this->getCharacterUnit(index);
        return unit->getText();
    }
    
    Attribute AttributeString::getAttribute(int index)
    {
        Unit * unit = this->getCharacterUnit(index);
        return unit->getAttribute();
    }
    
    Unit * AttributeString::getCharacterUnit(int index)
    {
        size_t maxLength = this->getLength();
        CCASSERT(index < maxLength, "index must be smaller than length");
        int currentIndex = 0;
        for (int i = 0; i < _units.size() - 1; ++i) {
            auto unit = _units.at(i);
            auto nextUnit = _units.at(i + 1);
            
            int nextIndex = currentIndex + (int)nextUnit->getLength();
            
            if (currentIndex <= index && index < nextIndex) {
                int offset = index - currentIndex;
                std::string character = Utils::substringUTF8(unit->getText().c_str(), offset, 1);
                Unit * newUnit = Unit::create(character.c_str(), unit->getAttribute());
                return newUnit;
            }
            currentIndex += nextIndex;
        }
        return nullptr;
    }
    
    std::string AttributeString::getText()
    {
        std::stringstream ss;
        for (Unit * unit : _units) {
            ss << unit->getText();
        }
        return ss.str();
    }
    
    UnitVector AttributeString::getUnitsByCharacters()
    {
        size_t length = this->getLength();
        UnitVector units;
        for (int i = 0; i < length; ++length) {
            units.pushBack(this->getCharacterUnit(i));
        }
        return std::move(units);
    }
}