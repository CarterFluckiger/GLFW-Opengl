// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

//Soil
#include "SOIL2/SOIL2.h"

//glm
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


// Other includes
#include "Window.h"
#include "Header-Files/Shader.h"
#include "Texture.h"
#include "Camera.h"


#include <iostream>
#include <string>

void KeyCallback( GLFWwindow* window, int key, int scancode, int action, int mode );
void ScrollCallback( GLFWwindow* window, double xOffset, double yOffset );
void MouseCallback( GLFWwindow* window, double xPos, double yPos );
void DoMovement(  );

Camera camera( glm::vec3(0.0f, 0.0f, 3.0f)  );
GLfloat lastX = 1600/2.0f;
GLfloat lastY = 1000/2.0f;

int main()
{
   Window Window;
   Window.WindowOpen( );
  
   Texture GenTex( "Resources/Images/Grass_image.jpeg", Wrapping::Repeat , Filter:: Linear );
   

   glfwSetKeyCallback( Window.WindowAccess(), KeyCallback );
   glfwSetCursorPosCallback( Window.WindowAccess(), MouseCallback );
   glfwSetScrollCallback( Window.WindowAccess(), ScrollCallback );
 
   glfwSetInputMode(Window.WindowAccess(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
   
   
    // Build and compile our shader program
   
   
   
   
   // START OF TEXTURES
   
   

   
   glEnable( GL_BLEND );
   glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
   
   
   
   
   //END OF TEXTURES
   
   
   
   
   
   
    Shader ourShader( "Resources/Shaders/Texture.vs", "Resources/Shaders/Texture.frag" );
    
    
    // Set up vertex data (and buffer(s)) and attribute pointers
    GLfloat vertices[] =
       {
           // Positions         // Colors              //texture coords
          0.5f, 0.5f, 0.0f,      1.0f, 0.0f, 0.0f,        1.0f, 1.0f, //Top right
          0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,       1.0f, 0.0f, //Bottom right
          -0.5f, -0.5f,0.0f,     1.0f, 0.0f, 0.0f,       0.0f,0.0f, // Bottom left
          -0.5f, 0.5f, 0.0f,     1.0f, 1.0f, 1.0f,       0.0f, 1.0f  //top left
       };
   GLuint indices[] =
   {
      0, 1, 3,  //first triangle
      1, 2, 3  //second triangle
   };
   
   
   

   
   
    GLuint VBO, VAO, EBO;
    glGenVertexArrays( 1, &VAO );
    glGenBuffers( 1, &VBO );
   glGenBuffers( 1, &EBO );
   
   
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray( VAO );
    
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
   glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );
   
//EBO stuff
   glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, EBO );
   glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW );
    
    // Position attribute
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof( GLfloat ), ( GLvoid * ) 0 );
    glEnableVertexAttribArray( 0 );
    // Color attribute
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof( GLfloat ), ( GLvoid * )( 3 * sizeof( GLfloat ) ) );
    glEnableVertexAttribArray( 1 );
   
   //Texture coordinate attribute
   glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof( GLfloat ), ( GLvoid * )( 6 * sizeof( GLfloat ) ) );
    glEnableVertexAttribArray( 2 );
   
    glBindVertexArray( 0 ); // Unbind VAO
   

     
 
   
    // Game loop
    while ( !glfwWindowShouldClose( Window.WindowAccess( ) ) )
    {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents( );

        // Render
        // Clear the colorbuffer
        glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT );
        
        // Draw the triangles underneath
        ourShader.Use( );
 
       //TEXTURE STUFF
       
       GenTex.CHOOSE_TEXTURE( 0 );
       GenTex.Texture_Bind();
       //This uses the 0 texture which is set to dirt right now
       glActiveTexture( GL_TEXTURE0 );
    
       glUniform1i( glGetUniformLocation(ourShader.Program, "ourTexture1"),0 );
       
       
        glBindVertexArray( VAO );
       glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        
        // Swap the screen buffers
        glfwSwapBuffers( Window.WindowAccess( ) );
    }
    
    // Properly de-allocate all resources once they've outlived their purpose
    glDeleteVertexArrays( 1, &VAO );
    glDeleteBuffers( 1, &VBO );
   glDeleteBuffers( 1,&EBO );
    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate( );
    
    return EXIT_SUCCESS;
}
