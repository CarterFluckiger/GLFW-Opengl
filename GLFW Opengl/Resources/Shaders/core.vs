#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

out vec3 TexCoord
out vec2 ourColor;


void main()
{
    gl_Position = vec4( position, 1.0f) ;
    ourColor = color;
    
    TexCoord = vec2( texCoord.x, 1.0 - texCoord.y );
}

//Original shader file that is used to add color to triangles
//This is an old file that is not used an longer.  I kept it as record if I have to revert back to it
