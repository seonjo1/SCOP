#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec3 aColor;

uniform mat4 viewModel;
uniform mat4 projection;

out vec2 texCoord;
out vec3 color;

void main() {
    gl_Position = projection * viewModel * vec4(aPos, 1.0f);
    texCoord = aTexCoord;

    // 각 정점의 위치를 기반으로 의사난수 생성
    color = aColor;
}