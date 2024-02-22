#version 330 core

uniform vec3 soundDirection;

out vec4 FragColor;

void main()
{
    vec3 normalizedDirection = normalize(soundDirection);
    vec3 color = (normalizedDirection + 1.0) * 0.5;
    FragColor = vec4(color, 1.0);
}