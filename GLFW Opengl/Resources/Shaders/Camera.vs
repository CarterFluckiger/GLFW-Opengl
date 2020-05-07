#version 330 core
layout (location = 0) in vec3 position;
layout (location = 2) in vec2 texCoord;

out vec2 TexCoord;

//matrix variables that are specific to the camera
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    //gl_Position is used for the camera position and the changes that come with that
    gl_Position = projection * view * model * vec4(position, 1.0f);
    TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);
}
//Current vertex shader that I am using for the camera situation
