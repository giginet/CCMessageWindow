//
//  MessageWindow.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/10/20.
//
//

#include "MessageWindow.h"
#include <sstream>

const int kMAX_MESSAGE_QUEUE = 6;

const float kDefaultMessageWindowDelay = 0.75f;
const float kDefaultMessageWindowLastDelay = 2.0f;
const float kDefaultMessageWindowSpeed = 1.0f / 60.0f;

MessageWindow::MessageWindow(const char* fontName, float size, Size dimensions) {
  _messageQueue = Array::create();
  _messageQueue->retain();
  _textSpeed = 1;
  _textIndex = 0;
  _delay = kDefaultMessageWindowDelay;
  _lastDelay = kDefaultMessageWindowLastDelay;
  _label = LabelTTF::create("", fontName, size, dimensions, kCCTextAlignmentCenter, kCCVerticalTextAlignmentTop);
  _label->retain();
  _label->setColor(ccc3(255, 255, 255));
  _shadow = LabelTTF::create("", fontName, size, dimensions, kCCTextAlignmentCenter, kCCVerticalTextAlignmentTop);
  _shadow->retain();
  _shadow->setColor(ccc3(33, 33, 33));
  _shadow->setPosition(ccp(2, -2));
  this->setEnableShadow(true);
  this->addChild(_shadow);
  this->addChild(_label);
  _onFinishedFunction = NULL;
  _onUpdatedFunction = NULL;
  _ended = false;
  this->setMessageSpeed(kDefaultMessageWindowSpeed);
}

MessageWindow::~MessageWindow() {
  _messageQueue->release();
  _label->release();
  _shadow->release();
}

void MessageWindow::pushMessage(const wchar_t* message) {
  String* str = String::create(message);
  if (str->length() == 0) return;
  if (_messageQueue->count() > kMAX_MESSAGE_QUEUE) {
    _messageQueue->removeAllObjects();
  }
  if (this->isLastMessage() && this->isEndMessage()) { // 最後のメッセージで終わってたら
    this->unschedule(schedule_selector(MessageWindow::updateNextMessage));
    _messageQueue->addObject(str);
    this->updateNextMessage(NULL); // 強制的に次のメッセージに送ってやる
  } else {
    _messageQueue->addObject(str);
  }
}

void MessageWindow::update(float dt) {

}

VQString* MessageWindow::getCurrentWholeMessage() {
  if (_messageQueue->count() == 0) {
    return VQString::create();
  }
  VQString* vqs = (VQString*)_messageQueue->objectAtIndex(0);
  return vqs;
}

VQString* MessageWindow::getCurrentMessage() {
  return this->getCurrentWholeMessage()->substringWithRange(0, _textIndex);
}

void MessageWindow::setMessageSpeed(float speed) {
  _messageSpeed = speed;
  this->start();
}

void MessageWindow::start() {
  this->stop();
  this->schedule(schedule_selector(MessageWindow::updateNextText), _messageSpeed);
}

void MessageWindow::stop() {
  this->unschedule(schedule_selector(MessageWindow::updateNextText));
}

void MessageWindow::setOnMessageFinishedFunction(boost::function<void (VQString*, MessageWindow *)> finish) {
  _onFinishedFunction = finish;
}

void MessageWindow::setOnMessageUpdatedFunction(boost::function<void (VQString*, MessageWindow *)> update) {
  _onUpdatedFunction = update;
}

bool MessageWindow::isLastMessage() {
  return _messageQueue->count() == 1;
}

bool MessageWindow::isEndMessage() {
  return _textIndex >= this->getCurrentWholeMessage()->length();
}

void MessageWindow::setDelay(float d) {
  _delay = d;
}

void MessageWindow::setLastDelay(float d) {
  _lastDelay = d;
}

void MessageWindow::updateNextText(CCObject* sender) {
  _label->setString(this->getCurrentMessage()->getCString());
  if (_enableShadow) {
    _shadow->setString(this->getCurrentMessage()->getCString());
  }
  if (_messageQueue->count() == 0) return;
  if (this->isEndMessage()) return;
  if (_messageQueue->count() > 0 && _textIndex <= this->getCurrentWholeMessage()->length()) {
    if (_onUpdatedFunction) {
      int length = this->getCurrentWholeMessage()->length();
      _onUpdatedFunction(this->getCurrentWholeMessage()->substringWithRange(_textIndex, min(_textSpeed, length - _textIndex - 1)), this);
    }
    _textIndex += _textSpeed;
    // メッセージが終わったら、次のメッセージに
    if (!_ended && _textIndex > this->getCurrentWholeMessage()->length() - 1) {
      _ended = true;
      _textIndex = this->getCurrentWholeMessage()->length();
      if (_onFinishedFunction) {
        _onFinishedFunction(this->getCurrentWholeMessage(), this);
      }
      SEL_SCHEDULE sel = (SEL_SCHEDULE)schedule_selector(MessageWindow::updateNextMessage);
      this->scheduleOnce(sel, this->isLastMessage() ? _lastDelay : _delay); // ToDo ここで落ちる
    }
  }
}

void MessageWindow::updateNextMessage(CCObject* sender) {
  _ended = false;
  _textIndex = 0;
  _messageQueue->removeObjectAtIndex(0);
  this->unschedule(schedule_selector(MessageWindow::updateNextMessage));
}

void MessageWindow::finishMessage() {
  if (_ended) return;
  _textIndex = this->getCurrentWholeMessage()->length() - 2; // 最大文字-1文字
  this->updateNextText(this);
}

void MessageWindow::setTextSpeed(int textSpeed) {
  _textSpeed = textSpeed;
}

void MessageWindow::setEnableShadow(bool shadow) {
  _shadow->setVisible(shadow);
  _enableShadow = shadow;
}