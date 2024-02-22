#pragma once

#include <DLLInclude.hpp>
#include <MonoBehavior/AudioSource.hpp>
#include <MonoBehavior/Canva.hpp>
#include <MonoBehavior/Scripts/BaseScript.hpp>

namespace MonoBehavior
{
	namespace Script
	{
		class POTATOS_ENGINE_API PlayThemeScript : public BaseScript
		{
		private:
			MonoBehavior::Canva * canva;

			MonoBehavior::AudioSource* audioSource;

			std::string soundName;

			bool canvaSet;
			bool AudioSourceSet;

			float increment;

			bool doOnce;

		public:
			void Start(GAMESTATE * p_gameState) override;
			void Update(const float p_deltaTime, const Inputs & p_inputs) override;

		};
	}
}
