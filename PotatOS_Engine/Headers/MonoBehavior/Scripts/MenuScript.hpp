#pragma once

#include <DLLInclude.hpp>
#include <MonoBehavior/AudioSource.hpp>
#include <MonoBehavior/Canva.hpp>
#include <MonoBehavior/Scripts/BaseScript.hpp>

#include <Refureku/Refureku.h>
#include <Refureku/Generated/MenuScript.rfkh.h>

namespace MonoBehavior RFKNamespace()
{
	namespace Script RFKNamespace()
	{
		class RFKClass() POTATOS_ENGINE_API MenuScript : public BaseScript
		{
		private:
			RFKField()
			std::vector<MonoBehavior::Canva *> menuCanva;

			bool canvaSet;
			float spaceButton;

			RFKField()
			int buttonNumber;
			//char* items[6];

			// Input
			int lastKeySInteraction;
			KEY_TYPE* actionInputChange;
			int remapedIterator;
			bool releaseKey;

			bool doOnce;
		public:
			bool showSubtitles;
			static bool showMenu;
			bool releaseKeyMenu;

		public:
			MenuScript();
			void Start(GAMESTATE * p_gameState) override;
			void Update(const float p_deltaTime, const Inputs & p_inputs) override;
			void Draw(const MonoBehavior::Renderer::Camera * p_camera, const DataStructure::LightManager & p_lightManager,
				const MonoBehavior::Renderer::Light * p_light = nullptr) const override;

			void Destroy() override;

			MonoBehavior_Script_MenuScript_GENERATED
		};
	}
}

File_MenuScript_GENERATED