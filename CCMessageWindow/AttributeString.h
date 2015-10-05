#ifndef __CCMessageWindow__AttributeString__
#define __CCMessageWindow__AttributeString__

#include "cocos2d.h"
#include "Unit.h"
#include "Attribute.h"

namespace CCMessageWindow {
    typedef cocos2d::Vector<Unit *> UnitVector;
    
    class AttributeString :public cocos2d::Ref
    {
    CC_CONSTRUCTOR_ACCESS:
        AttributeString();
        bool init(UnitVector units);
        virtual ~AttributeString();
    private:
        UnitVector _units;
    public:
        static AttributeString * create(const char *text);
        static AttributeString * create(const char *text, Attribute attribute);
        static AttributeString * create(UnitVector units);
        
        void appendUnit(Unit *unit);
        void appendString(const char * string, Attribute attribute);
        void appendString(const char * string);
        
        size_t getLength();
        std::string getCharacter(int index);
        Attribute getAttribute(int index);
        Unit * getCharacterUnit(int index);
        std::string getText();
        UnitVector getUnitsByCharacters();
    };
}

#endif /* defined(__CCMessageWindow__AttributeString__) */
