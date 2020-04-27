# InvasiveSpeciesCPP
C++ implementation for [InvasiveSpecies](https://github.com/yanfrimmel/InvasiveSpecies) 

![Example](ExampleCPP.png)

## Features

* Tile based grid.
* Player avatar follows mouse press.
* Frames per seconds counter.
* Camera that follows the player in world coordinates.
* A living world: 
    * NPC's can eat.
    * NPC's can drink.
    * NPC's can reproduce.
    * NPC's travel to random directions.
    * Plants grow with time providing food for the animals.
* Player can eat, drink, and reproduce by moving close to the appropriate game objects.    

* Will be continued...

## How to use

### Prerequisites

This game uses SDL2, SDL_Image, and SDL_ttf, you need to have them installed in your system.

### To build on Linux

```bash
    mkdir build
    cd build
    cmake ..
    make
```

### To run

```bash
    cd build
    ./InvasiveSpeciesCPP {SCREEN_WIDTH} {SCREEN_HEIGHT} {IS_FULL_SCREEN}
