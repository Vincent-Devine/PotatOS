#include "Guizmo.hpp"
#include <ImGUI/Include/imgui.h>
#include "DebugSystem/Log.hpp"
#include <imgui_internal.h>
#include <MonoBehavior/Physics/Collider.hpp>

namespace UI
{
	void Guizmo::Init(Core::Engine* p_engine)
	{
		engine = p_engine;
		operation = ImGuizmo::OPERATION::TRANSLATE;
	}

	void Guizmo::Draw(DataStructure::GameObject* p_gameObjectSelected)
	{
		if (!p_gameObjectSelected || engine->GetGameState() == GAMESTATE::PLAY)
		{
			return;
		}

		SetUpImGuizmo();
		Input();
		
		// Camera
		MonoBehavior::Renderer::Camera* camera = engine->GetCurrentScene()->GetCamera();
		Math::Mat4 cameraProjection = camera->GetProjection();
		const float* cameraProjectionPtr = &cameraProjection.Transpose().data[0][0];
		Math::Mat4 cameraView = camera->GetView();
		const float* cameraViewPtr = &cameraView.Transpose().data[0][0];

		// GameObject Transform
		Math::Mat4 modelWorld = p_gameObjectSelected->transform.GetWorldMatrix();
		Math::Mat4 matrixGameObjectPtr = modelWorld.Transpose();

		ImGuizmo::Manipulate(cameraViewPtr, cameraProjectionPtr,
			operation, ImGuizmo::MODE::LOCAL,
			&matrixGameObjectPtr.data[0][0]);

		if (ImGuizmo::IsUsing())
		{
			DataStructure::Transform& transform = p_gameObjectSelected->transform;
			Math::Vector3 translation, rotation, scale;
			
			matrixGameObjectPtr.Decompose(matrixGameObjectPtr, translation, rotation, scale);
			
			if (operation == ImGuizmo::OPERATION::TRANSLATE)
			{
				transform.SetPosition((Math::Quaternion::QuatToMatrix(transform.parentTransform->GetRotation().Invert()) * Math::Vector4(translation - transform.parentTransform->GetPosition(), 1.0f)).ToVector3());
			}
			else if (operation == ImGuizmo::OPERATION::ROTATE)
			{
				transform.SetRotation(transform.parentTransform->GetRotation().Invert() * Math::Quaternion::QuatFromEuler(rotation * Math::RAD2DEG));
			}
			else
			{
				transform.SetScale(scale / transform.parentTransform->GetScale());
			}
			
			MonoBehavior::Physics::Collider* collider = p_gameObjectSelected->GetCollider();
			if (collider)
			{
				collider->SetModified();
			}
		}
	}

	void Guizmo::Input()
	{
		if (ImGui::IsKeyPressed(ImGuiKey_E))
		{
			operation = ImGuizmo::OPERATION::TRANSLATE;
		}
		else if (ImGui::IsKeyPressed(ImGuiKey_R))
		{
			operation = ImGuizmo::OPERATION::ROTATE;
		}
		else if (ImGui::IsKeyPressed(ImGuiKey_T))
		{
			operation = ImGuizmo::OPERATION::SCALE;
		}
	}

	void Guizmo::SetUpImGuizmo()
	{
		ImGuizmo::SetOrthographic(false);
		ImGuizmo::SetDrawlist();
		float windowWidth = static_cast<float>(ImGui::GetWindowWidth());
		float windowHeight = static_cast<float>(ImGui::GetWindowHeight());
		ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);
	}
}