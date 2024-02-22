#version 330 core

#define MAX_DIRECTIONAL_LIGHT 5
#define MAX_POINT_LIGHT 5
#define MAX_SPOT_LIGHT 5


layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BloomColor;

in VS_OUT
{
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} fs_in;

// Texture
uniform sampler2D texture_;

// Light
struct LightData
{
    vec3 lightPosition;
    vec3 viewPosition;
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
};

struct DirectionalLightData
{
    LightData lightData;
    vec3 direction;
};

struct PointLightData
{
    LightData lightData;
    float constant;
    float linear;
    float quadratic;
};

struct SpotLightData
{
    LightData lightData;
    vec3 direction;
    float cutOff;
    float outerCutOff;
};

uniform float nbDirectionalLight;
uniform float nbPointLight;
uniform float nbSpotLight;

uniform DirectionalLightData directionalLights[MAX_DIRECTIONAL_LIGHT];
uniform PointLightData pointLights[MAX_POINT_LIGHT];
uniform SpotLightData spotLights[MAX_SPOT_LIGHT];

vec4 DirectionalLight(DirectionalLightData p_data)
{
    // Diffuse
    vec3 norm = normalize(fs_in.Normal);
    vec3 lightDir = normalize(-p_data.direction);
    float diff = max(dot(norm, lightDir), 0.0);

    // Specular
    vec3 viewDir = normalize(p_data.lightData.viewPosition - fs_in.FragPos);
    vec3 reflectDir = reflect(lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

    return p_data.lightData.ambient + (diff * p_data.lightData.diffuse) + (spec * p_data.lightData.specular); 
}

vec4 PointLight(PointLightData p_data)
{
    float distance = length(p_data.lightData.lightPosition - fs_in.FragPos);
    float attenuation = 1.0 / (p_data.constant + p_data.linear * distance + p_data.quadratic * (distance * distance));

    // Diffuse
    vec3 norm = normalize(fs_in.Normal);
    vec3 lightDir = normalize(p_data.lightData.lightPosition - fs_in.FragPos);
    float diff = max(dot(norm, lightDir), 0.0);

    // Specular
    vec3 viewDir = normalize(p_data.lightData.viewPosition - fs_in.FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

    return p_data.lightData.ambient * attenuation + (diff * p_data.lightData.diffuse * attenuation) + (spec * p_data.lightData.specular * attenuation); 
}

vec4 SpotLight(SpotLightData p_data)
{

    // Diffuse
    vec3 lightDir = normalize(p_data.lightData.lightPosition - fs_in.FragPos);
    float theta = dot(lightDir, normalize(-p_data.direction));
    if(theta > p_data.cutOff)
    {
        float epsilon = p_data.cutOff - p_data.outerCutOff;
        float intensity = clamp((theta - p_data.outerCutOff) / epsilon, 0.0, 1.0);

        vec3 norm = normalize(fs_in.Normal);
        float diff = max(dot(norm, lightDir), 0.0);

        // Specular
        vec3 viewDir = normalize(p_data.lightData.viewPosition - fs_in.FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

        return p_data.lightData.ambient + (diff * p_data.lightData.diffuse * intensity) + (spec * p_data.lightData.specular * intensity); 
    }
    else
    {
        return p_data.lightData.ambient;
    }
}

vec4 LightCalc()
{
    vec4 result;
    for(int i = 0; i < nbDirectionalLight; i++)
    {
        result += DirectionalLight(directionalLights[i]);
    }

    for(int i = 0; i < nbPointLight; i++)
    {
        result += PointLight(pointLights[i]);
    }

    for(int i = 0; i < nbSpotLight; i++)
    {
        result += SpotLight(spotLights[i]);
    }

    return result;
}


void main()
{           
    vec4 text = texture(texture_, fs_in.TexCoords);
    vec4 light = LightCalc();

    vec4 result = text * light;

    float brightness = dot(result.rgb, vec3(0.2126f, 0.7152f, 0.0722f));    
    if(brightness > 1.0f)
    {
        BloomColor = vec4(result.rgb, 1.0f);
    }
    else
    {
        BloomColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    }

    FragColor = result;
}