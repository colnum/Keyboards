/* Copyright 2020 Ito
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "quantum.h"

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */

#define LAYOUT( \
    kL00, kL01, kL02, kL03, kL04, kL05, \
    kL10, kL11, kL12, kL13, kL14, kL15, \
    kL20, kL21, kL22, kL23, kL24, kL25, \
    kL30, kL31, kL32, kL33, kL34, kL35, \
    kR00, kR01, kR02, kR03, kR04, kR05, \
    kR10, kR11, kR12, kR13, kR14, kR15, \
    kR20, kR21, kR22, kR23, kR24, kR25, \
    kR30, kR31, kR32, \
    kC00, kC01, kC02  \
) \
{ \
    { kL00, kL01, kL02, kL03, kL04, kL05 }, \
    { kL10, kL11, kL12, kL13, kL14, kL15 }, \
    { kL20, kL21, kL22, kL23, kL24, kL25 }, \
    { kL30, kL31, kL32, kL33, kL34, kL35 }, \
    { kR00, kR01, kR02, kR03, kR04, kR05 }, \
    { kR10, kR11, kR12, kR13, kR14, kR15 }, \
    { kR20, kR21, kR22, kR23, kR24, kR25 }, \
    { kR30, kR31, kR32, kC00, kC01, kC02 }  \
}
