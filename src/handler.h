#ifndef HANDLER_H_
#define HANDLER_H_

#include <memory>

#include "context.h"

using Key = uint16_t;

class KeyHandler {
 public:
  virtual ~KeyHandler() = default;
  virtual KeyboardContext HandlePressed(KeyboardContext ctx) { return ctx; }
  virtual KeyboardContext HandleReleased(KeyboardContext ctx) { return ctx; }
};

class SimpleKeyHandler final : public KeyHandler {
 public:
  explicit SimpleKeyHandler(Key key) : key_{key} {}
  KeyboardContext HandlePressed(KeyboardContext ctx) override;
  KeyboardContext HandleReleased(KeyboardContext ctx) override;

  static std::unique_ptr<KeyHandler> Make(Key key);

 private:
  Key key_;
};

#endif  // HANDLER_H_
