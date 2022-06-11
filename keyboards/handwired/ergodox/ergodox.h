#pragma once

#include "quantum.h"

#define XXX KC_NO

#define LAYOUT_default(\
L01, L02, L03, L04, L05, L06, L07,                          R01, R02, R03, R04, R05, R06, R07, \
L08, L09, L10, L11, L12, L13, L14,                          R08, R09, R10, R11, R12, R13, R14, \
L15, L16, L17, L18, L19, L20, L21, L22, L23,      R15, R16, R17, R18, R19, R20, R21, R22, R23, \
L24, L25, L26, L27, L28, L29, L30, L31, L32,      R24, R25, R26, R27, R28, R29, R30, R31, R32, \
L33, L34, L35, L36, L37, L38,           L39,      R33,           R34, R35, R36, R37, R38, R39  \
) \
{ \
{ L01, L02, L03, L04, L05, L06, L07, XXX, XXX }, \
{ L08, L09, L10, L11, L12, L13, L14, XXX, XXX }, \
{ L15, L16, L17, L18, L19, L20, L21, L22, L23 }, \
{ L24, L25, L26, L27, L28, L29, L30, L31, L32 }, \
{ L33, L34, L35, L36, L37, L38, XXX, XXX, L39 }, \
{ XXX, XXX, R01, R02, R03, R04, R05, R06, R07 }, \
{ XXX, XXX, R08, R09, R10, R11, R12, R13, R14 }, \
{ R15, R16, R17, R18, R19, R20, R21, R22, R23 }, \
{ R24, R25, R26, R27, R28, R29, R30, R31, R32 }, \
{ R33, XXX, XXX, R34, R35, R36, R37, R38, R39 }  \
}
