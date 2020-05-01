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

GLuint WIDTH = 800;
GLuint HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

Camera camera( glm::vec3(0.0f, 0.0f, 3.0f)  );
GLfloat lastX = WIDTH/2.0f;
GLfloat lastY = HEIGHT/2.0f;

bool keys[1024];
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

   Camera Camera;
   Window Window;
int main()
{


   Window.WindowOpen( );
   

   glfwSetKeyCallback( Window.WindowAccess(), KeyCallback );
   glfwSetCursorPosCallback( Window.WindowAccess(), MouseCallback );
   glfwSetScrollCallback( Window.WindowAccess(), ScrollCallback );
 
   glfwSetInputMode(Window.WindowAccess(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
   
    // Build and compile our shader program
   
   // START OF TEXTURES
   
   glViewport(0, 0 , SCREEN_WIDTH, SCREEN_HEIGHT );
   
   glEnable( GL_DEPTH_TEST );
   glEnable( GL_BLEND );
   glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
   
   
   
   
   //END OF TEXTURES
   
   
   
   
   
   
    Shader ourShader( "Resources/Shaders/Camera.vs", "Resources/Shaders/Camera.frag" );
    
   
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
   

  int Elements =5120;
   int otherelments = Elements;
   
   glm::vec3 * cubePositions;
   cubePositions = new glm::vec3 [Elements];
   
   int z = 0;
   for(int l = 0; l<=1;l++)
   {
      int m = 0;
      if(l == 1)
      {
         m=20;
      }
   for(int p = 0; p<=9; p++)
   {
   for(int j =0;  j <= 15; j++)
   {
        cubePositions[Elements] =
      {
       glm::vec3(j+m , p, z)
      };
      Elements--;
      for(int r = 1; r<=15;r++)
      {
         cubePositions[Elements] =
         {
            glm::vec3( j+m, p, r)
         };
         Elements--;
      }
   }
   }
   }


   
    GLuint VBO, VAO;
    glGenVertexArrays( 1, &VAO );
    glGenBuffers( 1, &VBO );

   
   
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray( VAO );
    
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
   glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );
   
   
    // Position attribute
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof( GLfloat ), ( GLvoid * ) 0 );
    glEnableVertexAttribArray( 0 );

 
   //Texture coordinate attribute
   glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof( GLfloat ), ( GLvoid * )( 3* sizeof( GLfloat ) ) );
    glEnableVertexAttribArray( 2 );

    glBindVertexArray( 0 ); // Unbind VAO
   
    Texture  GenStone( "Resources/Images/Stone_image.jpeg", Wrapping::Clamp_Edge , Filter:: Nearest);
   Texture  GenTex( "Resources/Images/stb_image.jpeg", Wrapping::Clamp_Edge , Filter:: Nearest);
  

   
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
        glClearColor( 0.3f, 0.3f, 1.3f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        
        // Draw the triangles underneath
        ourShader.Use( );
   
      GenTex.CHOOSE_TEXTURE( 0 );
       GenTex.Texture_Bind();

       GenStone.CHOOSE_TEXTURE(1);
             GenStone.Texture_Bind();
       
   glUniform1i( glGetUniformLocation(ourShader.Program, "ourTexture2"),1 );
       glUniform1i( glGetUniformLocation(ourShader.Program, "ourTexture1"),0 );
       
       //This uses the 0 texture which is set to dirt right now
         
      
       
       glm::mat4 projection(1);
       projection = glm::perspective(  Camera.GetZoom() , ( GLfloat )Window.WIDTH / (GLfloat)Window.HEIGHT, 0.1f , 1000.0f);
       glm::mat4 view(1);
       view = Camera.GetViewMatrix(  );
       GLint modelloc = glGetUniformLocation( ourShader.Program , "model" );
      GLint viewloc = glGetUniformLocation( ourShader.Program , "view" );
       GLint projloc = glGetUniformLocation( ourShader.Program , "projection" );
       
       
         glUniformMatrix4fv( viewloc , 1, GL_FALSE, glm::value_ptr( view) );
         glUniformMatrix4fv( projloc , 1, GL_FALSE, glm::value_ptr( projection ) );
       
       
       //TEXTURE STUFF
       
       
        glBindVertexArray( VAO );
      
       for(GLuint i = 0; i <otherelments; i++)
       {
          glm::mat4 model(1);
          model = glm:: translate(model, cubePositions[i]);
          GLfloat angle =0.0f * i;
     
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
    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate( );
    
    return EXIT_SUCCESS;
}
    
    

void DoMovement(  )
{
   if( keys[GLFW_KEY_W] || keys[GLFW_KEY_UP] )
               {
                                Camera.ProcessKeyboard( FORWARD , deltaTime );
               }
                                
    if( keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN] )
                 {
                                 Camera.ProcessKeyboard( BACKWARD , deltaTime );
                 }
                                 
   if( keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT] )
                {
                                Camera.ProcessKeyboard( LEFT , deltaTime );
                }
                                
   if( keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT] )
                {
                                Camera.ProcessKeyboard( RIGHT , deltaTime );
                }
   if(keys[GLFW_KEY_SPACE] )
   {
 Camera.ProcessKeyboard(UP, deltaTime);
   }
   if(keys[GLFW_KEY_LEFT_SHIFT])
   {
        Camera.ProcessKeyboard(DOWN, deltaTime);
   
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
   Camera.ProcessMouseMovement( xOffset, yOffset );
}
void ScrollCallback( GLFWwindow* window , double xOffset, double yOffset )
{
   Camera.ProcessMouseScroll( yOffset );
}

