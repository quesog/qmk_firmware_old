// 0 DO
// 1 D1
// 2 D2
// 3 D3
// 4 D4
// 5 D5
// 6 D6
// 7 D7
// 8 B0
// 9 B1
// 10 B2
// 11 B3
// 12 B4
// 13 B5
// 14 C0
// 15 C1
// 16 C2
// 17 C3
// 18 C4
// 19 C5

// UP D3
// LF D6
// DN D7
// RH B0

// A  B1 Y
// B  B2 X
// C  B3 A
// D  B4 B

// MN C0
// SH C1
// SL C2
// ST B5

// L1 C3
// L2 C4
// L3 C5
// L4 C6
// L5 D7

matrix[0] = (
  (readPin(D3) << 0) |
  (readPin(D6) << 1) |
  (readPin(D7) << 2) |
  (readPin(B0) << 3) |
  (readPin(B1) << 4) |
  (readPin(B2) << 5) |
  (readPin(B3) << 6) |
  (readPin(B4) << 7)
  );
matrix[1] = (
  (readPin(C0) << 0) |
  (readPin(C1) << 1) |
  (readPin(C2) << 2) |
  (readPin(B5) << 3)
  );
matrix[2] = (
  (readPin(C3) << 0) |
  (readPin(C4) << 1) |
  (readPin(C5) << 2) |
  (readPin(C6) << 3) |
  (readPin(D7) << 4)
  );
