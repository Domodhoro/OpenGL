#version 300 es

out highp vec4 FragColor;
uniform sampler2D TextureSampler;
in highp vec2 Texture;

void main()
{
    FragColor = texture(TextureSampler, Texture);
}
