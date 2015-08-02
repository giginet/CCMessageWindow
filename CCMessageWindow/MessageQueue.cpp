//
//  MessageQueue.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/10/20.
//
//

#include "MessageQueue.h"
#include <sstream>

USING_NS_CC;

namespace CCMessageWindow {

    MessageQueue::MessageQueue()
    {
        
    }
    
    MessageQueue::~MessageQueue()
    {
        
    }
    
    bool MessageQueue::init()
    {
        return true;
    }
    
    void MessageQueue::pushMessage(const char *message)
    {
        _messages.push_back(message);
    }
    
    std::string MessageQueue::getCurrentMessage()
    {
        // TODO
        return _messages.front();
    }
    
    std::string MessageQueue::getCurrentWholeMessage()
    {
        return _messages.front();
    }
    
    
}