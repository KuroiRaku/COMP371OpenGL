Team Members:\
Alessandro Kreslin (40025121)<br />
Dann Kaoussarani (40133457)<br />
Le Cherng Lee (40122814)<br />
Arshia Hamidi (40068250)<br />
<br />
Our project started with 5 members, but one of the members dropped the class, that’s why there are only 4 models

## Project Overview
This project shows each member character model that consist of their first letter and last letter of their name as well as first number and last number of their student ID.<br /> This project allow user to rotate the models, moving the camera like in fps as well as rotating the world.<br /> There are some basic shaders code that changes models' colour as well as a little bit of lighting code and is just an extra work that we done.<br /> There's also an objectLoader and we loaded a cube with it as well as a font code which we did not use in the project as of right now. 

## Grid and Lines
The grid is made up of a series of lines 128 x 128 with equal length spreading across the x,z plane\
The lines are made in the length of 7 grid units apart going in the x,y,z axis\ We binded a separate shader to achieve the different colors of each line.

## The Models
We only have 4 team members now so we made 4 models. We used the Vertex Array method of creating the models and modelled them using triangle primitives. Each team members model was placed in a separate class for ease of separation.

## The Camera
We used the Model View Projection approach to modelling the 3d world with the camera position changing the values\ These are the camera controls:\
While right mouse button click and move the mouse in x direction: pan camera in X direction\
While middle button is pressed and move the mouse in y direction: tilt camera in Y direction\
While left mouse button click: zoom in or out

## Model Control
You can select each of the model through the keys 1,2,3,4. From there here are the controls\
‘U’: to increase the scale\
‘J’: to decrease the scale\
‘WASD’: to move the model up, left, down, right respectively\
‘SHIFT + WASDQE’: to rotate the model in pitch, yaw, roll direction respectively by 5 degrees respectively\
‘P’: to render model with points\
‘L’: to render model with lines\
’T’: to render model with triangles\
'right arrow button': To rotate the world model to +y axis\
'left arrow button': To rotate the world model to -y axis\
'up arrow button': To rotate the world to +x axis\
'down arrow button': To rotate the world to -x axis\
'home button': Reset all the model to its original position

## Code Reference
We have refer to code in [learnopengl.com](learnopengl.com)
