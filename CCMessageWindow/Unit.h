//
//  Unit.hpp
//  Commuage
//
//  Created by giginet on 10/5/15.
//
//

#ifndef Unit_hpp
#define Unit_hpp

#include <stdio.h>
#include "Attribute.h"

namespace CCMessageWindow {
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
        
        size_t getLength();
        
        CC_SYNTHESIZE(std::string, _text, Text);
        CC_SYNTHESIZE(Attribute, _attribute, Attribute);
    };
}

#endif /* Unit_hpp */
