# How to get up to this point -- Getting OpenGL and (other libraries) up and running

### Getting Visual Studio Project up and running
 - Create an _empty Visual Studio project_
 - Feel free to create your `main.cpp` and your `int main() { return 0; }`
 - Create a folder named something like 'External Libraries' at the solution level (next to the .sln)

### Download the _*pre-complied binaries*_ for GLFW and GLEW.
 - NOTE: Download the 32 bit binaries for ease of setting up
 - GLFW: http://www.glfw.org/download.html
 - GLEW: http://glew.sourceforge.net/
 - Extract the binaries put it in the 'External Libraries' folder
 - name the respective folder as GLFW/GLEW (instead of something like `glfw-3.2.1.bin.WIN32`)

### Re-configuring our VS Project
 - In the top left (tool bar thing), click on 'Project' -> 'Properties'
 - Go to 'C/C++' -> 'General' -> 'Additional Include Directories'
   - Locate the 'include' folders of GLFW and GLEW
      - This should be something like `$(SolutionDir)External Libraries/GLFW/include` and `$(SolutionDir)External Libraries/GLEW/include`
   - If you are successful, you will be able to call `#include <GL/glew.h>` or `#include <GLFW/glfw3.h>` in your `.cpp`s
 - Go to 'Linker' -> 'General' -> 'Additional Library Directories'
   - Locate the .lib files of GLFEW and GLEW
      - Something like: `$(SolutionDir)External Libraries/GLEW/lib/Release/Win32` or `$(SolutionDir)External Libraries/GLFW/lib-vc2015`
   - This makes sure the linker knows where to look to find these libraries
 - Go to 'Linker' -> 'Input' -> 'Additional Dependencies'
   - Add the following .lib in there:
      - opengl32.lib
      - glew32s.lib (OR glew32.lib if you don't want to use the static lib)
      - glfw3.lib
   - This makes sure the linker knows that we have some dependencies to resolve
   
### What next?
 - Look through the main.cpp that's in this repo and slowly digest what's going on. You should be able to type all that code over and get a window up and running!
   
### Help!

#### Q: I have a ton of these
![A ton of linker errors](https://i.imgur.com/GfkUrjs.png)

#### A: Check if you're on x64 or x86 (x32)
