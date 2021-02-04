#include <glad/glad.h>
#include <GLFW/glfw3.h>

//Engine
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Font.h"
#include "Texture.h"
#include "GLDebugMessageCallback.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void increamentRValue(float& RValue);

// settings
const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 768;

int main(void)
{

    GLFWwindow* window;

    if (!glfwInit()) {
        return -1;
    }
    

    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "怖い！", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    //glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    OpenGLFont font("resources/shaders/text.vs", "resources/shaders/text.fs", SCR_WIDTH, SCR_HEIGHT, "resources/fonts/Amaze_Normal.ttf", 25);

    glfwSwapInterval(1);

    //OpenGL state
    GLCall(glEnable(GL_CULL_FACE));
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    
    //hidden surface removal
    glDepthFunc(GL_LESS);
    glDepthMask(GL_TRUE);

    //the dot for a 3d square
    float square[] = {
        -0.5f,-0.5f,0.0f,
         0.5f,-0.5f,0.0f,
         0.5f, 0.5f,0.0f,
        -0.5f, 0.5f,0.0f,
    };

    unsigned int indices[] = {
        0,1,2,
        2,3,0
    };


    //binding the buffer
    unsigned int buffer;
    //for the numbers please refer to the Square array above
    VertexBuffer vb(square, 4 * 3 * sizeof(float));

    VertexArray va;
    VertexBufferLayout layout;
    layout.Push<float>(3);
    va.AddBuffer(vb, layout);

    //optimise way so not to reuse same vertices by introducing index buffer
    unsigned int ibo;
    IndexBuffer ib(indices, 6);

    Shader shader("resources/shaders/Basic.shader");
    shader.Bind();
    shader.SetUniform4f("u_Color", 0.2f, 0.4f, 0.8f, 1.0f);

    Texture texture("resources/textures/phone.png");
    texture.Bind(0);
    shader.SetUniform1i("u_Texture", 0);

    va.Unbind();
    shader.Unbind();
    vb.Unbind();
    ib.Unbind();

    Renderer renderer;

    //colour
    float rValue = 184.0 / 255.0;
    float gValue = 213.0 / 255.0;
    float bValue = 238.0 / 255.0;
    float alpha = 1.0;

    float increment = 0.05f;
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        //Render clear colour buffer bit
        renderer.Clear();

        // render
        // ------
        glClearColor(0, gValue, bValue, alpha);
        shader.Bind();
        shader.SetUniform4f("u_Color", rValue, gValue, bValue, alpha);

        renderer.Draw(va, ib, shader, 0);

        if (rValue > 1.0f)
            increment = -0.05f;
        else if (rValue < 0.0f)
            increment = 0.05f;

        rValue += increment;

        font.PrintText("This is sample text", 30.0f, 30.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);

        //POLL FOR CURRENT EVENT
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    //font.Clean();
    glfwTerminate();

    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        glClearColor(255.0 / 255.0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    //trying changing the shape
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
        glClearColor(255.0 / 255.0, 0, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        float triangle[] = {
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f  // top
        };
    }

    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
        glClearColor(0, 255.0 / 255.0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
        float rValue = 184.0 / 255.0;
        float gValue = 213.0 / 255.0;
        float bValue = 238.0 / 255.0;
        float alpha = 1.0;
        glClearColor(rValue, gValue, bValue, alpha);
        glClear(GL_COLOR_BUFFER_BIT);
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


void increamentRValue(float& RValue)
{
    float increment = 0.05f;

    if (RValue > 1.0f)
        increment = -0.05f;
    else if (RValue < 0.0f)
        increment = 0.05f;

    RValue += increment;
}