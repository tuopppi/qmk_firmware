# tuopppi/chocofi

38-key column-aligned keyboard with a built-in PMW3360 pointing device.
RP2040, 4×10 matrix (COL2ROW), NKRO.

## Flash

```
make tuopppi/chocofi:default:flash
```

Install QMK cli:

```
uv tool install qmk
```

![chocofi keymap](chocofi.png)

## Layout

The letter layout is derived from
[Minimak](https://github.com/binaryphile/minimak) — binaryphile's
bigram-frequency-optimized layout, specifically the full 12-key variant
(19 of 26 letter slots identical) — adapted for Finnish:

- **V↔F** swap (Minimak has R↔F; F is rare in Finnish, 0.19%)
- **no L↔O** swap (Finnish L 5.8% ≈ O 5.6%, so L stays on the home row)
- **Ö** in the P slot, **'** in the / slot
- ö/ä are emitted as `RALT+O` / `RALT+A`, matching the EurKey host layout

```
 col  0    1    2    3    4     5    6    7    8    9
      ESC   W    D    R    K     Y    U    I    O    F12
      Q     S    T    V    G     H    N    E    L    Ö
      A     X    C    F    B     J    M    ,    .    P
      Z         NUM  Ä   SYM     SP   ⌫   ⌘M           '
```

- Columns are aligned (no ANSI row stagger), so the Enter chord (E+L) and
  the Tab chord (,+.) sit in the same two columns, one row apart.
- The pinkies are short, so they rest on **A/P**, 1U below the
  ring/middle/index home row `S T V G H N E L`.
  Effective home row: `A S T V G | H N E L P`.
- ~58% of Finnish text is at zero-travel rest positions (QWERTY: ~38%).

## Home row mods

Tap = letter, hold = mod (macOS/iOS / non-Apple via host OS detection).
macOS and iOS detection results use the same modifier assignments.
All tap/hold resolution is done by
[sm_td](https://github.com/stasmarkin/sm_td).

| Key | Hold |
|-----|------|
| A   | L⌃ / L⌘ |
| S   | L⌥ |
| T   | L⌘ / L⌃ |
| V, Z | L⇧ |
| N   | R⇧ |
| E   | R⌘ / R⌃ |
| L   | R⌥ |
| P   | R⌃ / R⌘ |

Only G and H are plain letters. **Ä** (thumb key) is a layer tap:
tap = ä, hold = MOUSE layer.

## Combos

| Chord | Action |
|-------|--------|
| E+L   | Enter |
| ,+.   | Tab |
| C+F   | mouse left |
| X+C   | mouse middle |
| SYM+Space | toggle MOUSE layer |
| W+D+I+O | reset to bootloader (fallback) |

F double-tap = mouse left; Bksp double-tap = ⌥Bksp (delete word).

## Mouse

PMW3360 on SPI0, 1000 CPI. Pointing is always active; **holding SYM
converts pointer motion to scroll**. The MOUSE layer (Ä hold, or the
SYM+Space combo) has MS_BTN1–5, screenshots, and QK_BOOT.

## Layers

| Layer | Contents |
|-------|----------|
| DEFAULT | letters, mods, combos |
| SYM | symbols, Caps Word toggle, ⌘Z / Ctrl+⌘Z |
| NUM | arrows, F1/F2, HOME/END, ⌘X/⌘C/⌘V, numpad, Del |
| MOUSE | MS_BTN1–5, screenshots, QK_BOOT |
