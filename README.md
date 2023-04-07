# ray.0462

## Graphics application demo

Adapted from https://github.com/phantomics/demo.ray .

### Running the demo

Run the demo:

```
cd ray.0462/src
./demo
```

A window will appear in which you fly through a rolling 3D landscape of random
blocks.  You can use the arrow keys to move in various ways, or some other keys
like S, W, A, and D.

## Test

The following script assembles the demo code and diffs it against a reference
output.  I use it as I refactor the code, as a gauge of size and speed.  When
I see a change that is acceptable, I copy the tmp/demo.s back into ref/demo.s.

```
./test_asm
```

## Utilities

The demo script automatically builds the code and runs it, but you can also run
the build script directly if you like, e.g.:

```
./build         # Build anything out of date
./build clean   # Force a full build
./build erase   # Erase build output files
```

## Prerequisites

### Raylib

Here are some instructions on installing raylib:

https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux

Typically:
```
sudo apt install libasound2-dev mesa-common-dev libx11-dev libxrandr-dev libxi-dev xorg-dev libgl1-mesa-dev libglu1-mesa-dev

git clone https://github.com/raysan5/raylib.git raylib
cd raylib
mkdir build && cd build
cmake -DBUILD_SHARED_LIBS=ON ..
make
sudo make install

cd src
make
```

I installed raylib one level above my ray.0462 directory, and then I linked it
locally with:

```
cd ray.0462
ln -s ../raylib .
```
