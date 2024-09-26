#version 330 core
in vec2 texCoord;
in vec3 color;
out vec4 fragColor;

uniform sampler2D tex;
uniform float texRatio;

void main() {
	fragColor = texture(tex, texCoord) * texRatio + vec4(color, 1.0f) * (1 - texRatio);
}