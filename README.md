# A Simple C++ Ray Tracer

## Project Description

Author: Kairong Jiang

This project implements a distribution ray tracer, with advanced effects such as anti-aliasing, depth of field, glossy reflaction and refraction, and hard shadow.

The number of samples can be modified at run time.

There is also an option to switch to a simple ray tracer with diffuse, specular and ambient shading models.

A custom scene file ```myscene.txt``` is provided (credit to Dr. Joshua Levine) to illustrated the effects of the distribution ray tracer. ```myscene.ppm``` is the result of 100 samples.

## User Instructions

### System Requirements

* CMake 2.8 or newer
* C++ compiler with C++11 support (gcc 4.8.1 or newer, or Clang 3.3 or newer)
* SDL2 library

### Build and Run
Build the program using ```cmake```.

Run the program with the relative path to the scene txt file set as program argument.

e.g. 

```mkdir build```

```cd build```

```cmake ..```

```make```

```./simple_raytrace ../myscene.txt```

The program will show the image rendered by the ray tracer. By default, simple ray tracer will be used. You can perform the following keyboard operations:

* press ```d``` to change between simple ray tracer and distribution ray tracer.

* when in distribution mode:
    * press ```n``` to decrease number of samples.
    * press ```k``` to increase number of samples.
   