#ifndef KEYB_H_
#define KEYB_H_

#include <array>

#include "Arduino.h"
#include "Keyboard.h"

#include "context.h"
#include "handler.h"

using Pin = uint8_t;
using Time = uint32_t;

namespace {
static std::array<std::unique_ptr<KeyHandler>, 12> kKeyMap{
    // Row 0
    SimpleKeyHandler::Make(KEY_ESC), SimpleKeyHandler::Make(KEY_MEDIA_MUTE),
    SimpleKeyHandler::Make(KEY_MEDIA_VOLUME_DEC),
    SimpleKeyHandler::Make(KEY_MEDIA_VOLUME_INC),
    // Row 1
    SimpleKeyHandler::Make(KEY_LEFT), SimpleKeyHandler::Make(KEY_DOWN),
    SimpleKeyHandler::Make(KEY_UP), SimpleKeyHandler::Make(KEY_RIGHT),
    // Row 2
    SimpleKeyHandler::Make(KEY_MEDIA_PLAY),
    SimpleKeyHandler::Make(KEY_MEDIA_PAUSE),
    SimpleKeyHandler::Make(KEY_BACKSPACE), SimpleKeyHandler::Make(KEY_ENTER)};
}  // namespace

template <std::size_t ROWS, std::size_t COLS>
class Keyb {
 public:
  Keyb(std::array<Pin, ROWS> rows,
       std::array<Pin, COLS> cols,
       int debounce,
       Time scan_delay)
      : rows_{rows},
        cols_{cols},
        debounce_{debounce},
        scan_delay_{scan_delay},
        matrix_{0} {}

  // Init initializes the Keyb.
  // This also intializes the underlying Arduino Keyboard driver.
  void Init() {
    Keyboard.begin();
    // Set up row pins.
    // Only one is set to OUTPUT at a time for scanning.
    for (const Pin row : rows_) {
      pinMode(row, INPUT);
    }
    // Set up column pins
    for (const Pin col : cols_) {
      pinMode(col, INPUT_PULLUP);
    }
  }

  // Scan scans the matrix for keypresses, handles debouncing and
  // calls the handler functions for key presses and releases.
  void Scan() {
    for (std::size_t r = 0; r < ROWS; r++) {
      const Pin rowpin = rows_[r];
      pinMode(rowpin, OUTPUT);
      digitalWrite(rowpin, LOW);
      delay(1);
      for (std::size_t c = 0; c < COLS; c++) {
        const Pin colpin = cols_[c];
        const std::size_t idx = r * COLS + c;
        const bool pressed = (digitalRead(colpin) == LOW);
        // De-bouncing logic.
        if (matrix_[idx] == 0 && pressed) {
          // Key was pressed.
          matrix_[idx] = 2 * debounce_;
          HandlePressed(idx);
        } else if (matrix_[idx] == debounce_ && !pressed) {
          // Key was released.
          matrix_[idx]--;
          HandleReleased(idx);
        } else if (matrix_[idx] != debounce_ && matrix_[idx] > 0) {
          matrix_[idx]--;
        }
      }
      pinMode(rowpin, INPUT);
    }
    delay(scan_delay_);
  }

  // HandlePressed is called when the key at index `idx` has been
  // determined pressed after debouncing.
  void HandlePressed(std::size_t idx) const {
    kKeyMap[idx]->HandlePressed(KeyboardContext{});
  }

  // HandleReleased is called when the key at index `idx` has been
  // determined released after debouncing.
  void HandleReleased(std::size_t idx) const {
    kKeyMap[idx]->HandleReleased(KeyboardContext{});
  }

 private:
  const std::array<Pin, ROWS> rows_;
  const std::array<Pin, COLS> cols_;
  const int debounce_;
  const Time scan_delay_;
  std::array<int, ROWS * COLS> matrix_;
};

// MakeKeyb creates a Keyb object while inferring the template
// arguments from the two arrays passed in.
template <std::size_t ROWS, std::size_t COLS>
constexpr Keyb<ROWS, COLS> MakeKeyb(std::array<Pin, ROWS> rows,
                                    std::array<Pin, COLS> cols,
                                    int debounce,
                                    Time scan_delay) {
  return Keyb<ROWS, COLS>(rows, cols, debounce, scan_delay);
}

#endif  // KEYB_H_
