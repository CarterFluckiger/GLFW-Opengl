#include <stdio.h>
#include <iostream>
#include "Window.h"
//GLEW
#define GLEW_STATIC
#include <GL/glew.h>
//GLFW
#include <GLFW/glfw3.h>

int Window::WindowOpen()
{
   //Functions used to make the window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    int screenwidth = 0;
    int screenHeight = 0;
    window = glfwCreateWindow(WIDTH, HEIGHT,"Minecrapp", nullptr,nullptr);
    glfwGetFramebufferSize(window, &screenwidth, &screenHeight);

   // A lot checks that made debugging easier
    if(nullptr == window)
                    {
         std::cout<<"Failed to create GLFW window"<<std::endl;
         glfwTerminate();
         return -1;
                    }
                    glfwMakeContextCurrent(window);
                    glewExperimental=GL_TRUE;
     if(GLEW_OK != glewInit())
     {
         std::cout<<"Failed to initialize GLEW"<<std::endl;
         return -1;
     }
       // Define the viewport dimensions
      glViewport( 0, 0, screenwidth, screenHeight );
    return 0;
}
//Return to close window
int Window:: WindowClose()
{
    return 0;
}
//Get function for window
//Very useful
GLFWwindow* Window:: WindowAccess()
{
    return window;
}

