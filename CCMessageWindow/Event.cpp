#include "Event.h"

namespace CCMessageWindow {
    EventTextUpdated::EventTextUpdated(const std::string& eventName)
    : EventCustom(eventName)
    , startedIndex(0)
    , updatedString("")
    {
    }
    
    EventMessageFinished::EventMessageFinished(const std::string& eventName)
    : EventCustom(eventName)
    {
    }
}