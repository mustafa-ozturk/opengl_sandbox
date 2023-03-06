#version 400

in vec3 vertexPositions;

uniform mat4 u_MVP;

void main() {
    gl_Position = u_MVP * vec4(vertexPositions, 1.0);
}