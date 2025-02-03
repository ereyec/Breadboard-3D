# Breadboard 3D - Description

This project is a SPICE netlist 3d visualization tool, created with C++ and OpenGL. 

![image](/textures/breadboard3Dim.png)

# Build Instructions
(Windows)

Make sure g++ in installed on your machine. 

Enter ````g++ -I./include -L./lib ./include/glad.c ./breadboard3D/main.cpp -l:libglfw3.a -lopengl32 -lgdi32 -luser32 -o program.exe```` in cmd in the root directory.

# User Instructions

Save your SPICE netlist as a text file to the root directory. The example uses an LTSpice netlist, if you are using other versions of SPICE, note that there may be some differences in how each version stores its netlist. 

When prompted with ````Enter your netlist file name: ```` make sure your netlist is in the same directory as the executable, and simple type in the name of the file. e.g. ````netlistTest.txt````

As of now, only 1 IC is allowed per netlist, however, it should be possible to "fit" multiple ICs by simply adding nodes in the appropriate order in a single line in the netlist. 
Note that the ICs will appear as one large IC, with no gap in between each.  

See netlistTest.txt for an example. 

Prefix your netlist IC line with ````-i````.

Prefix the voltage source with ````-v````.

Only resistors, capacitors, and diodes are supported, 3-lead elements are not supported at this time.

Jumper wire connections are currently in development. As of now, they only connect IC pin nodes to either vcc or ground. Because they haven't been extensively tested, there may be some redundant connections or inaccuracies. Make sure you check the connections are correct before building your breadboard.