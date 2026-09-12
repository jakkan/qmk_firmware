/*
Copyright 2020 Pierre Chevalier <pierrechevalier83@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

// The halves share 5V over the TRRS cable and these controllers don't isolate
// the VBUS pad from that rail, so the unplugged half reads VBUS high, declares
// itself master too, and neither side ever runs the slave loop. Deciding on an
// actual USB address instead of VBUS picks the plugged half every time. Costs
// the slave up to SPLIT_USB_TIMEOUT (2 s) before it starts scanning.
#define SPLIT_USB_DETECT

// No handedness detection is configured, here or in the keyboard, so QMK falls
// back to MASTER_LEFT: the half holding the cable is the left half. Keep the
// cable in the left half. See the README for the EE_HANDS alternative.

// The other Sweep has its right half wired in reverse: physical inner-index
// column sits on the pin a stock right half uses for the pinky, and so on.
// Scanning that half with the LEFT pin map undoes it, so one layout serves
// both boards. Build with:  qmk compile ... -e MIRRORED_RIGHT=yes
#ifdef MIRRORED_RIGHT
#    undef DIRECT_PINS_RIGHT
#    define DIRECT_PINS_RIGHT DIRECT_PINS
#endif
// Set the mouse settings to a comfortable speed/accuracy trade-off,
// assuming a screen refresh rate of 60 Htz or higher
// The default is 50. This makes the mouse ~3 times faster and more accurate
#define MOUSEKEY_INTERVAL 16
// The default is 20. Since we made the mouse about 3 times faster with the previous setting,
// give it more time to accelerate to max speed to retain precise control over short distances.
#define MOUSEKEY_TIME_TO_MAX 40
// The default is 300. Let's try and make this as low as possible while keeping the cursor responsive
#define MOUSEKEY_DELAY 100
// It makes sense to use the same delay for the mouseweel
#define MOUSEKEY_WHEEL_DELAY 100
// The default is 100
#define MOUSEKEY_WHEEL_INTERVAL 50
// The default is 40
#define MOUSEKEY_WHEEL_TIME_TO_MAX 100

// I've tried 200, it caused mo to accidentally activate hold more than I liked
#define TAPPING_TERM 220
#define PERMISSIVE_HOLD
#define QUICK_TAP_TERM 0

// Underglow configuration
#ifdef RGBLIGHT_ENABLE
#    define RGBLIGHT_EFFECT_BREATHING
#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#    define RGBLIGHT_EFFECT_SNAKE
#    define RGBLIGHT_EFFECT_KNIGHT
#    define RGBLIGHT_EFFECT_CHRISTMAS
#    define RGBLIGHT_EFFECT_STATIC_GRADIENT
#    define RGBLIGHT_EFFECT_RGB_TEST
#    define RGBLIGHT_EFFECT_ALTERNATING
#    define RGBLIGHT_EFFECT_TWINKLE
#    define RGBLIGHT_HUE_STEP 8
#    define RGBLIGHT_SAT_STEP 8
#    define RGBLIGHT_VAL_STEP 8
#endif
