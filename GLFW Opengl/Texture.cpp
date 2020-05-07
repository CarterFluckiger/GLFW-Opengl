#include <stdio.h>
#include <iostream>

#include "Texture.h"

//GLEW
#define GLEW_STATIC
#include <GL/glew.h>
//GLFW
#include <GLFW/glfw3.h>

#include "SOIL2.h"

#include <string>
//Constructor

Texture::Texture()
{
    TEXTURE_TAG = 0;
   std::cout<<"ERROR:CALLED::DEFAULT_TEXTURE"<<std::endl;
}
//Destructor
Texture::~Texture()
{
}

//Bind and Unbind textures
void Texture::Texture_Bind()
{
    glBindTexture(GL_TEXTURE_2D, TEXTURE_TAG);
}
void Texture:: Texture_Unbind()
{
    glBindTexture( GL_TEXTURE_2D , 0 );
}


void Texture:: CHOOSE_TEXTURE(unsigned int TEXTURE_NUMBER)
{
   //Switch statement for the texture identifiers
   switch(TEXTURE_NUMBER)
   {
      case 0:
         glActiveTexture( GL_TEXTURE0 );
         break;
       case 1:
           glActiveTexture( GL_TEXTURE1 );
           break;
       case 2:
           glActiveTexture( GL_TEXTURE2 );
           break;
       case 3:
           glActiveTexture( GL_TEXTURE3 );
           break;
          //Couts error message
       default: std::cout<<"ERROR:: CHOOSE_TEXTURE::INVALID\n"<<std::endl;
           break;
   }
}
//Returns private member in TEXTURE_TAG
unsigned int Texture::GET_TEXTURE()
{
    return TEXTURE_TAG;
}



Texture::Texture(std::string Image_File, Wrapping wrap, Filter filter)
{
   
    glGenTextures( 1, &TEXTURE_TAG );
    glActiveTexture(TEXTURE_TAG);
    Texture_Bind();

   
   
   //Checks the wrap and filter than the user wants to use for the respective texture
   //Then runs the appropriate glTexParamenteri function
    if(wrap == Repeat)
{
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
}
    if(wrap == Mirrored_Repeat)
{
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_MIRRORED_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_MIRRORED_REPEAT );
}
        if(wrap == Clamp_Border)
    {
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_CLAMP_TO_BORDER );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_CLAMP_TO_BORDER );
    }
        if(wrap == Clamp_Edge)
    {
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_CLAMP_TO_EDGE );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_CLAMP_TO_EDGE );
    }
   
   int width, height;
//Uses soil to create a pointer to the image
    unsigned char* image = SOIL_load_image( Image_File.c_str(  ) , &width,&height , 0, SOIL_LOAD_RGBA);
    glTexImage2D( GL_TEXTURE_2D, 0 , GL_RGBA , width, height, 0, GL_RGBA , GL_UNSIGNED_BYTE, image   );
      glGenerateMipmap( GL_TEXTURE_2D );
   
   
    if( filter == Filter:: Nearest )
    {
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
        glTexParameteri(  GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    }
    //How to pick what types the filter and wrap are
    
   SOIL_free_image_data( image );
}

void Texture:: GET_BORDER( float* color )
{
   glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
}
