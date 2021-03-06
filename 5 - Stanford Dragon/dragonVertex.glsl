#version 300 es

layout(location = 0) in vec3 vertexCoords;
layout(location = 1) in vec3 normalCoords;

uniform mat4 model, view, projection;
out highp vec3 Normal, FragPos;

void main() {
    gl_Position = projection * view * model * vec4(vertexCoords, 1.0f);

    Normal = normalize(normalCoords);
	FragPos = vec3(model * vec4(vertexCoords, 1.0f));
}
