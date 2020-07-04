/** Teensy 4.1 keyb firmware
 *
 * Credit to
 * https://forum.pjrc.com/threads/55395-Keyboard-simple-firmware for debouncing
 * inspiration.
 */

#include "Arduino.h"
#include "Keyboard.h"

static constexpr int kDebounce = 10;
static constexpr int kScanDelay = 5;

static constexpr int kRowPins[] = {10, 11, 12};
static constexpr int kNumRows = 3;
static constexpr int kColPins[] = {2, 3, 4, 5};
static constexpr int kNumCols = 4;

// preliminary, for testing
static constexpr int kKeyMap[] = {
  KEY_ESC, KEY_MEDIA_MUTE, KEY_MEDIA_VOLUME_DEC, KEY_MEDIA_VOLUME_INC,
  KEY_LEFT, KEY_DOWN, KEY_UP, KEY_RIGHT,
  KEY_MEDIA_PLAY, KEY_MEDIA_PAUSE, KEY_BACKSPACE, KEY_ENTER
};

static int matrix[kNumRows * kNumCols] = {0};

void setup() {
  Keyboard.begin();

  // Set up row pins.
  // Only one is set to OUTPUT at a time for scanning.
  for (const int row : kRowPins) {
    pinMode(row, INPUT);
  }

  // Set up column pins.
  for (const int col : kColPins) {
    pinMode(col, INPUT_PULLUP);
  }

  for (int i = 0; i < kNumRows * kNumCols; i++) {
    matrix[i] = 0;
  }
}

void sendKey(int key, bool pressed) {
  const int msg = kKeyMap[key];
  if (pressed) {
    Keyboard.press(msg);
  } else {
    Keyboard.release(msg);
  }
}

void loop() {
  for (int r = 0; r < kNumRows; r++) {
    const int rowpin = kRowPins[r];
    pinMode(rowpin, OUTPUT);
    digitalWrite(rowpin, LOW);
    delay(1);

    for (int c = 0; c < kNumCols; c++) {
      const int colpin = kColPins[c];
      const int idx = r * kNumCols + c;
      const bool pressed = (digitalRead(colpin) == LOW);
      // De-bouncing logic.
      if (matrix[idx] == 0 && pressed) {
        // Key was pressed.
        matrix[idx] = kDebounce * 2;
        sendKey(idx, true);
      } else if (matrix[idx] == kDebounce && !pressed) {
        // Key was released.
        matrix[idx]--;
        sendKey(idx, false);
      } else if (matrix[idx] != kDebounce && matrix[idx] > 0) {
        matrix[idx]--;
      }
    }
    pinMode(rowpin, INPUT);
  }
  delay(kScanDelay);
}
