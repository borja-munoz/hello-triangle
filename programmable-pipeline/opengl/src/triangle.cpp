#include "shader.h"

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
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    GLFWwindow *window = glfwCreateWindow(800, 600, "ProgrammablePipeline", NULL, NULL);
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

unsigned int createTriangle()
{
    unsigned int VBO, VAO, EBO;

    // We create the array of vertices forming the two triangles
    // Only vertex coordinates
    float vertices[] = 
    {
        // positions         // colors
        0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
        0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f    // top 
    };

    // We first generate the vertex attribute object and
    // the vertex buffer object

    // The vertex attribute object tells OpenGL how to interpret the vertex data
    // It stores our vertex attribute configuration and tells OpenGL which VBO and EBO to use
    glGenVertexArrays(1, &VAO);

    // We must store the vertices in the GPU memory using vertex buffer objects (VBO)
    glGenBuffers(1, &VBO);
    
    // Binding
    // 1. We must first bind the vertex array object
    // 2. Then we bind the vertex buffer and copy the data
    // 3. After that we bind the element buffer and copy the element indices
    // 4. Finally we tell OpenGL how to interpret the vertex data

    // Bind the vertex array
    glBindVertexArray(VAO);

    // To copy the data to the GPU memory we must bind the vertex buffer and
    // then call the glBufferData method
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // We let OpenGL know how to interpret the vertex data using vertex attributes
    // In this case:
    // - Coordinates starts at index 0, color at index 1
    // - The attributes are vec3 so the size is 3
    // - The type of data is float
    // - We don´t want to normalize the data
    // - The space between consecutive attributes is 6 * sizeof(float) = 12
    // - Offset where data start is 0 for coordinates and 3 * sizeof(float) for color
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Once we have copied the data and configured the vertex buffer object
    // we can proceed to do the unbinding
    // 1. First we unbind the vertex buffer object
    // 2. Then we unbind the vertex attribute object

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 

    return(VAO);
}

int main(int argc, char *argv[])
{
    GLFWwindow *window;
    unsigned int VAO;

    window = initGLFW();

    if (window != NULL)
    {
        if (initGLAD())
        {
            Shader shader = Shader("src/shaders/triangleVertexColors.vs",
                                   "src/shaders/triangleVertexColors.fs");

            VAO = createTriangle();

            while (!glfwWindowShouldClose(window))
            {
                processInput(window);   

                glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
                glClear(GL_COLOR_BUFFER_BIT);

                shader.use();

                // If we have only one VAO, this is not necessary in every render loop
                // We'll do so to keep things a bit more organized
                glBindVertexArray(VAO); 

                // We draw the primitives using the currently active shader
                // using the vertex data (vertex buffer object) and 
                // indices data (element buffer object) that are associated
                // to the vertex attribute object (VAO) that is currently binded
                glDrawArrays(GL_TRIANGLES, 0, 3);

                // OpenGL double buffer
                glfwSwapBuffers(window);
                glfwPollEvents();    
            }

            glDeleteVertexArrays(1, &VAO);
        }

        glfwTerminate(); 
    }
    
    return(0);
}