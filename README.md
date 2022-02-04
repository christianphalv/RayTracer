# Overview
This program reads a scene from an input file and renders the scene using a raytracer.
* Author: Christian Halvorson
* Date: 2/4/2022

# Specifications

## Make
This program comes with a Makefile that allows for easy compilation. Use the following commands to use the Makefile.
* `make` - Builds the program and creates and executable.
* `make run` - Builds the program if not up to date and runs the program with the `input/input.txt` file.
* `make clean` - Deletes binary and executable files.

## Executable
You can run this program with other input files or with auto-generated input. Use the following commands to generate images with other inputs.
* `./build/ratracer.exe ./input/input.txt` - Runs the program using the input file `./input/input.txt`.
* `./build/ratracer.exe` - Runs the program with the auto-generated input.

## Input File
The input file requires specific syntax. Each command must be on its own line and there must not be any empty lines. Below are the accepted commands. Bolded items are keywords and italicized items are placeholders for numbers.
* **eye** *pos_x* *pos_y* *pos_y* - Sets the position of the camera.
* **viewdir** *dir_x* *dir_y* *dir_z* - Sets the view direction of the camera.
* **updir** *dir_x* *dir_y* *dir_z* - Sets the up direction of the camera.
* **vfov** *fov_v* - Sets the vertical field of view in degrees.
* **imsize** *width* *height* - Sets the image size in pixels. (Must be positive integers)
* **bkgcolor** *red* *green* *blue* - Sets the background color of the image. (Must be numbers in range 0-1)
* **mtlcolor** *red* *green* *blue* - Sets the color of the next object. Every object after this command will have this color until another color is set. (Must be numbers in range 0-1)
* **sphere** *pos_x* *pos_y* *pos_y* *radius* - Creates a sphere.

## Output File
The output file will be generated as `output/input.ppm`, where `input` is the name of the input file. Output files are of type PPM, which requires a speciel program to view.