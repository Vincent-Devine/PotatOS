#version 330 core
layout (location = 0) in vec3 aPos;
layout(location = 3) in ivec4 aBoneIDs;
layout(location = 4) in vec4 aWeights;

uniform mat4 lightSpaceMatrix;
uniform mat4 model;
uniform bool isAnimated;

const int MAX_BONES = 200;
const int MAX_BONE_INFLUENCE = 4;
uniform mat4 gBones[MAX_BONES];

void main()
{
    vec4 updatedPosition = vec4(0.0f);

    if(isAnimated) {
        for(int i = 0 ; i < MAX_BONE_INFLUENCE ; i++)
        {
            if(aBoneIDs[i] == -1) 
                continue;

            if(aBoneIDs[i] >= MAX_BONES) 
            {
                updatedPosition = vec4(aPos,1.0f);
                break;
            }

            vec4 localPosition = gBones[aBoneIDs[i]] * vec4(aPos,1.0f);
            updatedPosition += localPosition * aWeights[i];
        }
    }
    else
    {
        updatedPosition = vec4(aPos, 1.0f);
    }

    gl_Position = lightSpaceMatrix * model * updatedPosition;
}