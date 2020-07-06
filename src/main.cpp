/** Teensy 4.1 keyb firmware
 *
 * Credit to
 * https://forum.pjrc.com/threads/55395-Keyboard-simple-firmware for debouncing
 * inspiration.
 */

#include <array>

#include "handler.h"
#include "scanner.h"

static constexpr std::size_t kNumRows = 3;
static constexpr std::size_t kNumCols = 4;

static constexpr std::array<kb::Pin, kNumRows> kRowPins{10, 11, 12};
static constexpr std::array<kb::Pin, kNumCols> kColPins{2, 3, 4, 5};
static constexpr int kDebounce = 10;
static constexpr kb::Time kScanDelay = 5;

static constexpr std::array<kb::Key, kNumRows * kNumCols> kKeys{
    // Row 0
    KEY_ESC, KEY_MEDIA_MUTE, KEY_MEDIA_VOLUME_DEC, KEY_MEDIA_VOLUME_INC,
    // Row 1
    KEY_LEFT, KEY_DOWN, KEY_UP, KEY_RIGHT,
    // Row 2
    MODIFIERKEY_SHIFT, KEY_MEDIA_PAUSE, KEY_BACKSPACE, KEY_ENTER};

static auto scanner =
    kb::Scanner<kNumRows, kNumCols>(kRowPins, kColPins, kDebounce, kScanDelay);
static auto handler = kb::Handler<kNumRows, kNumCols>(kKeys);

void setup() {
  handler.Init();
  scanner.Init();
}

void loop() {
  scanner.Scan(handler);
}
