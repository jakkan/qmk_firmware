# jakkan — Ferris Sweep

Colemak Mod-DH on 34 keys, with home-row mods and six layers. One layout,
built two ways to cover two boards with differently wired right halves.

## One-time setup

Toolchain and uv, on Fedora:

    sudo dnf install avr-gcc avr-libc avr-binutils avrdude dfu-programmer uv

The QMK CLI goes in a repo-local venv at `.venv/` (gitignored), which `uv run`
picks up automatically from the repo root:

    uv venv
    uv pip install qmk -r requirements.txt
    uv run qmk git-submodule

Flashing needs udev rules, or avrdude won't see the bootloader without root:

    sudo cp util/udev/50-qmk.rules /etc/udev/rules.d/
    sudo udevadm control --reload-rules && sudo udevadm trigger

`uv run qmk doctor` checks the result.

## Build

Every `qmk` command below is prefixed with `uv run` so it resolves to that
venv; drop the prefix if you have `qmk` on your PATH some other way.

    # stock wiring
    uv run qmk compile -kb ferris/sweep -km jakkan

    # board whose right half is wired in reverse
    uv run qmk compile -kb ferris/sweep -km jakkan -e MIRRORED_RIGHT=yes

## Flash

Both halves run the same firmware, so each one gets flashed separately over its
own USB cable. Swap `compile` for `flash` and keep the same flags:

    uv run qmk flash -kb ferris/sweep -km jakkan            # once per half

To get a half into the bootloader, either press its reset button, or hold the
top outer key while plugging that half in — `Q` on the left, `'` on the right.
Note that the key-hold route is bootmagic, which also invalidates the EEPROM
settings block; the reset button doesn't. Either is fine here — nothing in this
build depends on EEPROM state, so there is no per-half setup step and no
first-time flash that differs from any later one.

In use, the USB cable goes in the **left** half; see below.

## Layout

```
 Q  W  F  P  B      J  L  U  Y  '
 A  R  S  T  G      M  N  E  I  O     <- home-row mods
 Z  X  C  D  V      K  H  ,  .  /
        SPC TAB    ENT BSPC
```

Home-row mods run outward from the index finger on both hands, so the halves
mirror each other: `RALT LSFT LGUI LALT LCTL` reading pinky-ward.

Each thumb is a layer-tap:

| Thumb       | Tap   | Hold  |
|-------------|-------|-------|
| left outer  | Space | `NAV` |
| left inner  | Tab   | `MOU` |
| right inner | Enter | `SYM` |
| right outer | Bksp  | `NUM` |

`SHF` and `FUN` come from chording the two right thumbs: `NUM`+inner gives
`SHF`, `SYM`+outer gives `FUN`.

## Why `MIRRORED_RIGHT`

The layout is written once, in normal column order — on every row the
right-half keys run inner-index to pinky, mirroring the left half.

One of the two Sweeps has its right half wired in reverse: the physical
inner-index column sits on the pin a stock right half uses for the pinky, and
so on outward. Rather than maintain the keycodes in two orders, `config.h`
redefines `DIRECT_PINS_RIGHT` to the left pin map for that board, which is the
stock right map reversed row by row, and scans the reversed wiring back into
the right order. `rules.mk` turns `-e MIRRORED_RIGHT=yes` into the define.

## Handedness and master detection

Two separate questions, and this keymap answers them differently.

**Which half am I?** `ferris/sweep` configures no handedness detection of its
own and this keymap adds none, so QMK falls back to `MASTER_LEFT`: whichever
half holds the USB cable *becomes* the left half. Keep the cable in the left
half — plugging into the right silently mirrors the board. The payoff is that
neither half needs anything written to its EEPROM: one image, flashed to both,
no per-side setup.

`EE_HANDS` is the alternative — handedness stored per half in EEPROM, so either
side can hold the cable. It costs a one-time `-bl avrdude-split-left` /
`-bl avrdude-split-right` flash per half, and until that byte is written an
erased EEPROM reads `0xFF`, which QMK takes as *left* on both halves and the
board appears dead.

**Which half talks to the computer?** That is `SPLIT_USB_DETECT`, and it is
required on these boards. The halves share 5V over the TRRS cable and the
controllers don't isolate the VBUS pad from that rail, so without the macro the
unplugged half reads VBUS high, declares itself master as well, and neither side
ever runs the slave loop. With it, master detection instead waits for a host to
actually assign a USB address — up to `SPLIT_USB_TIMEOUT`, 2 s — which only the
plugged half ever gets. The trade is that the slave half takes up to those 2 s
after power-up to begin scanning.

## Known quirk

On `NAV` and `MOU` the left thumb pair is swapped: `MO(SHF)` sits on the same
key as `LT(NAV, KC_SPC)` and `MO(FUN)` on the same key as `LT(MOU, KC_TAB)`, so
each is under the thumb already holding that layer, and unreachable. Harmless —
`SHF` and `FUN` are still reachable via the right-thumb chords above — but the
free thumb on each of those layers is a wasted `KC_NO`.
