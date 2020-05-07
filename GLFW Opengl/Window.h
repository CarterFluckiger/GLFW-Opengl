#ifndef Window_h
#define Window_h

//GLEW
#define GLEW_STATIC
#include <GL/glew.h>

//GLFW
#include <GLFW/glfw3.h>

class Window
{
public:
//Constructor and Descructor are empty

   //Pre conditions- Window opject created
   //Post conditions- Creates the window and viewport
   // Also creates many error messages to catch odd bugs when creating the window
    int WindowOpen( );
   //Pre conditions- None
   //Post conditions- returns a 0 and ends the program and window
    int WindowClose( );
   //A get function that returns the window
    GLFWwindow* WindowAccess( );

   // const ints for the window width and height
 const int WIDTH = 800, HEIGHT = 600;
   
private:
   // Window is private so it can't be accessed without the get function
    GLFWwindow *window;
};

#endif /* Window_h */
