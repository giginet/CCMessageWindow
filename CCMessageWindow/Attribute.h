#ifndef Attribute_hpp
#define Attribute_hpp

#include "cocos2d.h"

namespace CCMessageWindow {
    class Attribute
    {
    public:
        std::string fontName;
        cocos2d::Color3B color;
        float fontSize;
        Attribute();
        
        static Attribute defaultAttribute();
    };
}

#endif /* Attribute_hpp */
