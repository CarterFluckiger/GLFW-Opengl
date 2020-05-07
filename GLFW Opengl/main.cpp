/*
 Carter Fluckiger
 Data Structures Spring 2020
 Due: May 6,2020
 Lab: For this lab I made a minecraft creative clone game.  In this game you can fly around using the 3D camera which allows for any time of movement wanted.  The code also allows the user to customize the textures to basically any image that they want.  A favorite of mine and my classes was the "Mr. Busch face".  The game allows for the user to easily create any shader or texture that they want to very quickly.  The has the ability to create a "chunk".  The user can modify and change the generation of the chunk.  The chunk can be modified dynamically as I have it created which means that it easily could generate a smooth chunk if I used a noise creating function, but this "rocky" generation I have now shows that I can create unlimited custom terrain if my computer could handle that kind of generation.  The game also has a nice window that is created because if you want something done in OpeanGL you have to do it yourself for the most part.  Plan on continuing the project this summer, but have a product showcasing terrain generation and everything it takes to work with OpenGL.
*/

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
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "Block.h"

#include <time.h>
#include <iostream>
#include <string>


//Pre conditions- Window object has been created and ints for key, scancode,action, and node are fufilled
//Post conditions- Checks when buttons are pressed and let go off
void KeyCallback( GLFWwindow* window, int key, int scancode, int action, int mode );
//Pre conditions- Window object has been created and ints for key, scancode,action, and node are fufilled
//Post conditions- Resposible for changing camera view when scrolling with the optifind feature
void ScrollCallback( GLFWwindow* window, double xOffset, double yOffset );
//Pre conditions- Window object is created and doubles are fufilled when called
//Post conditions- Responsible for changing camera when using mouse operations
void MouseCallback( GLFWwindow* window, double xPos, double yPos );
//Pre conditions- That you have inputs that are possible
//Post conditions- Looks at the if statements for if the user presses a button that is an option to move
void DoMovement(  );

//Width and height used for size of the window
GLuint WIDTH = 800;
GLuint HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Values used for the Camera and camera positions and movements
Camera camera( glm::vec3(0.0f, 0.0f, 3.0f)  );
GLfloat lastX = WIDTH/2.0f;
GLfloat lastY = HEIGHT/2.0f;

// bool checks for the camera
bool keys[1024];
bool firstMouse = true;
//Deltatime is used when moving. For the speed and movement in relation to time
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

   Camera Camera;
   Window Window;
int main()
{
   srand((unsigned int) time(NULL));
   
   //Used to make the window
   Window.WindowOpen( );
   
//Calls to the Callback functions
   glfwSetKeyCallback( Window.WindowAccess(), KeyCallback );
   glfwSetCursorPosCallback( Window.WindowAccess(), MouseCallback );
   glfwSetScrollCallback( Window.WindowAccess(), ScrollCallback );
   glfwSetInputMode(Window.WindowAccess(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
   
   
   glViewport(0, 0 , SCREEN_WIDTH, SCREEN_HEIGHT );
   // Used for the textures.  They are necessary and one is specific to MAC OS
   glEnable( GL_DEPTH_TEST );
   glEnable( GL_BLEND );
   glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

   //Shader program being run
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
   
  
   
   
   
   //***********Creates Chunk*********
   // Struct and array used to hold the height values
   struct Height
   {
      int height;
   };
   Height chunk[256];
   
   //for loop to initialize the height values
   for(int k = 0;k < 255;k++)
   {
      int randomnumber = rand()%10+1;
      chunk[k].height = randomnumber;
   }
  

   //Creates pointer to dynamically allocate memory to it for when it is moved into the block class
   //The block class currently tries to make the block and chunk in the same class
  int Elements =  2560;
   int otherelements = Elements;
   //2560 is a chunk
   glm::vec3 * cubePositions;
   cubePositions = new glm::vec3 [Elements];
   
   
   //The beginning of for loops that create the positions for the cube use the vertices above
   
   //The commented out bits are used for creating multiple chunks but is not needed to show that one chunk with dynamic
   //height can be created.  Even though it isn't a smooth chunk it can be made smooth with noise functions
   int f =0;
   int z = 0;
   //for(int l = 0; l<=1;l++)
   //{
      int m = 0;
 
//      if(l >= 1 )
      //{
       //  m=17*f;
       //  f++;
    //  }
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
         //I commented out this chunk to make the height different to make a
         //square chunk, but if height is wanted it must be uncommented and s
         // would need to replace r in the below glm::vec3 statement
         //int s = chunk[f].height;

         cubePositions[Elements] =
         {
            glm::vec3( j+m, p, r)
         };
         f++;
         Elements--;
      }
   }
   }
   
   //Has all cubes initialized
 //  }

//*********Stops creating chunk********
   //VBO and VAO objects are created for creating a texture on the screen
    GLuint VBO, VAO;
    glGenVertexArrays( 1, &VAO );
    glGenBuffers( 1, &VBO );

   
   
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer).
    glBindVertexArray( VAO );
    
   //Binds the Buffer object
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
   glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );

   
   
    // Position attribute
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof( GLfloat ), ( GLvoid * ) 0 );
    glEnableVertexAttribArray( 0 );

 
   //Texture coordinate attribute
   glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof( GLfloat ), ( GLvoid * )( 3* sizeof( GLfloat ) ) );
    glEnableVertexAttribArray( 2 );
   
   // Unbind VAO
    glBindVertexArray( 0 );
   
   // Creates a texture object
   //Needs a location of the picture and a wrapping and filter attribute
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



       glUniform1i( glGetUniformLocation(ourShader.Program, "ourTexture1"),0 );
       
       //This uses the 0 texture which is set to dirt right now
         
      
       //Used for camera "stuff"
       glm::mat4 projection(1);
       projection = glm::perspective(  Camera.GetZoom() , ( GLfloat )Window.WIDTH / (GLfloat)Window.HEIGHT, 0.1f , 1000.0f);
       glm::mat4 view(1);
       view = Camera.GetViewMatrix(  );
       //Creates GLints for GetUniform functions for our model, view, and projection variable from shader
       GLint modelloc = glGetUniformLocation( ourShader.Program , "model" );
      GLint viewloc = glGetUniformLocation( ourShader.Program , "view" );
       GLint projloc = glGetUniformLocation( ourShader.Program , "projection" );
       
       
         glUniformMatrix4fv( viewloc , 1, GL_FALSE, glm::value_ptr( view) );
         glUniformMatrix4fv( projloc , 1, GL_FALSE, glm::value_ptr( projection ) );
       

       
       
        glBindVertexArray( VAO );
      
       //For loop for intializing the cubes and actually createing them
       // Also can alter the cubes like the angle of them
       for(GLuint i = 0; i < otherelements; i++)
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
    // Terminate GLFW
    glfwTerminate( );
    
    return EXIT_SUCCESS;
}
    
    // Finds what inputs have been pressed and sends information to camera class function
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
                           
   //finds if the inputs are pressed and released
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

//Allows use of mouse 
void MouseCallback( GLFWwindow* window, double xPos, double yPos )
{
   if(firstMouse)
   {
      //Changes current x and y position depending on the mouse movements
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
//Runs Mouse scroll function in the camera class
void ScrollCallback( GLFWwindow* window , double xOffset, double yOffset )
{
   Camera.ProcessMouseScroll( yOffset );
}

