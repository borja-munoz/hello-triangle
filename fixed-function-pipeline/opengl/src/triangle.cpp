#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <math.h>

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

GLFWwindow * initGLFW()
{
    glfwInit(); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_FALSE);
    #endif

    GLFWwindow *window = glfwCreateWindow(800, 600, "FixedPipeline", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return(NULL);
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    return(window);
}

bool initGLAD()
{
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return(false);
    } 

    return(true);
}


int main(int argc, char *argv[])
{
    GLFWwindow *window;

    window = initGLFW();

    if (window != NULL)
    {
        if (initGLAD())
        {
            while (!glfwWindowShouldClose(window))
            {
                processInput(window);   

                glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);
 
                glBegin(GL_TRIANGLES);

                glColor3f(1.0f, 0.0f, 0.0f);
                glVertex3f(0.5f, -0.5f, 0.0f);

                glColor3f(0.0f, 1.0f, 0.0f);
                glVertex3f(-0.5f, -0.5f, 0.0f);

                glColor3f(0.0f, 0.0f, 1.0f);
                glVertex3f(0.0f, 0.5f, 0.0f);

                glEnd();
                glFlush();

                // OpenGL double buffer
                glfwSwapBuffers(window);
                glfwPollEvents();    
            }

        }

        glfwTerminate(); 
    }
    
    return(0);
}