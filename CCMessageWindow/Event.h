#ifndef Event_h
#define Event_h

#include "cocos2d.h"

namespace CCMessageWindow {
    class EventTextUpdated :public cocos2d::EventCustom {
    public:
        std::string updatedString;
        int startedIndex;
        
        EventTextUpdated(const std::string &eventName);
    };
    
    class EventMessageFinished :public cocos2d::EventCustom {
    public:
        EventMessageFinished(const std::string &eventName);
    };
}

#endif
