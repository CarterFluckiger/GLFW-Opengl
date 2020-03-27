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
       case 1:
           glActiveTexture( GL_TEXTURE_1 );
           break;
       case 2:
           glActiveTexture( GL_TEXTURE_2 );
           break;
       case 3:
           glActiveTexture( GL_TEXTURE_3 );
           break;
           
       default: std::cout<<"ERROR:: CHOOSE_TEXTURE::INVALID\n"<<std::endl;
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
    if(wrap == Mirrored_Repeat)
{
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_Mirrored_Repeat );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_Mirrored_Repeat );
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
    
    
    
    if( filter == Filter:: Nearest )
    {
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
        glTexParameteri(  GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    }
    //How to pick what types the filter and wrap are
    
    int width, height;
    
      unsigned char* image = SOIL_load_image( "Resources/Images/grass_image.jpeg" , &width,&height , 0, SOIL_LOAD_RGBA);
    
    
    
 
    
}
