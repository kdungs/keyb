#include "handler.h"

KeyboardContext SimpleKeyHandler::HandlePressed(KeyboardContext ctx) {
  ctx.Press(key_);
  return ctx;
}

KeyboardContext SimpleKeyHandler::HandleReleased(KeyboardContext ctx) {
  ctx.Release(key_);
  return ctx;
}

/*static*/
std::unique_ptr<KeyHandler> SimpleKeyHandler::Make(Key key) {
  return std::make_unique<SimpleKeyHandler>(key);
}
