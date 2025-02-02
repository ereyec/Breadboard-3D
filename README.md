# Breadboard 3D - Description

This project is a SPICE netlist 3d visualization tool, created with C++ and OpenGL. 

![image](/textures/breadboard3Dim.png)

# Build Instructions
(Windows)

Enter ````g++ -I./include -L./lib ./include/glad.c ./breadboard3D/main.cpp -l:libglfw3.a -lopengl32 -lgdi32 -luser32 -o program.exe```` in cmd in the root directory.

# User Instructions

Save your SPICE netlist as a text file to the root directory. 

When prompted with ````Enter your netlist file name: ```` make sure your netlist is in the same directory as the executable, and simple type in the name of the file. e.g. ````netlistTest.txt````

As of now, only 1 IC is allowed per netlist, however, it should be possible to "fit" multiple ICs by simply adding nodes in the appropriate order in a single line in the netlist. 
Note that the ICs will appear as one large IC, with no gap in between each.  

See netlistTest.txt for an example. 

Prefix your netlist IC line with ````-i````.

Prefix the voltage source with ````-v````.

Resistors, capacitors, and diodes need no prefix. 3-lead elements and jumper wires are not supported at this time. 