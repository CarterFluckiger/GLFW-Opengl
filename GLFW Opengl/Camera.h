
#ifndef Camera_h
#define Camera_h

#include <vector>
#include <iostream>


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

#include "Window.h"


//Enum for the movement types
enum CAMERA_MOVEMENT{FORWARD, BACKWARD , RIGHT, LEFT , DOWN , UP};
//Values used in the camera class
const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 0.15f;
const GLfloat SENSITIVITY = 0.20f;
const GLfloat ZOOM = 45.0f;



class Camera
{
public:
   //Pre conditions- Camera object is created and attribute are fufilled when called
   //Post conditions- Sets data for the beginning of the program, for example it sets the beginning position of the camera
   Camera( glm::vec3 position = glm::vec3( 0.0f, 2.0f, 0.0f ), glm::vec3 up = glm::vec3( 0.0f, 1.0f, 0.0f ), GLfloat yaw = YAW, GLfloat pitch = PITCH ) : front( glm::vec3( 0.0f, 0.0f, -1.0f ) ), movementSpeed( SPEED ), mouseSensitivity( SENSITIVITY ), zoom( ZOOM )
   {
      this->position = position;
      this->worldUp = up;
      this->yaw = yaw;
      this->pitch = pitch;
      this->updateCameraVectors(  );
   }
   //Pre conditions- Camera objects is created and attribues are fufilled when called
   //Post conditions- Updates many of the variables dealing with the camera
   Camera( GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch ) : front( glm::vec3( 0.0f, 0.0f, -1.0f ) ), movementSpeed( SPEED ), mouseSensitivity( SENSITIVITY ), zoom( ZOOM )
   {
      this->position = glm::vec3(posX, posY, posZ );
      this->worldUp = glm::vec3(upX, upY, upZ );
      this->yaw = yaw;
      this->pitch = pitch;
      this->updateCameraVectors(  );
      
      realposZ = posZ;
   }
   
   //Pre conditions- Camera object created
   //Post conditions- get function that return the view matrix
   glm::mat4 GetViewMatrix(  )
   {
      return glm::lookAt( this->position, this->position + this->front , this->up );
   }
   //Pre conditions- Attributes are used when calling
   //Post conditions-Uses position and velocity to move the camera view
   void ProcessKeyboard( CAMERA_MOVEMENT direction, GLfloat deltaTime )
   {
      GLfloat velocity = this->movementSpeed + deltaTime;
      
      if( FORWARD == direction )
      {
         this->position += this->front * velocity;
      }
      
      if( BACKWARD == direction )
      {
         this->position -= this->front * velocity;
      }
      if( LEFT == direction )
      {
         this->position -= this->right * velocity;
      }
      if( RIGHT == direction )
      {
         this->position += this->right * velocity;
      }
      if(UP == direction)
      {
         this->position += this->up * velocity;
      }
      if(DOWN == direction)
      {
         this->position -= this->up * velocity;
      }
   }
   //Pre conditions- Has attributes when called
   //Post conditions- This function is used when turning around the camera "comes back around" in a circle like in real life
   void ProcessMouseMovement( GLfloat xOffset , GLfloat yOffset, GLboolean constrainPitch = true )
   {
      xOffset *= this->mouseSensitivity;
      yOffset *= this->mouseSensitivity;
      
      this->yaw += xOffset;
      this->pitch += yOffset;
      
                     if( constrainPitch )
                     {
                        if( this->pitch > 89.0f )
                        {
                           this->pitch =  89.0f;
                        }
                        
                        if( this->pitch < -89.0f )
                        {
                           this->pitch = -89.0f;
                        }
                     }
      
      this->updateCameraVectors(  );
   }
   
   //Pre conditions- Has GLfloat value
   //Post conditions- This function is used for the opticfind function which is a zoom feature
   void ProcessMouseScroll( GLfloat yOffseet )
   {
      if(this->zoom >= 1.0f && this-> zoom <= 45.0f)
      {
         this->zoom -= yOffseet;
      }
      
      if( this->zoom <= 1.0f )
      {
         this->zoom = 1.0f;
      }
      if( this->zoom >=45.0f )
      {
         this->zoom = 45.0f;
      }
   }
   
   //Pre conditions- None
   //Post conditions- return zoom
GLfloat GetZoom(  )
   {
      return this->zoom;
   }

   //The GetPosZ function is a prototype for not falling through the z axis
   // It is not in use yet
    GLfloat realposZ;
   GLfloat GetPosZ()
   {
      return realposZ;
   }
     
private:
   //private variable
   glm::vec3 position;
   glm::vec3 front;
   glm::vec3 up;
   glm::vec3 right;
   glm::vec3 worldUp;
   
   GLfloat yaw;
   GLfloat pitch;
   

   
   GLfloat movementSpeed;
   GLfloat mouseSensitivity;
   GLfloat zoom;
   
   //Pre conditions- None
   //Post conditions- Calculates the front and side vectos and resets them when moving
      void updateCameraVectors( )
       {
           // Calculate the new Front vector
           glm::vec3 front;
           front.x = cos( glm::radians( this->yaw ) ) * cos( glm::radians( this->pitch ) );
           front.y = sin( glm::radians( this->pitch ) );
           front.z = sin( glm::radians( this->yaw ) ) * cos( glm::radians( this->pitch ) );
           this->front = glm::normalize( front );
           // Also re-calculate the Right and Up vector
           this->right = glm::normalize( glm::cross( this->front, this->worldUp ) );  // Normalize the vectors
           this->up = glm::normalize( glm::cross( this->right, this->front ) );
       }
   };



#endif /* Camera_h */
