#version 330 core
in vec2 TexCoord;

out vec4 color;
out vec4 color2;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

void main()
{
    color = texture(ourTexture1, TexCoord);
    color2 = texture(ourTexture2, TexCoord);
}
