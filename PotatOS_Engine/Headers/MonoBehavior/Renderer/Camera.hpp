#pragma once

#include <DLLInclude.hpp>
#include <Common.hpp>
#include <Math/Vector3.hpp>
#include <Math/Mat4.inl>
#include <MonoBehavior/IComponent.hpp>

#include <Refureku/Refureku.h>
#include <Refureku/Generated/Camera.rfkh.h>

namespace MonoBehavior RFKNamespace()
{
	namespace Renderer RFKNamespace()
	{
		class RFKClass() POTATOS_ENGINE_API Camera : public IComponent
		{
			//Attributes
		private:
			Math::Vector3 rotation;
			
			float zFar;
			float zNear;
			float aspect;

			RFKField()
				float FOV;

			RFKField()
				float speed;

			Math::Mat4 view;
			Math::Mat4 projection;

		// Methods
		public:
			void Init(const int p_width, const int p_height);
			void Update(const float p_deltaTime, const Inputs& p_inputs) override;

			const Math::Mat4& GetView() const { return view; };
			const Math::Mat4& GetProjection() const { return projection; };

			const Math::Vector3& GetRotation() const { return rotation; };
			const float GetFOV() const { return FOV; };

			Math::Vector3* GetPtrRotation() { return &rotation; };
			float* GetPtrSpeed() { return &speed; };
			float* GetPtrFOV() { return &FOV; };

		private:
			void CalcView();
			void CalcProjection();

			MonoBehavior_Renderer_Camera_GENERATED
		};
	}
}

File_Camera_GENERATED


