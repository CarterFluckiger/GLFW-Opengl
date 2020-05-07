#version 330 core
in vec2 TexCoord;

out vec4 color;
out vec4 color2;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;
//Uses "ourTexture1" from our texture in the main.cpp

void main()
{
    color = texture(ourTexture1, TexCoord);
    color2 = texture(ourTexture2, TexCoord);
    //Uses color and color2 with texture pictures
}

//Current fragment shader that I am using for the camera situation
