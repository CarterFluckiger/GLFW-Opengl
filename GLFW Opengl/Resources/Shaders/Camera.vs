#version 330 core


void main()
{
    
    
vec3 cameraPos =vec3(0.0f, 0.0f, 3.0f);
vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
    glm::vec3 up = glm::vec3( 0.0f, 1.0f, 0.0f );
    glm::vec3 camerRight = glm::normalize(glm::cross( up, cameraDirection ));
    glm::vec3 cameraUp = glm::cross(cameraDirection, camerRight);
    
    glm::mat4 view;
    view = glm::lookA( glm::vec3( 0.0f, 0.0f, 3.0f ),
                                        glm::vec3( 0.0f, 0.0f, 0.0f ),
                                        glm::vec3( 0.0f, 1.0f, 0.0f ));
    const float radius = 10.0f;
    float camX = sin(glfwGetTime()) * radius;
    float camZ = cos(glfwGetTime()) * radius;
    glm::mat4 view;
    view = glm::lookAt(camX, 0.0, camZ), glm::vec3(0.0, 0.0,0.0), glm::vec3( 0.0, 1.0, 0.0 );
    
    glm::vec3 cameraPos = glm::vec3( 0.0f, 0.0f, 3.0f );
    glm::vec3 cameraFront = glm::vec3( 0.0f, 0.0f, -1.0f );
    glm::vec3 cameraUp = glm::vec3( 0.0f, 1.0f, 0.0f  );
    
    view = glm::lookAt( cameraPos, cameraPos + cameraFront, cameraUp );
    
    
    
}
