/*
Title: Sprite Batching
File Name: main.cpp
Copyright � 2016
Author: David Erbelding
Written under the supervision of David I. Schwartz, Ph.D., and
supported by a professional development seed grant from the B. Thomas
Golisano College of Computing & Information Sciences
(https://www.rit.edu/gccis) at the Rochester Institute of Technology.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at
your option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/



#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/gtc/matrix_transform.hpp"
#include "FreeImage.h"
#include <vector>
#include "../header/shader.h"
#include "../header/spriteBatcher.h"
#include <iostream>

SpriteBatcher* spriteBatcher;

// Window resize callback
void resizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
    spriteBatcher->SetScreenSize(glm::vec2(width, height));
}


int main(int argc, char **argv)
{
	// Initializes the GLFW library
	glfwInit();

	// Initialize window
	GLFWwindow* window = glfwCreateWindow(800, 600, "Sprite Batching!", nullptr, nullptr);

	glfwMakeContextCurrent(window);

	//set resize callback
	glfwSetFramebufferSizeCallback(window, resizeCallback);

	// Initializes the glew library
	glewInit();


    Texture* texture = new Texture("../assets/texture.png");
    texture->IncRefCount();

    // Create a spriteBatcher (This one will need the size of the screen)
    spriteBatcher = new SpriteBatcher(glm::vec2(800, 600));

    float frames = 0;
    float secCounter = 0;

	// Main Loop
	while (!glfwWindowShouldClose(window))
	{
        // Calculate delta time and frame rate
        float dt = glfwGetTime();
        frames++;
        secCounter += dt;
        if (secCounter > 1.f)
        {
            std::string title = "FPS: " + std::to_string(frames);
            glfwSetWindowTitle(window, title.c_str());
            secCounter = 0;
            frames = 0;
        }
        glfwSetTime(0);



		// Clear the screen.
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.0, 0.0, 0.0, 0.0);


        // Loop and draw 1000 sprites to the screen
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                for (int k = 0; k < 10; k++)
                {
                    spriteBatcher->Draw(glm::vec4(100 + i * 50 + k * -10, 100 + j * 50 + k * -10, 50, 50), glm::vec4(0, 0, 300, 320), glm::vec4(i / 10.f, j / 10.f, k / 10.f, 1), texture);
                    // Uncomment this line to see how much slower it is to call draw separately for each sprite.
                    //spriteBatcher->Flush();
                }
            }
        }
        // Now that we have a collection of all the draws we want to make, send it all to the gpu to be drawn!
        spriteBatcher->Flush();

		// Swap the backbuffer to the front.
		glfwSwapBuffers(window);

		// Poll input and window events.
		glfwPollEvents();

	}

    delete spriteBatcher;

    texture->DecRefCount();

	// Free GLFW memory.
	glfwTerminate();


	// End of Program.
	return 0;
}
