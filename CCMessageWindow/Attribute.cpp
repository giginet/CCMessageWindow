#include "Attribute.h"

namespace CCMessageWindow {
    Attribute::Attribute()
    : fontName("Helvetica")
    , fontSize(64)
    , color(cocos2d::Color3B::WHITE)
    {
    }
    
    Attribute Attribute::defaultAttribute()
    {
        auto attr = Attribute();
        return attr;
    }
}