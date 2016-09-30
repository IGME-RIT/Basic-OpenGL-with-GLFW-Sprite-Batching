# Basic OpenGL with GLFW: Sprite Batching

Sending information to the gpu is one of the most common bottlenecks when it comes to graphics programming.
This can make drawing thousands of sprites at once incredibly slow.
Instead of drawing individual objects one at a time, we can batch them all into one draw call to speed things up significantly.

# Setup

You will need to have CMake installed on your computer, and properly added to your path.
In order to setup, run the following in a shell, then open the project in your preferred editor.
Windows setup has been configured for use with Visual Studio.

Windows:
```
cd path/to/folder
setup.cmd
```
Linux:
```
cd path/to/folder
./setup
```
