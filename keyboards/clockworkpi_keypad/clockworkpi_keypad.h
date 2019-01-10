

#define k_ KC_NO

#define LAYOUT_keymap( \
    kMN, kSH,    kSL, kST, \
       kUP,        KY, \
    kLF, kRH,    kX, kB, \
       kDN,        kA, \
  kL1, kL2, kL3, kL4, kL5 \
) { \
  { kUP, kLF, kDN, kRH, kY,  kX, kA, kB }, \
  { kMN, kSH, kSL, kST, k_,  k_, k_, k_ }, \
  { kL1, kL2, kL3, kL4, kL5, k_, k_, k_ }, \
}
