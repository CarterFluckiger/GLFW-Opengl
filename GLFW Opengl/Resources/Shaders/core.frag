#version 330 core
in vec3 ourColor;
in vec2 TexCoord;

out vec4 color;

uniform sampler2D ourTexture1;

void main()
{
    color = texture(ourTexture1, TexCoord)
}

//Original fragment file that is used to add color to triangles
//This is an old file that is not used an longer.  I kept it as record if I have to revert back to it
