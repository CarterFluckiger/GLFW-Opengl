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


#include "Shader.h"
#include "Texture.h"


//This class is not used in the project the way that it is currently

// I am working towards its implementation but in the current state it is not

//Enum for the type of block
enum BlockType{GRASS, STONE };

class Block
{
public:
   //Pre conditions- Block object created
   //Post conditions- None
   Block()
   {

   }
   //Pre conditions- Block object created
   //Post conditions- Deletes pointers that are left over
   ~Block()
   {
    delete vertices;
   delete indices;
     delete cubePositions;
   }
   //Pre conditions- Block object created and block attribube is fufilled
   //Post conditions- At the moment nothing
   Block( BlockType block );
   
   // Isn't created yet
   void PickType(BlockType block);
   //Isn't created yet
   void MakeChunk();

   // Isn't created yet
   void InsertBlock(  );
   
   //  Next 3 functions are get functions for private variables
   int Get_Other_Elements()
   {
      return otherelements;
   }
   glm::vec3 GetCube(GLuint i)
   {
      return cubePositions[i];
   }
GLfloat *  Get_Amount_Vertices()
   {
      return vertices;
   }
   


   
   
private:
   //Variables are used for the creation of blocks and chunks
   
   glm::vec3 * cubePositions;
   int otherelements;
   GLfloat * vertices;
   int Elements = 0;;
   float * indices;
   unsigned int Amount_Of_Vertices = 192;
   const int Amount_Of_Indices = 36;
   int data;
};

#endif /* Block_h */

