#include "rev1_4knob.h"

// LAYOUT マクロの実装
#define LAYOUT( \
    l00, l01, l02, l03, l04, l05, \
    l10, l11, l12, l13, l14, l15, \
    l20, l21, l22, l23, l24, l25, \
    l30, l31, l32, l33, l34, l35, \
    l40, l41, l42, l43, l44, l45, \
    l50, l51, l52, l53, l54, l55, \
    r00, r01, r02, r03, r04, r05, \
    r10, r11, r12, r13, r14, r15, \
    r20, r21, r22, r23, r24, r25, \
    r30, r31, r32, r33, r34, r35, \
    r40, r41, r42, r43, r44, r45, \
    r50, r51, r52, r53, r54, r55  \
) { \
    { l00, l01, l02, l03, l04, l05 }, \
    { l10, l11, l12, l13, l14, l15 }, \
    { l20, l21, l22, l23, l24, l25 }, \
    { l30, l31, l32, l33, l34, l35 }, \
    { l40, l41, l42, l43, l44, l45 }, \
    { l50, l51, l52, l53, l54, l55 }, \
    { r00, r01, r02, r03, r04, r05 }, \
    { r10, r11, r12, r13, r14, r15 }, \
    { r20, r21, r22, r23, r24, r25 }, \
    { r30, r31, r32, r33, r34, r35 }, \
    { r40, r41, r42, r43, r44, r45 }, \
    { r50, r51, r52, r53, r54, r55 } \
}

void define_layout_impl(void) {
    // 実装は空でOK
}