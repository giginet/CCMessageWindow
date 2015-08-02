//
//  MessageWindow.h
//  MessageWindow
//
//  Created by giginet on 2012/10/20.
//
//

#ifndef __MessageWindow__MessageWindow__
#define __MessageWindow__MessageWindow__

#include "cocos2d.h"
#include <deque>

using namespace std;
using namespace cocos2d;

class MessageWindow :public Node {
  private:
    Array* _messageQueue;
    std::function<void (const wstring, MessageWindow*)> _onFinishedFunction;
    std::function<void (const wstring, MessageWindow*)> _onUpdatedFunction;
    int _textIndex;
    int _textSpeed;
    float _messageSpeed;
    void onMessageFinished();
    void onMessageUpdated();
    void update(float dt);
    float _delay;
    float _lastDelay;
    void updateNextMessage(Object* sender);
    void updateNextText(Object* sender);
    bool _ended;
    bool _enableShadow;
    LabelTTF* _label;
    LabelTTF* _shadow;
public:
    MessageWindow(const char* fontName, float size, Size dimensions);
    ~MessageWindow();
    void pushMessage(const wchar_t* message);
    void setMessageSpeed(float speed);
    void setOnMessageFinishedFunction(function<void (const wstring, MessageWindow*)> finish);
    void setOnMessageUpdatedFunction(function<void (const wstring, MessageWindow*)> update);
    wstring getCurrentMessage();
    wstring getCurrentWholeMessage();
    bool isLastMessage();
    bool isEndMessage();
    void setDelay(float d);
    void setLastDelay(float d);
    void start();
    void stop();
    void setTextSpeed(int textSpeed);
    void setEnableShadow(bool shadow);
    
    /**
     強制的にメッセージを終了させます
     */
    void finishMessage();
};

#endif /* defined(__MessageWindow__MessageWindow__) */
