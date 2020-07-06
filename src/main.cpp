/** Teensy 4.1 keyb firmware
 *
 * Credit to
 * https://forum.pjrc.com/threads/55395-Keyboard-simple-firmware for debouncing
 * inspiration.
 */

#include "keyb.h"

static constexpr auto kRowPins = std::array<Pin, 3u>{10, 11, 12};
static constexpr auto kColPins = std::array<Pin, 4u>{2, 3, 4, 5};
static constexpr int kDebounce = 10;
static constexpr Time kScanDelay = 5;

static auto kb = MakeKeyb(kRowPins, kColPins, kDebounce, kScanDelay);

void setup() {
  kb.Init();
}

void loop() {
  kb.Scan();
}
