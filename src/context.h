#ifndef CONTEXT_H_
#define CONTEXT_H_

#include "Arduino.h"
#include "Keyboard.h"

class KeyboardContext {
 public:
  void Press(int key) { Keyboard.press(key); }

  void Release(int key) { Keyboard.release(key); }
};

#endif  // CONTEXT_H_
