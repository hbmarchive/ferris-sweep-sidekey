# Hannah's Sidekey Ferris Sweep Layout

This is an evolution of the first 34-key layout I designed for my Ferris Sweep.
I have tried to place layer keys in various positions and I have come to the
conclusion that - for me at least - thumb keys are too important to use for
layer switching or overloading to be used in multiple ways.

Instead I have overloaded two keys at the lower left- and right-sides of the
keyboard, freeing up the thumb keys to provide `Shift`, `Space`, `Enter` and
`Escape`. Tapping the `Left` key enters a **left tap** layer for a single
keypress whereas holding down the `Left` key enters a **left hold** layer until
the key is released. The `Right` key accesses the **right tap** and **right
hold** layers in the same way.

Double-tapping the layer keys accesses the keypress that the layer key
overloaded. So double-tapping `Left` produces a `Z` and double-tapping `Right`
produces `/`.

That sounds like a lot of functionality but for the most part it flows nicely.
The commonly used keypresses are on the right layers: mostly you will be
right-tapping for punctuation and right-holding for numbers, with a bit of
left-holding for navigation.

### Credit

Once again, I want to give credit and a massive amount of thanks to [Ben
Vallack](https://www.youtube.com/benvallack) for talking through his
tap-not-hold approach and for all of his inspirational work on ergonomic
keyboards and layouts. My initial layout drew heavily from his [Ferris Sweep
layout](https://github.com/benvallack/34-QMK-Ferris-Sweep).

The contributers who make QMK possible are an incredible bunch of people and the
ErgoMechKeyboard community as a whole has been welcoming and helpful. Please
support open source projects and communities.

## Layers

### Base Layer

![Base Layer](https://imgur.com/aOX8l2Q.png)

The base layer is set out in the Colemak Mod-DH format with a `Backspace` key at
the top right-hand side instead of a semicolon key. Holding shift and pressing
the `Backspace` key will send `Delete`.

The top row has home row style modifier keys available:

* The `W` and `Y` keys produce `Ctrl` when held down
* The `F` and `U` keys produce `Alt` (or `Option`) when held down
* The `P` and `L` keys produce `Win` (or `Cmd` or `Search`) when held down

The `Left` and `Right` layer keys are explained above.

### Right Tap Layer

![Right Tap Layer](https://imgur.com/a65EAnw.png)

This layer contains symbols. The top row has symbols usually found on the number
keys. The symbols that usually appear on the right of the keyboard next to the
`Enter` key are on the right side. Braces and brackets are paired off on the
left side alongside `\` and `|`, where they appear on UK ISO keyboards. Finally
`Tab` and `Caps Lock` are on the far left.

### Right Hold Layer

![Right Hold Layer](https://imgur.com/3dqSy44.png)

This layer contains numbers in a keypad-like layout. Both hold layers have cut
and paste keyboard shortcuts on the thumb keys.

### Left Tap Layer

![Left Tap Layer](https://imgur.com/7rmIZNn.png)

### Left Hold Layer

![Left Hold Layer](https://imgur.com/Do563rD.png)
