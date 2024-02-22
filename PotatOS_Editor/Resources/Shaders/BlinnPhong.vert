#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;
layout(location = 3) in ivec4 aBoneIDs;
layout(location = 4) in vec4 aWeights;

out VS_OUT
{
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} vs_out;

const int MAX_BONES = 200;
const int MAX_BONES_INFLUENCES = 4;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 gBones[MAX_BONES];

void main()
{
    vs_out.FragPos = vec3(model * vec4(aPos, 1.f));   
    vs_out.Normal = mat3(transpose(inverse(model))) * aNormal;
    vs_out.TexCoords = aTexCoords;
    gl_Position =  projection * view * model * vec4(aPos, 1.f);
}