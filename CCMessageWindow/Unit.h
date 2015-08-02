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
    class Unit :public cocos2d::Ref
    {
    CC_CONSTRUCTOR_ACCESS:
        Unit();
        bool init();
    public:
        /** Parse message and generate unit container */
        static cocos2d::Vector<Unit *> parseUnits(const char *message);
        
        CC_SYNTHESIZE(std::u16string, _text, Text);
        CC_SYNTHESIZE(std::string, _fontName, FontName);
        CC_SYNTHESIZE(float, _fontSize, FontSize);
        CC_SYNTHESIZE(cocos2d::Color3B, _color, Color);
        CREATE_FUNC(Unit);
    };
}

#endif /* defined(__CCMessageWindow__Unit__) */
