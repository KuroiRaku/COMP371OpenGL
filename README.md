

## Project Dependencies
This project is meant to run on linux.
Dependencies are GLEW, GLFW. You are going to need these 2 dependencies installed on your computer as well as pkg-config and ninja-build.
install all these deps, then run "ninja" in the main directory of the project.
Also, make sure you have clang(the compiler) installed.

## Grid and Lines
The grid is made up of a series of lines 128 x 128 with equal length spreading across the x,z plane\

## The Camera
We used the Model View Projection approach to modelling the 3d world with the camera position changing the values\ These are the camera controls:\
While right mouse button click and move the mouse in x direction: pan camera in X direction\
While middle button is pressed and move the mouse in y direction: tilt camera in Y direction\
While left mouse button click: zoom in or out

### More On camera
You can move around the camera using the Arrow keys.
You can use Left Shift to move the camera Down and Space to move the camera Up.

## Model Control
You can select each Letter using the number keys 0-5
You can move around the selected letter using W A S D
To move the letters vertically you use P for up and M for down
You can also toggle between LINE polygon mode and FILL with hotkeys G and H

## Code Reference
I have referred to code from [learnopengl.com](learnopengl.com)
And I also used a precoded OBJLoader class: https://github.com/BennyQBD/ModernOpenGLTutorial/blob/master/obj_loader.cpp
And here is the header for the OBJLoader class: https://github.com/BennyQBD/ModernOpenGLTutorial/blob/master/obj_loader.h
