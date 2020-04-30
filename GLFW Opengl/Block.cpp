#include "Block.h"
#include "Texture.h"
#include "Header-Files/Shader.h"

Block::Block(BlockType block)
{
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
    

   int Elements = 5;
    
    glm::vec3 * cubePositions;
    cubePositions = new glm::vec3 [Elements];
    
    int z = 0;
    for(int j = 0; j<= 4; j ++)
    {
         cubePositions[Elements] =
       {
          glm::vec3(j , z, z),
       };
       Elements--;
    }
}

void Block::PickType(BlockType block)
{
   switch (block)
   {
      case GRASS:
        
         break;
      case STONE:
       
         break;
         
      default:
         std::cout<<"BLOCK_BLOCKTYPE_INVALID"<<std::endl;
         break;
   }
}
