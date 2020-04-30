#ifndef Block_h
#define Block_h

//GLEW
#define GLEW_STATIC
#include <GL/glew.h>

//GLFW
#include <GLFW/glfw3.h>
//Soil
#include "SOIL2.h"

//glm
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


#include "Header-Files/Shader.h"
#include "Texture.h"

enum BlockType{GRASS, STONE };

class Block
{
public:
   Block()
   {

   }
   ~Block()
   {
     
   }
   Block( BlockType block );
   void PickType(BlockType block);

   
   void InsertBlock(  );
   


   
   
private:

   float * indices;
   const int Amount_Of_Vertices = 192;
   const int Amount_Of_Indices = 36;
   int data;
};

#endif /* Block_h */

