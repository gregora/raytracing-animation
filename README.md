# Animation Wrapper for Raytracer

An animation wrapper for my own raytracer, written in C++. This was made to simplify creating animations with my raytracer.
The program takes an animation and a scene file and renders the animation.

## Dependencies
* SDL2

## Compiling
Before you start compiling, make sure you have SDL2 library installed.

* If you want to compile with g++ compiler on Linux, everything is already in `compile.sh` file.

## List of all the files and folders
* .gitignore - A gitignore file
* compile.sh - A Linux shell script that compiles the whole project
* main.cpp - The file with main function, that then includes everything else
* README.md - readme file
* settings/ - a folder with a single file called `settings`, that tell the animation wrapper how to create `Frame` object
* libraries/ [folder] - a folder in which are all the necessary libraries (except for SDL2). Within this folder there are other folders, with the name of the library used. In each of those folders are then all the necessary .h and .cpp files.
  * lodepng/ [folder] - a folder with all the files necessary to save frames to png images. It was not written by me but you can find it on Github [https://github.com/lvandeve/lodepng](https://github.com/lvandeve/lodepng)
  * raytracing/ [folder] - the folder, in which all the raytracing stuff is. Everything in this folder is my work.
  * animation/ [folder] - a folder with all the necessary things for rendering animations.

## How to create your own scene

A scene is a simple file in which there is information about all the triangles in the scene.

A scene file can handle three different instructions
* `tr` - render a triangle. An example of such instruction would be `tr 0 0 100 100 0 100 50 50 150 1 0 0`. After the instruction, there are 12 float numbers, that tell the parser: x, y, z coordinates of all three sides of triangle and r g b values for the color of triangle (values should be between 0 and 1). There is also optional argument reflectiveness, which should be between 0 and 1 as well.
* `ttr` - acts similarly to just `tr`, but instead of rgb colors, there has to be a link to a png texture. After that, there should be 6 more floating point numbers, that represent the triangle on the texture itself, from where colors should be sampled. Example: `ttr -200 200 0 200 200 0 0 0 200 textures/obama.png 0 0 1750 0 875 1500`. Reflectiveness argument is also optional.
* `lo` - load another scene. An example would be `lo 200 0 0 scenes/pyramid.scene`. This tells the parser, to load scene `scenes/pyramid.scene` and move it 200 units in x direction and 0 units in y and z directions. The three numbers can be float numbers as well.
* `ls` - Add a light source. The following three floats tell its position, and the fourth float tells its brightness. Example: `ls 300 500 20 1`
* `#` - Indicates a comment. Any line that does not have `tr`, `lo` or `ls` command in the beginning will be ignored, but I recommend you still use `#` as comments.

## How to create your own animation

To create your own animtion, you will need to have a couple of things.
* First, you need to have root scene file. This file can then call other files, if you wish.
* Second, you need a `settings` file in `/settings/` folder. This file tells my program how to create your `Frame` object. The file enables you to set a couple of things:
  * width - width of your image(s)
  * height - height of your image(s)
  * save - where to save your image(s) to
  * load - where to load your scene file from
  * spp (optional) - number of samples per pixel. Keep in mind that `spp 3` means that there are 9 samples per pixel (3x3)
  * ambient-light (optional) - How strong should the ambient light be
  * script (optional) - where should the script file be loaded from
  * start-at (optional) - which command to start on
  * end-at (optional) - which command to end on
* Third, you need to have a `script` file. This is the file, that you either input into your `settings` file or when the program starts. The script file supports a couple of different commands:
  * `render` - renders current frame
  * `camera-move x y z` - move camera to a position `x y z`
  * `camera-direction yaw pitch roll` - set camera's given yaw/pitch/roll
  * `sky-color red green blue` - set the sky color
  * `light-move id x y z` - move a given light source to `x y z`. Keep in mind that `id` is the number of the light source as it was loaded. That means that if your scene files load other light sources, you have to take that into account


## What is the output?

The program outputs a series of png images that can then be combined into an animation
