/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

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

#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#undef TAPPING_TERM
#define TAPPING_TERM 200
#define ONESHOT_TAP_TOGGLE 5 /* Tapping this number of times holds the key until tapped this number of times again. */
#define ONESHOT_TIMEOUT 5000 /* Time (in ms) before the one shot key is released */

// #undef OLED_FONT_H
// #define OLED_FONT_H "helixfont.h"
// #define OLED_FONT_H "keyboards/helix/rev3_5rows/keymaps/froggy/helixfont.h"

// If you need more program area, try select and reduce rgblight modes to use.

// Selection of RGBLIGHT MODE to use.
// #ifdef RGBLIGHT_ENABLE
//    //#define RGBLIGHT_EFFECT_BREATHING
//    //#define RGBLIGHT_EFFECT_RAINBOW_MOOD
//    //#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
//    //#define RGBLIGHT_EFFECT_SNAKE
//    #define RGBLIGHT_EFFECT_KNIGHT
//    //#define RGBLIGHT_EFFECT_CHRISTMAS
//    //#define RGBLIGHT_EFFECT_STATIC_GRADIENT
//    //#define RGBLIGHT_EFFECT_RGB_TEST
//    //#define RGBLIGHT_EFFECT_ALTERNATING
// #endif


#undef RGBLIGHT_EFFECT_BREATHING
// #undef RGBLIGHT_EFFECT_RAINBOW_MOOD
// #undef RGBLIGHT_EFFECT_RAINBOW_SWIRL
#undef RGBLIGHT_EFFECT_SNAKE
// #undef RGBLIGHT_EFFECT_KNIGHT
#undef RGBLIGHT_EFFECT_CHRISTMAS
#undef RGBLIGHT_EFFECT_STATIC_GRADIENT
#undef RGBLIGHT_EFFECT_RGB_TEST
#undef RGBLIGHT_EFFECT_ALTERNATING

#endif /* CONFIG_USER_H */

