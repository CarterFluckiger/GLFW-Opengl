#ifndef Texture_h
#define Texture_h

//GLEW
#define GLEW_STATIC
#include <GL/glew.h>

//GLFW
#include <GLFW/glfw3.h>
//Soil
#include "SOIL2.h"

#include <string>

//Enum for the wrap type
enum Wrapping{Repeat, Mirrored_Repeat, Clamp_Edge, Clamp_Border  };
//enum for Filter type
enum Filter{Linear , Nearest };

class Texture
{
public:
   //Pre conditions- None
//Post conditions- returns a int that is a private member
    unsigned int GET_TEXTURE();
   //Pre conditions- Needs Texture_Number variable that is an input
   //Post conditions- Uses switch statement to apply texture to a GL_TEXTURE int
    void CHOOSE_TEXTURE(unsigned int TEXTURE_NUMBER);
    
   
    //Constructor and destructor
   //Pre conditions- None
   //Post conditions- Sets Texture tag = 0 by default.  Also has  check that can cout an error message which is nice for debugging
    Texture();
   //Pre conditions-None
   //Post conditions- None
    ~Texture();
    
   //Pre conditions- The variable are given when called
   //Post conditions- The texture is created with all of the specific
   // things like wrapping and filter adding
   Texture(std::string Image_File, Wrapping wrap, Filter type);
   //Pre conditions- None
   //Post conditions- Rune the glBindTexture function that needs the
   // Texture in and Texture tag int
    void Texture_Bind();
   //Pre conditions- None
   //Post conditions- Unbinds texture that needs GL_TEXTURE_2D
    void Texture_Unbind();
   //Pre conditions- needs color pointer
   //Post conditions- Runs gl function to set the border
   void GET_BORDER( float* color );
    
    
private:
   //Texture int to keep track of each texture
    unsigned int TEXTURE_TAG;
};

#endif /* Texture_h */
