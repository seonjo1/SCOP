#version 330 core
in vec2 texCoord;
in vec3 color;
out vec4 fragColor;

uniform sampler2D tex;

void main() {
	fragColor = vec4(color, 1.0f);
}