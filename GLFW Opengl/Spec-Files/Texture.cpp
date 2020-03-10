#include <stdio.h>
#include <iostream>

#include "Spec-Files/Texture.h"

//GLEW
#define GLEW_STATIC
#include <GL/glew.h>
//GLFW
#include <GLFW/glfw3.h>

#include "SOIL2.h"

Texture::Texture
{
    TEXTURE_TAG = 0;
}


void Texture::Bind()
{
    glBindTexture(GL_TEXTURE_2D, TEXTURE_TAG);
}


void Texture:: Unbind()
{
    glBindTexture( GL_TEXTURE_2D , 0 );
}


void Texture:: CHOOSE_TEXTURE(unsigned int TEXTURE_NUMBER)
{
   switch(TEXTURE_NUMBER)
   {
       case 0:
           break;
       case 1:
           break;
           
       default: std::cout<<"ERROR:: CHOOSE_TEXTURE::INVALID"<<std::endl;
           break;
   }
}


    
unsigned int Texture::GET_TEXTURE()
{
    return TEXTURE_TAG;
}



Texture::Texture(std::string Image_File, Wrapping wrap, Filter type)
{
    glGenTextures( 1, &TEXTURE_TAG );
    
    Bind();
    
    glActiveTexture(TEXTURE_TAG);
    
    
    
    if(wrap == Repeat)
{
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
}
    if(wrap == )
{
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
}
    //How to pick what types the filter and wrap are
    
    int width, height;
    
      unsigned char* image = SOIL_load_image( "Resources/Images/grass_image.jpeg" , &width,&height , 0, SOIL_LOAD_RGBA);
    
    
    
 
    
}
