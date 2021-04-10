## Quiz 2
Le Cherng Lee (40122814)<br />
<br />

## Project Overview
This project shows 6 characters that made up from my last name and my first name.<br /> This project allow user to switch between cameras, moving the camera like in fps as well as rotating the world and switching lights on and off.<br /> There are some extra gimmicks that I had done for colors.<br />

## Project Dependencies
This project uses GLAD and GLFW libraries to run the OpenGL version 4.6 application.<br />
Other libraries that this project uses are GLM, however the dependencies include other libraries which aren't being used as of right now which is freetype, SOIL, IMGUI, stb. <br />
We have also set up linux cmake files but some of the libraries listed are not yet included since not all of the libraries are being used at the moment. <br /> 
**To load and start the application in correct way, please open .sln file. The .sln file contains includes and dependcies configurations** <br />
For Mac users, sorry that we didn't configure settings (.cmake files) on your platform, this application will only run on windows and maybe linux as of right now unless you implemented your own files.

## Grid and Lines
The grid is made up of a series of lines 128 x 128 with equal length spreading across the x,z plane\
The lines are made in the length of 7 grid units apart going in the x,y,z axis\ We binded a separate shader to achieve the different colors of each line.

## The Models
I have hard coded a custom cylinder, sphere as well as a "rectangular cube" using VAO, VBO. Then this quiz will only requires me to create three different letter models. Which is L, E and C. We form these characters through drawing cubes and spheres. Each model also has different colours. <br/>
  

## The Camera
I used the Model View Projection approach to modelling the 3d world with the camera position changing the values\ These are the camera controls:\
While right mouse button click and move the mouse in x direction: pan camera in X direction\
While middle button is pressed and move the mouse in y direction: tilt camera in Y direction\
While left mouse button click: zoom in or out\
TGFH to move around\

## Model Control
You can select each of the model through the keys 1,2,3,4. From there here are the controls\
‘U’: to increase the scale\
‘J’: to decrease the scale\
‘WASD’: to move the model up, left, down, right respectively\
‘SHIFT + WASDQE’: to rotate the model in pitch, yaw, roll direction respectively by 5 degrees respectively\
‘P’: to render model with points\
‘L’: to render model with lines\
’T’: to render model with triangles\
'up arrow button': To rotate the world to +x axis\
'down arrow button': To rotate the world to -x axis\
'home button': Reset all the world matrix to its original position
'0': Reset every model to its original position

## Lighting Control And Cameras
'6': to always reset to ambient light\
'5': turn off ambient light (It won't be completely dark)\
'7': turn on spotlight number 1 that shines on model\
'K': turn on spotlight 3 that is on the ceiling shining on the stage\
'S': turn on spotlight 2 that follows another camera when you press N\
'N': Switch to camera that is facing on the middle of the plane on top.\
'left arrow' + 'right arrow': While on N, press it to circle around the middle left or right.\
'R': Switch to fps main camera.\
'M': Switch to camera infront of model.\
'B': Switch to camera back of models.\
'Q': Turn off shadows? (Alternatively, go to main and set bool shadow to false.\

## Code Reference
I have refer to code in [learnopengl.com](learnopengl.com)
For Sphere, I have refer to https://stackoverflow.com/questions/43087620/draw-sphere-in-opengl-4-0
