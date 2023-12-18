# BMP_X11



BMP X11 is a library and example that allows you to view BMP (Bitmap) image files using X11 libraries.
Overview

This project provides a simple library to handle BMP files and a basic example showcasing how to use it with X11 for image display.
Features

    BMP File Support: Easily load and display BMP image files.
    X11 Integration: Utilize X11 libraries for image rendering on Unix-like systems.
![Sample Image](./assets/Naqsh_20231218073625.png)
Getting Started
Prerequisites

    Ensure you have the X11 development libraries installed on your system.

Installation

    Clone the repository:

    bash

git clone https://github.com/masoud4/bmp-x11.git

Build the project:

bash

    cd bmp-x11
    make

Usage

    Include the necessary headers in your code:

    c

#include "bmp.h"

Link against the BMP X11 library during compilation:

bash

    gcc yourfile.c -o yourfile -lbmpx11

    Use the library functions to load and display BMP images.

Example

Here's a minimal example demonstrating how to use BMP X11 to display a BMP image:

c

#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main() {
    // Initialize BMP structure
    BMP bmp;
    bmp_init(&bmp);

    // Load BMP image
    if (bmp_load("example.bmp", &bmp) != BMP_OK) {
        fprintf(stderr, "Error loading BMP file\n");
        return EXIT_FAILURE;
    }

    // Display BMP image using X11
    bmp_display_x11(&bmp);

    // Cleanup
    bmp_free(&bmp);

    return EXIT_SUCCESS;
}

License

This project is licensed under the MIT License - see the LICENSE file for details.