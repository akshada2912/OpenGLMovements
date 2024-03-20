# Part A: Procedural Generation of the Prism 
Geenrated and rendered a prism of given parameters. The number of sides of the polygon in the prism should be passed as a command line argument. As this argument increases, the prism will tend to become cylindrical in nature.
1. Coded up the prism generation pipeline which should create the vertices and the faces of the prism for any general n sides.
2. Colored each of the faces of the prism with any color you like (each face should have a unique color)

# Part B: Bringing the scene to life with motion 
1. Flying Camera: The fly camera is a popular camera locomotion technique used in Blender to navigate the scene. Implemented it by binding six keys - W and S for forward and backward, A and D for left and right and Q and E for up and down for the respective camera movement. Ensured the camera always faces the prism’s center.
2. Object Translation: Another six keyswere assigned for 6D (up, down, left, right, towards, away w.r.t to the camera) movement of the prism. The camera need not follow the prism.
3. Prism let’s go for a spin: On press of the key R, the prism rotates about X axis. 

# Part C: Change the shape 
1. Egyptian pyramids: Prism can be converted into a pyramid. Use Key press T to toggle between prism and pyramid.
