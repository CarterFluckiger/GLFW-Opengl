#include "Block.h"
#include "Texture.h"
#include "Header-Files/Shader.h"



// ***** THIS WHOLE CLASS IS NOT "USED" the code is in the main
// I could not get the info to move succefully to the main

void Block::MakeChunk()
{
   vertices = new GLfloat [Amount_Of_Vertices]
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
   
   Elements =5120;
      otherelements = Elements;
     //2560 is a chunk
    
     cubePositions = new glm::vec3 [Elements];
     
     int f =1;
     int z = 0;
     for(int l = 0; l<=1;l++)
     {
        int m = 0;
   
        if(l >= 1 )
        {
           m=17*f;
           f++;
        }
     for(int p = 0; p<=9; p++)
     {
     for(int j =0;  j <= 15; j++)
     {
          cubePositions[Elements] =
        {
         glm::vec3(j+m , p, z)
        };
        Elements--;
        for(int r = 1; r<=15;r++)
        {
           cubePositions[Elements] =
           {
              glm::vec3( j+m, p, r)
           };
           Elements--;
        }
     }
     }
     }
   
   //All similar to the main
}

//Function for picking what block will be created
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
