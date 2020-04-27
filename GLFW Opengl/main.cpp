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

bool keys[1024];
bool firstMouse=true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;


   Window Window;
int main()
{
   Camera Camera;

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
   
   
   
   
   
   
    Shader ourShader( "Resources/Shaders/Camera.vs", "Resources/Shaders/Camera.frag" );
    
    /*
     These are the old vertices
    // Set up vertex data (and buffer(s)) and attribute pointers
    GLfloat vertices[] =
       {
           // Positions         // Colors              //texture coords
          0.5f, 0.5f, 0.0f,      1.0f, 0.0f, 0.0f,        1.0f, 1.0f, //Top right
          0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,       1.0f, 0.0f, //Bottom right
          -0.5f, -0.5f,0.0f,     1.0f, 0.0f, 0.0f,       0.0f,0.0f, // Bottom left
          -0.5f, 0.5f, 0.0f,     1.0f, 1.0f, 1.0f,       0.0f, 1.0f  //top left
       };
   */
   
   //New vertices for new cubes
   GLfloat vertices[] =
      {
          -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
          0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
          0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
          0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
          -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
          -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
          
          -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
          0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
          0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
          0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
          -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
          -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
          
          -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
          -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
          -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
          -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
          -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
          -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
          
          0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
          0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
          0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
          0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
          0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
          0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
          
          -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
          0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
          0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
          0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
          -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
          -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
          
          -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
          0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
          0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
          0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
          -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
          -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
      };
   
   
   
   
/*
   GLuint indices[] =
   {
      0, 1, 3,  //first triangle
      1, 2, 3  //second triangle
   };
*/
   
   glm::vec3 cubePositions[] =
   {
      glm::vec3(0.0f, 0.0f, 0.0f),
      glm::vec3(2.0f, 5.0f, -15.0f),
      glm::vec3(-1.5f, -2.2f,-2.5f),
      glm::vec3(-3.8f, -2.0f, -12.3f),
      glm::vec3(2.4f, -0.4f, -3.5f),
      glm::vec3(-1.7f, 3.0f, -7.5f),
      glm::vec3(1.3f, -2.0f, -2.5f),
      glm::vec3(1.5f, 2.0f, -1.5f),
      glm::vec3(1.5f, 0.2f, -1.5f),
      glm::vec3(-1.3f, 1.0f, -1.5f),
   };
   
   

   
   
    GLuint VBO, VAO, EBO;
    glGenVertexArrays( 1, &VAO );
    glGenBuffers( 1, &VBO );
   glGenBuffers( 1, &EBO );
   
   
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray( VAO );
    
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
   glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );
   /*
//EBO stuff
   glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, EBO );
   glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW );
    */
    // Position attribute
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof( GLfloat ), ( GLvoid * ) 0 );
    glEnableVertexAttribArray( 0 );
    // Color attribute
    glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof( GLfloat ), ( GLvoid * )( 3 * sizeof( GLfloat ) ) );
    glEnableVertexAttribArray( 2 );
   /*
   //Texture coordinate attribute
   glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof( GLfloat ), ( GLvoid * )( 6 * sizeof( GLfloat ) ) );
    glEnableVertexAttribArray( 2 );
*/
    glBindVertexArray( 0 ); // Unbind VAO
   

  
   
    // Game loop
    while ( !glfwWindowShouldClose( Window.WindowAccess( ) ) )
    {
       //Camera Frame updating
       GLfloat currentFrame = glfwGetTime(  );
       deltaTime = currentFrame - lastFrame;
       lastFrame = currentFrame;
       
       
      
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents( );
       DoMovement();
       
       //Camera
       

        // Render
        // Clear the colorbuffer
        glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        
        // Draw the triangles underneath
        ourShader.Use( );
       
       
       glm::mat4 projection = glm::perspective(  Camera.GetZoom() , ( GLfloat )Window.WIDTH / (GLfloat)Window.HEIGHT, 0.1f , 1000.0f);
       glm::mat4 view;
       view = Camera.GetViewMatrix(  );
       GLint modelloc = glGetUniformLocation( ourShader.Program , "model" );
      GLint viewloc = glGetUniformLocation( ourShader.Program , "view" );
       GLint projloc = glGetUniformLocation( ourShader.Program , "projection" );
       
       
         glUniformMatrix4fv( viewloc , 1, GL_FALSE, glm::value_ptr( view) );
         glUniformMatrix4fv( projloc , 1, GL_FALSE, glm::value_ptr( projection ) );
       
       
       //TEXTURE STUFF
       
       GenTex.CHOOSE_TEXTURE( 0 );
       GenTex.Texture_Bind();
       //This uses the 0 texture which is set to dirt right now
       glActiveTexture( GL_TEXTURE0 );
    
       glUniform1i( glGetUniformLocation(ourShader.Program, "ourTexture1"),0 );
       
       
        glBindVertexArray( VAO );
      
       for(GLuint i = 0; i <10; i++)
       {
          glm::mat4 model;
          model = glm:: translate(model, cubePositions[i]);
          GLfloat angle =20.0f * i;
          
          model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f) );
           glUniformMatrix4fv( modelloc , 1, GL_FALSE, glm::value_ptr( model ) );
          
          glDrawArrays( GL_TRIANGLES, 0, 36 );
       }
       
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
void DoMovement(  )
{
   if( keys[GLFW_KEY_W] || keys[GLFW_KEY_UP] )
               {
                                camera.ProcessKeyboard( FORWARD , deltaTime );
               }
                                
    if( keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN] )
                 {
                                 camera.ProcessKeyboard( BACKWARD , deltaTime );
                 }
                                 
   if( keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT] )
                {
                                camera.ProcessKeyboard( LEFT , deltaTime );
                }
                                
   if( keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT] )
                {
                                camera.ProcessKeyboard( RIGHT , deltaTime );
                }
}
                           
                                
                                
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
  {
           if( GLFW_KEY_ESCAPE == key && GLFW_PRESS == action )
            {
                                glfwSetWindowShouldClose( Window.WindowAccess( ), GL_TRUE );
            }
            if(key >= 0 && key < 1024 )
            {
                  if( GLFW_PRESS == action )
                  {
                     keys[key] = true;
                  }
               else if(GLFW_RELEASE == action)
               {
                  keys[key] = false;
               }
            }
 }

void MouseCallback( GLFWwindow* window, double xPos, double yPos )
{
   if(firstMouse)
   {
      lastX = xPos;
      lastY = yPos;
      firstMouse = false;
   }
   GLfloat xOffset = xPos - lastX;
   GLfloat yOffset = lastY - yPos;
   
   lastX = xPos;
   lastY = yPos;
   camera.ProcessMouseMovement( xOffset, yOffset );
}
void ScrollCallback( GLFWwindow* window , double xOffset, double yOffset )
{
   camera.ProcessMouseScroll( yOffset );
}


*/
