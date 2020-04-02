#ifndef Texture_h
#define Texture_h

//GLEW
#define GLEW_STATIC
#include <GL/glew.h>

//GLFW
#include <GLFW/glfw3.h>
//Soil
#include "SOIL2.h"

//Enum for the wrap type
enum Wrapping{Repeat, Mirrored_Repeat, Clamp_Edge, Clamp_Border  };
//enum for Filter type
enum Filter{Linear , Nearest };

class Texture
{
public:
    unsigned int GET_TEXTURE();
    void CHOOSE_TEXTURE(unsigned int TEXTURE_NUMBER);
    
   
    //Constructor and destructor
    Texture();
    ~Texture();
    
    Texture(std::string Image_File, Wrapping wrap, Filter type);
    void Texture_Bind();
    void Texture_Unbind();
   void GET_BORDER( float* color );
    
    
private:
    unsigned int TEXTURE_TAG;
};

#endif /* Texture_h */
