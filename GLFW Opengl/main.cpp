#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other includes
#include "Shader.h"
#include "Window.h"

int main( )
{
   Window Window;
   Window.WindowOpen( );
    // Build and compile our shader program
    Shader ourShader( "Resources/Shaders/core.vs", "Resources/Shaders/core.frag" );
    
    
    // Set up vertex data (and buffer(s)) and attribute pointers
    GLfloat Texture_Vertices[] =
    {
       0.0f, 0.0f,  // lower-left corner
       1.0f, 0.0f,  // lower-right corner
       0.5f, 1.0f   // top-center corner
    };
   
   // START OF TEXTURES
   
   


   
   float borderColor = ( 1.0f, 1.0f, 0.0f, 1.0f );
   glTexParameterfv( GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor );
   
   glTexParameter( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
   glTexParameter( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
   
   
   
   
   
   unsigned int texture;
   glGenTextures( 1, &texture );
   glBindTexture( GL_TEXTURE_2D, texture );
   
   
   glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT );
   glTextParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT );
   glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
   glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
   
#define STB_IMAGE_IMPLEMENTATION
   #include "stb_image.h"
   
   int width, height, nrChannels;
   unsigned char* data = stbi_load( "container.jpg", &width, &height, &nrChannels, 0 )
   if(data)
   {
      glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,GL_RGB,GL_UNSIGNED_BYTE, data );
      glGenerateMipmap( GL_TEXTURE_2D );
   }
   else
   {
      std::cout<< " Failed  to load texture "<<std::endl;
   }
   
   stbi_image_free(data);
   
      
   
   float vertices[] = {
       // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
       -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
       -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
   };
   
   
   glVertexAttribPointer( 2,2,GL_FLOAT,GL_FALSE,8 * sizeof( float ),(void*)(6 * sizeof( float )) );
   glEnableVertexAttribArray( 2 );
   
   glBindTexture( GL_TEXTURE_2D, texture );
   glBindVertexArray( VAO );
   glDrawElements( GL_TRIANGLES, 6 , GL_UNSINGED_INT , 0 );
   
   
   
   
   
   
   
   //END OF TEXTURES
   
   
    GLuint VBO, VAO;
    glGenVertexArrays( 1, &VAO );
    glGenBuffers( 1, &VBO );
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray( VAO );
    
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );
    
    // Position attribute
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof( GLfloat ), ( GLvoid * ) 0 );
    glEnableVertexAttribArray( 0 );
    // Color attribute
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof( GLfloat ), ( GLvoid * )( 3 * sizeof( GLfloat ) ) );
    glEnableVertexAttribArray( 1 );
    
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
        
        // Draw the triangle
        ourShader.Use( );
        glBindVertexArray( VAO );
        glDrawArrays( GL_TRIANGLES, 0, 3 );
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
