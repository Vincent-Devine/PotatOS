#pragma once

#include <MonoBehavior/IComponent.hpp>
#include <Wrapper/RHI.hpp>
#include <Core/ResourceManager.hpp>
#include <Wrapper/FontRenderer.hpp>

#include <Refureku/Refureku.h>
#include <Refureku/Generated/Canva.rfkh.h>

namespace MonoBehavior RFKNamespace()
{
	class RFKClass() POTATOS_ENGINE_API Canva : public IComponent
	{
	private:
		Wrapper::RHI* rhi;

		Resource::Shader* shader = nullptr;
		Wrapper::FontRenderer *fontRenderer;
		unsigned int VBO, VAO;


		RFKField()
		Math::Vector4 color;

		RFKField()
		float scale;

		RFKField()
		Math::Vector2 posSet;

		RFKField()
		std::string text;
		
		RFKField()
		bool isText; 

		RFKField()
		float width;

		RFKField()
		float height;

		float widthButton;
		float heightButton;

		Math::Vector2 cursorPos;

		Math::Mat4 camMat;

		RFKField()
		float timer;
	public :
		bool isClicked;
		bool hide;

	public : 
		Canva(Math::Vector2 p_Position, Math::Vector4 p_color,
			float p_width, float p_height, float p_timer, float p_scale);
		Canva();
		Canva(Math::Vector2 & p_Position, Math::Vector4 & p_color,
			float p_width, float p_height, const char* p_text);

		void Draw(const MonoBehavior::Renderer::Camera* p_camera, const DataStructure::LightManager& p_lightManager,
		const MonoBehavior::Renderer::Light* p_light = nullptr) const override;
		void Update(const float p_deltaTime, const Inputs & p_inputs) override;
		void SetText(const char* p_text);
		void SetPos(Math::Vector2& p_newPos);

		const char *  GetText() { return text.c_str();};
		void SetIsTextToFalse() { isText = false; };

		const Math::Vector4 GetColor() const { return color; };
		const Math::Vector2 GetPosition() const { return posSet; };
		const float GetScale() const { return scale; };
		const float GetHeight() const { return height; };
		const float GetWidth() const { return width; };
		const float GetTimer() const { return timer; };

		MonoBehavior_Canva_GENERATED
	};
}
File_Canva_GENERATED
