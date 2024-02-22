#include "pch.h"
#include <MonoBehavior/Canva.hpp>

namespace MonoBehavior
{
    Canva::Canva()
    {
        componentType = CANVA;
        hide = true;
        fontRenderer = new Wrapper::FontRenderer();

        color = Math::Vector4(1.f, 1.f, 1.f, 1.f);
        posSet = Math::Vector2(0.f, -450.f);

        scale = 1.f;
        rhi = Wrapper::RHI::Get();

        height = 100.f;
        width = 100.f;

        heightButton = 100.f;
        widthButton = 100.f;


        isText = false;
        shader = Core::ResourceManager::Get()->UseShader("Resources/Shaders/Font.vert", "Resources/Shaders/Font.frag");
        rhi->InitCanva(VBO, VAO);

        isClicked = false;
        timer = 5.f;
    }

    Canva::Canva(Math::Vector2& p_Position, Math::Vector4& p_color, float p_width, float p_height, const char * p_text)
    {
        componentType = CANVA;
        text = p_text;
        hide = true;
        fontRenderer = new Wrapper::FontRenderer();

        color = p_color;
        posSet = p_Position;

        scale = 1.f;
        rhi = Wrapper::RHI::Get();

        heightButton = p_height;
        widthButton = p_width;

        height = p_height;
        width = p_height;


        isText = false;
        shader = Core::ResourceManager::Get()->UseShader("Resources/Shaders/Font.vert", "Resources/Shaders/Font.frag");
        rhi->InitCanva(VBO, VAO);

        timer = 5.f;
        isClicked = false;
    }

    Canva::Canva(Math::Vector2 p_Position, Math::Vector4 p_color, float p_width, float p_height, float p_timer, float p_scale)
    {
        componentType = CANVA;
        hide = true;
        fontRenderer = new Wrapper::FontRenderer();

        color = p_color;
        posSet = p_Position;

        scale = p_scale;
        rhi = Wrapper::RHI::Get();

        heightButton = p_height;
        widthButton = p_width;

        height = p_height;
        width = p_height;


        isText = false;
        shader = Core::ResourceManager::Get()->UseShader("Resources/Shaders/Font.vert", "Resources/Shaders/Font.frag");
        rhi->InitCanva(VBO, VAO);

        timer = p_timer;
        if (timer == 0.f)
        {
            timer = 5.f;
        }
        isClicked = false;
    }

    void Canva::Draw(const MonoBehavior::Renderer::Camera* p_camera, const DataStructure::LightManager& p_lightManager,
        const MonoBehavior::Renderer::Light* p_light) const
    {

        if (p_light )
        {
            return;
        }

        if (!hide)
        {
            shader->Use();

            shader->SetMat4("projection", p_camera->GetProjection().GetOrthographicProjectionWithoutNearFar());

            shader->SetVec3("textColor", Math::Vector3(color.x, color.y, color.z));
            rhi->StartCanva(VAO);

            std::string::const_iterator c;
            Math::Vector2 posTemp = posSet;

            // iterate through all characters
            for (c = text.begin(); c != text.end(); c++)
            {
                Wrapper::Character ch = fontRenderer->characters[*c];

                float xpos = posTemp.x + ch.bearing.x * scale;
                float ypos = posTemp.y - (ch.size.y - ch.bearing.y) * scale;

                float w = ch.size.x * scale;
                float h = ch.size.y * scale;
                /*if (w > width || h > height)
                {
                    break;
                }*/
                // update VBO for each character
                float vertices[6][4] =
                {
                    { xpos,     ypos + h,   0.0f, 0.0f },
                    { xpos,     ypos,       0.0f, 1.0f },
                    { xpos + w, ypos,       1.0f, 1.0f },

                    { xpos,     ypos + h,   0.0f, 0.0f },
                    { xpos + w, ypos,       1.0f, 1.0f },
                    { xpos + w, ypos + h,   1.0f, 0.0f }
                };

                rhi->DrawCanva(VAO, VBO, ch.textureID, vertices);

                posTemp.x += (ch.advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
            }

            rhi->BindCanva();
            

        }
    }

    void Canva::Update(const float p_deltaTime, const Inputs& p_inputs)
    {
        if (!isText)
        {
            if (Wrapper::Window::Get()->GetKey(KEY_TYPE::KEY_MOUSE_BUTTON_LEFT, KEY_INTERACTION_TYPE::PRESS))
            {
                HWND hwnd = GetActiveWindow();
                RECT rect;
                GetWindowRect(hwnd, &rect);

                int windowWidth = rect.right - rect.left;
                int windowHeight = rect.bottom - rect.top;

                cursorPos = Wrapper::Window::Get()->GetCursorPositionInWindow();
                cursorPos -= Math::Vector2(windowWidth / 2, windowHeight / 2);

                if ((cursorPos.x) < (posSet.x + width)
                    && (cursorPos.x) > posSet.x
                    && (cursorPos.y) < (-posSet.y + height)
                    && (cursorPos.y) > (-posSet.y))
                {
                    isClicked = true;
                }
            }
        }
    }

    void Canva::SetText(const char * p_text)
    {
        text = p_text;
    }

    void Canva::SetPos(Math::Vector2& p_newPos)
    {
        posSet = p_newPos;
        scale = 2.f;
    }

}