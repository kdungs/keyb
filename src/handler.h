#ifndef KEYB_HANDLER_H_
#define KEYB_HANDLER_H_

#include <array>

#include "Arduino.h"
#include "Keyboard.h"

namespace kb {
using Key = std::uint16_t;

// Handler handles key presses and releases.
//
// For now, it can only send key codes from a predefined list through the
// Arduino Keyboard object.
template <std::size_t n_rows, std::size_t n_cols>
class Handler {
 public:
  explicit Handler(std::array<Key, n_rows * n_cols> keys) : keys_{keys} {}

  // Init initializes the underlying Keyboard object.
  void Init() { Keyboard.begin(); }

  // HandlePressed is called when a physical key is pressed on the board.
  // For now, it looks up the corresponding key code from a list and sends it
  // through the Arduino Keyboard.
  void HandlePressed(std::size_t idx) const { Keyboard.press(keys_[idx]); }

  // HandleReleased is called when a physical key is released on the board.
  // For now, it looks up the corresponding key code from a list and sends it
  // through the Arduino Keyboard.
  void HandleReleased(std::size_t idx) const { Keyboard.release(keys_[idx]); }

 private:
  std::array<Key, n_rows * n_cols> keys_;
};
}  // namespace kb

#endif  // KEYB_HANDLER_H_
