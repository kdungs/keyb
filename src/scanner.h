#ifndef KEYB_SCANNER_H_
#define KEYB_SCANNER_H_

#include <array>

#include "Arduino.h"
#include "handler.h"

namespace kb {
using Pin = std::uint8_t;
using Time = std::uint32_t;

// Scanner can scan a keyboard matrix of `n_rows` rows and `n_cols` cols that
// are connected to specific pins on the Teensy.
// It can determine whether a key was pressed or released and passes those
// events to a dedicated handler.
template <std::size_t n_rows, std::size_t n_cols>
class Scanner {
 public:
  Scanner(std::array<Pin, n_rows> rows,
          std::array<Pin, n_cols> cols,
          int debounce,
          Time scan_delay)
      : rows_{rows},
        cols_{cols},
        debounce_{debounce},
        scan_delay_{scan_delay},
        matrix_{0} {}

  // Init initializes the Scanner.
  void Init() {
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
  void Scan(Handler<n_rows, n_cols>& handler) {
    for (std::size_t r = 0; r < n_rows; r++) {
      const Pin rowpin = rows_[r];
      pinMode(rowpin, OUTPUT);
      digitalWrite(rowpin, LOW);
      delay(1);
      for (std::size_t c = 0; c < n_cols; c++) {
        const Pin colpin = cols_[c];
        const std::size_t idx = r * n_cols + c;
        const bool pressed = (digitalRead(colpin) == LOW);
        // De-bouncing logic.
        if (matrix_[idx] == 0 && pressed) {
          // Key was pressed.
          matrix_[idx] = 2 * debounce_;
          handler.HandlePressed(idx);
        } else if (matrix_[idx] == debounce_ && !pressed) {
          // Key was released.
          matrix_[idx]--;
          handler.HandleReleased(idx);
        } else if (matrix_[idx] != debounce_ && matrix_[idx] > 0) {
          matrix_[idx]--;
        }
      }
      pinMode(rowpin, INPUT);
    }
    delay(scan_delay_);
  }

 private:
  const std::array<Pin, n_rows> rows_;
  const std::array<Pin, n_cols> cols_;
  const int debounce_;
  const Time scan_delay_;
  std::array<int, n_rows * n_cols> matrix_;
};
}  // namespace kb

#endif  // KEYB_SCANNER_H_
