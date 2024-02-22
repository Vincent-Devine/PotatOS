#include "pch.h"

#include <sstream>
#include <MonoBehavior/Scripts/MenuScript.hpp>
#include <Input/InputManager.hpp>
#include <Wrapper/Window.hpp>

namespace MonoBehavior::Script
{
	bool MenuScript::showMenu = false;

	MenuScript::MenuScript()
	{
		componentType = SCRIPT;
		buttonNumber = 7;
		canvaSet = false;
		spaceButton = 100.f;
		releaseKeyMenu = true;
	}

	void MenuScript::Start(GAMESTATE* p_gameState)
	{
		showSubtitles = false;
		gameState = p_gameState;

		if (!canvaSet)
		{
			Input::InputManager* inputManager = Input::InputManager::Get();
			Wrapper::Window* window = Wrapper::Window::Get();
			for (size_t index = 0; index <= buttonNumber; index++)
			{
				float tempSpace = spaceButton * index;

				Math::Vector2 tempPos = Math::Vector2(-200.f,-450.f + tempSpace);
				Math::Vector4 tempCol = Math::Vector4(1.f, 1.f, 1.f, 1.f);
				
				std::string tempForward = "Forward : " + std::string(window->GetNameKeyType(inputManager->gameForward));
				std::string tempBackward = "Backward : " + std::string(window->GetNameKeyType(inputManager->gameBackward));
				std::string tempLeft = "Left : " + std::string(window->GetNameKeyType(inputManager->gameLeft));
				std::string tempRight = "Right : " + std::string(window->GetNameKeyType(inputManager->gameRight));
				std::string tempJump = "Jump : " + std::string(window->GetNameKeyType(inputManager->gameJump));
				std::string tempAttack = "Attack : " + std::string(window->GetNameKeyType(inputManager->gameAttack));
				std::string tempMenu = "Menu : " + std::string(window->GetNameKeyType(inputManager->gameMenu));
				std::string tempQuit = "Quit : " + std::string(window->GetNameKeyType(inputManager->gameQuit));

				const char* items[] =
				{
					tempQuit.c_str(), tempMenu.c_str(), tempAttack.c_str(), tempJump.c_str(),
					tempRight.c_str(), tempLeft.c_str(), tempBackward.c_str(), tempForward.c_str()
				};
				menuCanva.push_back(new MonoBehavior::Canva(tempPos, tempCol, 100.f, 50.f, items[index]));
			}
			Math::Vector2 tempPos = Math::Vector2(-100.f, 400.f);
			Math::Vector4 tempCol = Math::Vector4(1.f, 1.f, 1.f, 1.f);
			menuCanva.push_back(new MonoBehavior::Canva(tempPos, tempCol, 100.f, 50.f, "Menu"));
			canvaSet = true;;
		}
		
		for (size_t i = 0; i < menuCanva.size(); i++)
		{
			menuCanva[i]->Start(p_gameState);
			menuCanva[i]->hide = false;
			menuCanva[i]->SetIsTextToFalse();
		}


	}

	void MenuScript::Update(const float p_deltaTime, const Inputs& p_inputs)
	{
		Wrapper::Window* window = Wrapper::Window::Get();
		Input::InputManager* inputManager = Input::InputManager::Get();

		if (p_inputs.showmenu)
		{
			releaseKeyMenu = false;
		}
		if(!releaseKeyMenu)
		{
			releaseKeyMenu = !window->GetKey(inputManager->gameMenu, KEY_INTERACTION_TYPE::PRESS);
			if (releaseKeyMenu)
			{
				showMenu = !showMenu;
			}
			return;
		}

		if (showMenu)
		{

			for (size_t i = 0; i < menuCanva.size(); i++)
			{
				menuCanva[i]->Update(p_deltaTime, p_inputs);
				if (menuCanva[i]->isClicked)
				{
					releaseKey = false;
					Log::Print("Click on " + std::string(menuCanva[i]->GetText()), LOG_LEVEL_TYPE::Debug);
					std::stringstream ss(menuCanva[i]->GetText());
					remapedIterator = i;
					std::string word;
					ss >> word;
					if (word == "Forward")
					{
						actionInputChange = &inputManager->gameForward;
					}
					else if (word == "Backward")
					{
						actionInputChange = &inputManager->gameBackward;
					}
					else if (word == "Left")
					{
						actionInputChange = &inputManager->gameLeft;
					}
					else if (word == "Right")
					{
						actionInputChange = &inputManager->gameRight;
					}
					else if (word == "Jump")
					{
						actionInputChange = &inputManager->gameJump;
					}
					else if (word == "Attack")
					{
						actionInputChange = &inputManager->gameAttack;
					}
					else if (word == "Menu")
					{
						actionInputChange = &inputManager->gameMenu;
					}
					else if (word == "Quit")
					{
						actionInputChange = &inputManager->gameQuit;
					}
					menuCanva[i]->isClicked = false;
					releaseKey = false;
				}
			}
			if (actionInputChange)
			{
				if (!releaseKey)
				{
					releaseKey = !window->GetKey(KEY_TYPE::KEY_MOUSE_BUTTON_LEFT, KEY_INTERACTION_TYPE::PRESS);
					return;
				}
				KEY_TYPE keyEnter = window->GetLastKeyboardKeyInput();
				if (keyEnter != KEY_TYPE::KEY_UNKNOWN)
				{
					*actionInputChange = keyEnter;
					actionInputChange = nullptr;
					std::string tempName = menuCanva[remapedIterator]->GetText();
					int posNewKey = tempName.find(":");
					std::string newName;
					for (int i = 0; i < posNewKey; i++)
					{
						newName.push_back(tempName[i]);
					}
					newName += ": " + std::string(window->GetNameKeyType(keyEnter));
					menuCanva[remapedIterator]->SetText(newName.c_str());
				}
			}
		}
	}

	void MenuScript::Draw(const MonoBehavior::Renderer::Camera* p_camera, 
		const DataStructure::LightManager& p_lightManager, const MonoBehavior::Renderer::Light* p_light) const
	{
		if (showMenu)
		{
			for (size_t i = 0; i < menuCanva.size(); i++)
			{
				menuCanva[i]->Draw(p_camera, p_lightManager, p_light);
			}
		}
	}


	void MenuScript::Destroy()
	{
		for (Canva* canva : menuCanva)
		{
			delete canva;
		}
	}

	}
