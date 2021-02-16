Team Members:
Alessandro Kreslin (40025121)

Our project started with 5 members, but one of the members dropped the class, that’s why there are only 4 models

## Grid and Lines
The grid is made up of a series of lines 128 x 128 with equal length spreading across the x,z plane
The lines are made in the length of 7 grid units apart going in the x,y,z axis. We binded a separate shader to achieve the different colors of each line.

## The Models
We only have 4 team members now so we made 4 models. We used the Vertex Array method of creating the models and modelled them using triangle primitives. Each team members model was placed in a separate class for ease of separation.

## The Camera
We used the Model View Projection approach to modelling the 3d world with the camera position changing the values. These are the camera controls
While right mouse button click: pan camera X direction
While middle button is pressed: tilt camera Y direction
While left mouse button click: zoom in or out

## Model Control
You can select each of the model through the keys 1,2,3,4. From there here are the controls
‘U’: to increase the scale
‘J’: to decrease the scale
‘WASD’: to move the model up, left, down, right respectively
‘SHIFT + WASD’: to rotate the model up, left, down, right respectively by 5 degrees respectively
‘P’: to render model with points
‘L’: to render model with lines
’T’: to render model with triangles