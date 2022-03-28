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
* **mtlcolor** *albedoRed* *albedoGreen* *albedoBlue* *specularRed* *specularGreen* *specularBlue* *ambientK* *diffuseK* *specularK* *specularExponent* *opacity* *indexOfRefraction* - Sets the material of the next object. Every object after this command will have this material until another material is set. (Colors and Ks must be numbers in range 0-1)
* **texture** *texture.ppm* - Sets a textured material for the next objects.
* **plane** *n_x* *n_y* *n_z* *pos_x* *pos_y* *pos_z* - Creates a plane.
* **sphere** *pos_x* *pos_y* *pos_z* *radius* - Creates a sphere.
* **v** *pos_x* *pos_y* *pos_z* - Creates a triangle vertex.
* **vn** *n_x* *n_y* *n_z* - Creates a triangle normal.
* **vt** *u* *v* - Texture coordinates of a vertex.
* **f** *v_1* *v_2* *v_3* - Creates a triangle from three vertices.
* **f** *v_1//vn_1* *v_2//vn_2* *v_3//vn_3* - Creates a smooth shaded triangle from three vertices and normals.
* **f** *v_1/vt_1* *v_2/vt_2* *v_3/vt_3* - Creates a textured triangle from three vertices and texture coordinates.
* **f** *v_1/vt_1/vn_1* *v_2/vt_2/vn_2* *v_3/vt_3/vn_3* - Creates a smooth shaded, textured triangle from three vertices, textures, and normals.
* **light** *source_x* *source_y* *source_z* *w* *red* *green* *blue* - Creates a directional light source if *w* is 0. Creates a point light source if *w* is 1.
* **attlight** *source_x* *source_y* *source_z* *w* *red* *green* *blue* *c1* *c2* *c3* - Creates an attenuation light.

## Output File
The output file will be generated as `output/input.ppm`, where `input` is the name of the input file. Output files are of type PPM, which requires a speciel program to view.