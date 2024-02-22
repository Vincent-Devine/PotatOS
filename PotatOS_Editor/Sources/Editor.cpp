#include "Editor.hpp"

#include <Wrapper/JsonLayer.hpp>
#include <Wrapper/Window.hpp>
#include <Core/ResourceManager.hpp>

namespace UI
{
	Editor::Editor(Core::Engine& p_engine, Wrapper::RHI& p_rhi, Wrapper::Window& p_window, Input::InputManager& p_inputManager)
		: engine(p_engine)
		, rhi(p_rhi)
        , window(p_window)
        , inputManager(p_inputManager)
        , actionInputChange(nullptr)
        , remappedQuitEditor(false)
	{
        playIcon = Core::ResourceManager::Get()->UseTexture("UI_Assets/Icon/PlayButton.png");
        pauseIcon = Core::ResourceManager::Get()->UseTexture("UI_Assets/Icon/PauseButton.png");
        visionFilter = rhi.GetVisionType();

	}

	void Editor::Init()
	{
		uiLayer.Init(window);
        guizmo.Init(&engine);

        ImGuiIO& io = ImGui::GetIO();
        io.Fonts->AddFontFromFileTTF("Resources/Fonts/Arial/arial.ttf",18.f);
        ImGui::GetIO().Fonts->Build();
	}

	void Editor::Update()
	{

		rhi.Render(engine.GetCurrentScene());
		uiLayer.Update();
        Input();
	}

	void Editor::Render()
	{
        SetDockSpace(true);
        Toolbar();

		viewport.Draw(rhi, guizmo, graphScene.GetGameObjectSelected(), window.windowSize);
		graphScene.Draw(engine.GetCurrentScene());
		inspector.Draw(engine.GetCurrentScene()->GetGraphScene(), graphScene.GetGameObjectSelected(), graphScene.GetColliderSelected(), engine.GetCurrentScene(), assets.GetDirectoryPath());
        audioMixerUI.Draw();
        assets.Draw(engine);
		uiLayer.Draw();

	}

	void Editor::Destroy()
	{
		uiLayer.Destroy();
	}


    void Editor::SetDockSpace(bool p_open)
    {
        static bool optFullscreen = true;
        static bool optPadding = false;
        static ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_None;
 
        ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (optFullscreen)
        {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }
        else
        {
            dockspaceFlags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }

        if (dockspaceFlags & ImGuiDockNodeFlags_PassthruCentralNode)
            windowFlags |= ImGuiWindowFlags_NoBackground;

        if (!optPadding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("PotatOS Editor", &p_open, windowFlags);
        if (!optPadding)
            ImGui::PopStyleVar();
        if (optFullscreen)
            ImGui::PopStyleVar(2);
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspaceId = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspaceId, ImVec2(0.0f, 0.0f), dockspaceFlags);
        }
     
        if (ImGui::BeginMenuBar())
        {
            EditMenu();
            DisplayMenu();

            ImGui::EndMenuBar();
        }
        ImGui::End();
    }

    void Editor::DisplayMenu()
    {
        ImGui::SetWindowFontScale(1.2f);

        ImGuiStyle* style = &ImGui::GetStyle();
        ImVec4* colors = style->Colors;


        ImVec4 black = ImVec4(0.f, 0.f, 0.f, 1.f);
        ImVec4 darkGrey = ImVec4(0.1059f, 0.1137f, 0.1412f, 1.f);
        ImVec4 mediumDarkGrey = ImVec4(0.2157f, 0.2980f, 0.2784f, 1.f);
        ImVec4 darkGreen = ImVec4(0.2118f, 0.3529f, 0.0314f, 1.f);
        ImVec4 mediumGreen = ImVec4(0.3647f, 0.6157f, 0.0431f, 1.f);
        ImVec4 lightGreen = ImVec4(0.4471f, 0.9216f, 0.2275f, 1.f);


        colors[ImGuiCol_WindowBg] = black;
        colors[ImGuiCol_FrameBg] = darkGrey;
        colors[ImGuiCol_Header] = darkGrey;
        colors[ImGuiCol_HeaderActive] = mediumDarkGrey;
        colors[ImGuiCol_TabActive] = mediumGreen;
        colors[ImGuiCol_TabHovered] = lightGreen;
        colors[ImGuiCol_TabUnfocusedActive] = darkGreen;
        colors[ImGuiCol_Button] = darkGreen;
        colors[ImGuiCol_SliderGrab] = mediumGreen;
        colors[ImGuiCol_SliderGrabActive] = lightGreen;
        colors[ImGuiCol_CheckMark] = mediumGreen;
        colors[ImGuiCol_Separator] = darkGreen;
        colors[ImGuiCol_SeparatorHovered] = lightGreen;
        colors[ImGuiCol_SeparatorActive] = lightGreen;
        colors[ImGuiCol_Tab] = darkGreen;
        colors[ImGuiCol_DockingPreview] = darkGreen;
        colors[ImGuiCol_FrameBgActive] = mediumGreen;
        colors[ImGuiCol_FrameBgHovered] = darkGreen;
        colors[ImGuiCol_TitleBgActive] = mediumDarkGrey;
        colors[ImGuiCol_ButtonHovered] = mediumGreen;
        colors[ImGuiCol_ButtonActive] = lightGreen;
        colors[ImGuiCol_HeaderHovered] = mediumGreen;
        colors[ImGuiCol_TextSelectedBg] = mediumGreen;



        if (ImGui::BeginMenu("Display"))
        {
            if (ImGui::BeginMenu("Assets window"))
            {
                ImGui::SliderFloat("ThumbnailSize", &assets.thumbnailSize, 1.0f, 256.0f);
                ImGui::SliderFloat("Padding", &assets.padding, 1.0f, 32.0f);

                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Camera Editor"))
            {
                MonoBehavior::Renderer::Camera* cameraEditor = engine.GetCurrentScene()->GetCameraEditor();
                ImGui::SliderFloat("Speed", cameraEditor->GetPtrSpeed(), 0.f, 150.f);
                ImGui::SliderFloat("Sensitivity", &inputManager.sensitivity, 0.1f, 2.f);
                ImGui::Text("Forward    ");
                ImGui::SameLine();
                if (ImGui::Button(window.GetNameKeyType(inputManager.forward)))
                {
                    actionInputChange = &inputManager.forward;
                }
                ImGui::Text("Backward ");
                ImGui::SameLine();
                if (ImGui::Button(window.GetNameKeyType(inputManager.backward)))
                {
                    actionInputChange = &inputManager.backward;
                }
                ImGui::Text("Left           ");
                ImGui::SameLine();
                if (ImGui::Button(window.GetNameKeyType(inputManager.left)))
                {
                    actionInputChange = &inputManager.left;
                }
                ImGui::Text("Right        ");
                ImGui::SameLine();
                if (ImGui::Button(window.GetNameKeyType(inputManager.right)))
                {
                    actionInputChange = &inputManager.right;
                }
                ImGui::Text("Down       ");
                ImGui::SameLine();
                if (ImGui::Button(window.GetNameKeyType(inputManager.down)))
                {
                    actionInputChange = &inputManager.down;
                }
                ImGui::Text("Up            ");
                ImGui::SameLine();
                if (ImGui::Button(window.GetNameKeyType(inputManager.up)))
                {
                    actionInputChange = &inputManager.up;
                }
                ImGui::Text("Close       ");
                ImGui::SameLine();
                if (ImGui::Button(window.GetNameKeyType(window.GetKeyType(window.closeEditor))))
                {
                    remappedQuitEditor = true;
                }
                if (actionInputChange)
                {
                    KEY_TYPE keyEnter = window.GetLastKeyboardKeyInput();
                    if (keyEnter != KEY_TYPE::KEY_UNKNOWN)
                    {
                        *actionInputChange = keyEnter;
                        actionInputChange = nullptr;
                    }   
                }
                else if (remappedQuitEditor)
                {
                    KEY_TYPE keyEnter = window.GetLastKeyboardKeyInput();
                    if (keyEnter != KEY_TYPE::KEY_UNKNOWN)
                    {
                        window.closeEditor = window.GetGLFWKeyType(keyEnter);
                        remappedQuitEditor = false;
                    }
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("View mode"))
            {
                const char* items[] =
                {
                    "Classic", "Protanopia", "Protanomaly",
                    "Deuteranopia", "Deuteranomaly", "Tritanopia",
                    "Tritanomaly", "Blue cone Monochromacy","Achromatopsia"
                };

                if (ImGui::ListBox("Mode", &item_current, items, IM_ARRAYSIZE(items), 3))
                {
                    for (int n = 0; n < IM_ARRAYSIZE(items); n++)
                    {
                        const bool is_selected = (item_current == n);
                        if (ImGui::Selectable(items[n], is_selected))
                        {
                            item_current = n;
                        }
                        if (is_selected)
                        {
                            ImGui::SetItemDefaultFocus();
                        }
                    }

                }

                ImGui::Text("Selected viewmode");
                ImGui::SameLine();
                ImGui::TextWrapped(items[item_current]);

                rhi.SetVisionType((ColorVisionDeficiency::VISION_TYPE)item_current);
                ImGui::SameLine();

                ImGui::EndMenu();

            }

            ImGui::EndMenu();
        }
    }

    void Editor::EditMenu()
    {
        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::Button("Save scene"))
            {
                Wrapper::Save(engine.GetCurrentScene());
            }

            if (ImGui::BeginMenu("Create scene"))
            {
                static char newName[100];
                ImGui::Text("Enter new scene name");
                ImGui::InputText("Name", newName, IM_ARRAYSIZE(newName));
                if (ImGui::Button("Create scene"))
                {
                    engine.CreateScene(newName);
                }

                ImGui::EndMenu();
            }

            ImGui::EndMenu();
        }
    }

    void Editor::Toolbar()
    {
        ImGui::Begin("##Toolbar", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
        PlayButton();
        ImGui::End();
    }

    void Editor::PlayButton()
    {
        unsigned int icon;
        if (engine.GetGameState() == GAMESTATE::EDIT)
        {
            icon = playIcon->GetIdText();
        }
        else
        {
            icon = pauseIcon->GetIdText();
        }

        float size = ImGui::GetWindowHeight() - 10.f;
        ImGui::SetCursorPosX((ImGui::GetWindowContentRegionMax().x * 0.5f) - (size * 0.5f));
        if (ImGui::ImageButton((ImTextureID)icon, {size, size}, { 0, 1 }, { 1, 0 }, 0))
        {
            engine.ChangeGameState();
        }
    }

    void Editor::Input()
    {
        if (lastKeySInteraction == static_cast<int>(KEY_INTERACTION_TYPE::RELEASE) &&
            Wrapper::Window::Get()->GetKey(KEY_TYPE::KEY_S, KEY_INTERACTION_TYPE::PRESS) &&
            Wrapper::Window::Get()->GetKey(KEY_TYPE::KEY_LEFT_CONTROL, KEY_INTERACTION_TYPE::PRESS)
            && engine.GetGameState() == GAMESTATE::EDIT)
        {
            Wrapper::Save(engine.GetCurrentScene());
        }

        lastKeySInteraction = Wrapper::Window::Get()->GetKey(KEY_TYPE::KEY_S, KEY_INTERACTION_TYPE::PRESS);
    }
}
