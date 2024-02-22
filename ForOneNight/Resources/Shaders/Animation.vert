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
    vec4 totalPosition = vec4(0.0f);
    for(int i = 0 ; i < MAX_BONES_INFLUENCES ; i++)
    {
        if(aBoneIDs[i] == -1) 
            continue;
        if(aBoneIDs[i] >= MAX_BONES) 
        {
            totalPosition = vec4(aPos,1.0f);
            break;
        }
        vec4 localPosition = gBones[aBoneIDs[i]] * vec4(aPos,1.0f);
        totalPosition += localPosition * aWeights[i];
    }
        
    vs_out.FragPos = vec3(model * totalPosition);
    vs_out.TexCoords = aTexCoords;
    vs_out.Normal = mat3(transpose(inverse(model))) * aNormal;

    gl_Position =  projection * view * model * totalPosition;
}