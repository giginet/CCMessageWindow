//
//  Unit.h
//  CCMessageWindow
//
//  Created by giginet on 8/2/15.
//
//

#ifndef __CCMessageWindow__Unit__
#define __CCMessageWindow__Unit__

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
    
    class Unit :public cocos2d::Ref
    {
    CC_CONSTRUCTOR_ACCESS:
        Unit();
        bool init(const char* text, Attribute attribute);
    public:
        /** Parse message and generate unit container */
        static cocos2d::Vector<Unit *> parseUnits(const char *message);
        
        static Unit *create(const char* text);
        static Unit *create(const char* text, Attribute attribute);
        
        CC_SYNTHESIZE(std::string, _text, Text);
        CC_SYNTHESIZE(Attribute, _attribute, Attribute);
    };
}

#endif /* defined(__CCMessageWindow__Unit__) */
