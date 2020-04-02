// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

//Soil
#include "SOIL2/SOIL2.h"

// Other includes
#include "Window.h"
#include "Header-Files/Shader.h"
#include "Texture.h"


#include <iostream>
#include <string>

int main( )
{
   Window Window;
   Window.WindowOpen( );
  
   Texture GenTex( "Resources/Images/grass_image.jpeg", Wrapping::Repeat , Filter:: Linear );

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
   
   GLuint texture;
   int width, height;
   glGenTextures( 1, &texture );
   glBindTexture( GL_TEXTURE_2D, texture );
   
   glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
   glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
   
   glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
   glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
   
   
   
 unsigned char* image = SOIL_load_image( "Resources/Images/Dirt_image.jpeg" , &width,&height , 0, SOIL_LOAD_RGBA);
  glTexImage2D( GL_TEXTURE_2D, 0 , GL_RGBA , width, height, 0, GL_RGBA , GL_UNSIGNED_BYTE, image   );
  glGenerateMipmap( GL_TEXTURE_2D );
  SOIL_free_image_data( image );
  glBindTexture( GL_TEXTURE_2D, 0 );
   
   
     
 
   
    // Game loop
    while ( !glfwWindowShouldClose( Window.WindowAccess( ) ) )
    {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents( );

        // Render
        // Clear the colorbuffer
        glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT );
        
        // Draw the triangle
        ourShader.Use( );
       
       GenTex.CHOOSE_TEXTURE( 0 );
       GenTex.Texture_Bind();

       //TEXTURE STUFF
       
       
       glActiveTexture( GL_TEXTURE0 );
       glBindTexture( GL_TEXTURE_2D, texture );
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
