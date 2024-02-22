#include "pch.h"
#include <MonoBehavior/SoundAsset.hpp>

namespace MonoBehavior
{
    SoundAsset::SoundAsset()
    {
        componentType = SCRIPT;
        rhi = Wrapper::RHI::Get();

        shader = Core::ResourceManager::Get()->UseShader("Resources/Shaders/Sound.vert", "Resources/Shaders/Sound.frag");
    }

    void SoundAsset::Draw(const MonoBehavior::Renderer::Camera* p_camera, const DataStructure::LightManager& p_lightManager,
        const MonoBehavior::Renderer::Light* p_light) const
    {
        if (p_light)
        {
            return;
        }
        Math::Vector3 soundSourcePosition = gameObject->transform.GetPosition();
        Math::Vector3 listenerPosition = p_camera->gameObject->transform.GetPosition();
        Math::Vector3 soundDirection = Math::Vector3::Normalize(soundSourcePosition - listenerPosition);

        float quadVertices[4][2] =
        {
        -1.0f, -1.0f,
         1.0f, -1.0f,
        -1.0f,  1.0f,
         1.0f,  1.0f
        };

        rhi->InitSoundAsset(VBO, VAO, textID, quadVertices);

        shader->Use();
        shader->SetVec3("soundDirection", soundDirection);

        //rhi->DrawSoundAsset();
        rhi->BindSoundAsset(VAO, textID);
    }


}