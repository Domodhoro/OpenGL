#version 300 es

layout(location = 0) in vec3 vertexCoords;
layout(location = 1) in vec2 textureCoords;

uniform mat4 model, view, projection;

out highp vec2 Texture;

void main()
{
    gl_Position = projection * view * model * vec4(vertexCoords, 1.0f);
    Texture = textureCoords;
}
