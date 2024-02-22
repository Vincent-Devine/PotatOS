#include "Inspector.hpp"
#include<iostream>
#include <fstream>
#include <sstream>

#include <Refureku/Generated/EntityMacros.h>
#include <Refureku/Generated/Camera.rfks.h>
#include <Refureku/Generated/IComponent.rfks.h>
#include <Refureku/Generated/Light.rfks.h>
#include <Refureku/Generated/PointLight.rfks.h>
#include <Refureku/Generated/DirectionalLight.rfks.h>
#include <Refureku/Generated/SpotLight.rfks.h>
#include <Refureku/Generated/Vector2.rfks.h>
#include <Refureku/Generated/Vector3.rfks.h>
#include <Refureku/Generated/Vector4.rfks.h>
#include <Refureku/Generated/BoxCollider.rfks.h>
#include <Refureku/Generated/SphereCollider.rfks.h>
#include <Refureku/Generated/PlaneCollider.rfks.h>
#include <Refureku/Generated/CapsuleCollider.rfks.h>
#include <Refureku/Generated/Collider.rfks.h>
#include <Refureku/Generated/IResource.rfks.h>
#include <Refureku/Generated/AudioSource.rfks.h>
#include <Refureku/Generated/Animator.rfks.h>
#include <Refureku/Generated/Sound.rfks.h>
#include <Refureku/Generated/Animation.rfks.h>
#include <Refureku/Generated/Texture.rfks.h>
#include <Refureku/Generated/Shader.rfks.h>
#include <Refureku/Generated/Mesh.rfks.h>
#include <Refureku/Generated/Model.rfks.h>
#include <Refureku/Generated/Canva.rfks.h>
#include <Refureku/Generated/BaseScript.rfks.h>

namespace UI
{
	void Inspector::Draw(DataStructure::GraphScene& p_scenegraph, DataStructure::GameObject* p_gameObjectSelected,
		MonoBehavior::Physics::Collider* p_colliderSelected, Core::Scene* p_scene, std::filesystem::path p_pathDir)
	{

		std::ifstream file("Log.txt");
		if (!file.is_open())
		{
			std::cout << "Failed to open log"; // Return an empty string if the file cannot be opened
		}

		std::stringstream buffer;
		buffer << file.rdbuf();

		std::string contents = buffer.str();

		ImGui::Begin("Log");
		{
			ImGui::TextWrapped("%s", contents.c_str());
		}
		ImGui::End();

		ImGui::Begin("Inspector");
		if (p_gameObjectSelected)
		{
			pathDir = p_pathDir;
			DrawName(p_gameObjectSelected);
			DrawTransform(p_gameObjectSelected, p_colliderSelected);
			AddComponentButton(p_gameObjectSelected, p_scene);
			ShowIComponentFields(p_gameObjectSelected);
		}
		ImGui::End();
	}

	void Inspector::ShowIComponentFields(DataStructure::GameObject* p_gameObject)
	{
		for (size_t i = 0; i < p_gameObject->components.size(); i++)
		{
			if (ImGui::Button(("Delete##" + std::to_string(i)).c_str()))
			{
				p_gameObject->components[i]->Destroy();
				p_gameObject->components.erase(p_gameObject->components.begin() + i);
				break;
			}
			ImGui::SameLine();

			switch (p_gameObject->components[i]->componentType)
			{
			case MonoBehavior::COMPONENT_TYPE::NONE:
			{
				break;
			}
			case MonoBehavior::COMPONENT_TYPE::CAMERA:
			{
				if (ImGui::CollapsingHeader((("Camera##Component" + std::to_string(i)).c_str())))
				{
					ImGui::Indent();
					MonoBehavior::Renderer::Camera* camera = (MonoBehavior::Renderer::Camera*)p_gameObject->components[i];
					selectedObjectFields = camera->staticGetArchetype().getFieldsByPredicate([](rfk::Field const&, void*) { return true; }, camera, true);
					CheckFieldType(selectedObjectFields, camera);
					ImGui::Unindent();
				}
				break;
			}
			case MonoBehavior::COMPONENT_TYPE::POINT_LIGHT:
			{
				if (ImGui::CollapsingHeader(("Point Light##Component" + std::to_string(i)).c_str()))
				{
					ImGui::Indent();
						MonoBehavior::Renderer::PointLight* pointlight = (MonoBehavior::Renderer::PointLight*)p_gameObject->components[i];
						selectedObjectFields = pointlight->staticGetArchetype().getFieldsByPredicate([](rfk::Field const&, void*) { return true; }, pointlight, true);
						CheckFieldType(selectedObjectFields, pointlight);
						ImGui::Unindent();
				}
				break;
			}
			case MonoBehavior::COMPONENT_TYPE::SPOT_LIGHT:
			{
				if (ImGui::CollapsingHeader(("Spot Light##Component" + std::to_string(i)).c_str()))
				{
					ImGui::Indent();
						MonoBehavior::Renderer::SpotLight* spotlight = (MonoBehavior::Renderer::SpotLight*)p_gameObject->components[i];
						selectedObjectFields = spotlight->staticGetArchetype().getFieldsByPredicate([](rfk::Field const&, void*) { return true; }, spotlight, true);
						CheckFieldType(selectedObjectFields, spotlight);
						ImGui::Unindent();
				}
				break;
			}
			case MonoBehavior::COMPONENT_TYPE::DIRECTIONAL_LIGHT:
			{
				if (ImGui::CollapsingHeader(("Directional Light##Component" + std::to_string(i)).c_str()))
				{
					ImGui::Indent();
						MonoBehavior::Renderer::DirectionalLight* directionallight = (MonoBehavior::Renderer::DirectionalLight*)p_gameObject->components[i];
						selectedObjectFields = directionallight->staticGetArchetype().getFieldsByPredicate([](rfk::Field const&, void*) { return true; }, directionallight, true);
						CheckFieldType(selectedObjectFields, directionallight);
						ImGui::Unindent();
				}
				break;
			}
			case MonoBehavior::COMPONENT_TYPE::BOX_COLLIDER:
			{
				if (ImGui::CollapsingHeader(("Box Collider##Component" + std::to_string(i)).c_str()))
				{
					ImGui::Indent();
						MonoBehavior::Physics::BoxCollider* boxCollider = (MonoBehavior::Physics::BoxCollider*)p_gameObject->components[i];
						selectedObjectFields = boxCollider->staticGetArchetype().getFieldsByPredicate([](rfk::Field const&, void*) { return true; }, boxCollider, true, true);
						CheckFieldType(selectedObjectFields, boxCollider);
						ImGui::Unindent();
				}
				break;
			}
			case MonoBehavior::COMPONENT_TYPE::CAPSULE_COLLIDER:
			{
				if (ImGui::CollapsingHeader(("Capsule Collider##Component" + std::to_string(i)).c_str()))
				{
					ImGui::Indent();
						MonoBehavior::Physics::CapsuleCollider* capsuleCollider = (MonoBehavior::Physics::CapsuleCollider*)p_gameObject->components[i];
						selectedObjectFields = capsuleCollider->staticGetArchetype().getFieldsByPredicate([](rfk::Field const&, void*) { return true; }, capsuleCollider, true, true);
						CheckFieldType(selectedObjectFields, capsuleCollider);
						ImGui::Unindent();
				}
				break;
			}
			case MonoBehavior::COMPONENT_TYPE::SPHERE_COLLIDER:
			{
				if (ImGui::CollapsingHeader(("Sphere Collider##Component" + std::to_string(i)).c_str()))
				{
					ImGui::Indent();
						MonoBehavior::Physics::SphereCollider* sphereCollider = (MonoBehavior::Physics::SphereCollider*)p_gameObject->components[i];
						selectedObjectFields = sphereCollider->staticGetArchetype().getFieldsByPredicate([](rfk::Field const&, void*) { return true; }, sphereCollider, true, true);
						CheckFieldType(selectedObjectFields, sphereCollider);
						ImGui::Unindent();
				}
				break;
			}
			case MonoBehavior::COMPONENT_TYPE::PLANE_COLLIDER:
			{
				if (ImGui::CollapsingHeader(("Plane Collider##Component" + std::to_string(i)).c_str()))
				{
					ImGui::Indent();
						MonoBehavior::Physics::PlaneCollider* planeCollider = (MonoBehavior::Physics::PlaneCollider*)p_gameObject->components[i];
						selectedObjectFields = planeCollider->staticGetArchetype().getFieldsByPredicate([](rfk::Field const&, void*) { return true; }, planeCollider, true, true);
						CheckFieldType(selectedObjectFields, planeCollider);
						ImGui::Unindent();
				}
				break;
			}
			case MonoBehavior::COMPONENT_TYPE::AUDIOSOURCE:
			{
				if (ImGui::CollapsingHeader(("AudioSource##Component" + std::to_string(i)).c_str()))
				{
					ImGui::Indent();
						MonoBehavior::AudioSource* audioSource = (MonoBehavior::AudioSource*)p_gameObject->components[i];
						selectedObjectFields = audioSource->staticGetArchetype().getFieldsByPredicate([](rfk::Field const&, void*) { return true; }, audioSource, true, true);
						CheckFieldType(selectedObjectFields, audioSource);
						ImGui::Unindent();
				}
				break;
			}
			case MonoBehavior::COMPONENT_TYPE::ANIMATOR:
			{
				if (ImGui::CollapsingHeader(("Animator##Component" + std::to_string(i)).c_str()))
				{
					ImGui::Indent();
						MonoBehavior::Animator* animator = (MonoBehavior::Animator*)p_gameObject->components[i];
						selectedObjectFields = animator->staticGetArchetype().getFieldsByPredicate([](rfk::Field const&, void*) { return true; }, animator, true, true);
						CheckFieldType(selectedObjectFields, animator);
						ImGui::Unindent();
				}
				break;
			}
			case MonoBehavior::COMPONENT_TYPE::MODEL:
			{
				if (ImGui::CollapsingHeader(("Model##Component" + std::to_string(i)).c_str()))
				{
					ImGui::Indent();
						MonoBehavior::Renderer::Model* model = (MonoBehavior::Renderer::Model*)p_gameObject->components[i];
						selectedObjectFields = model->staticGetArchetype().getFieldsByPredicate([](rfk::Field const&, void*) { return true; }, model, true, true);
						CheckFieldType(selectedObjectFields, model);
						ImGui::Unindent();
				}
				break;
			}
			case MonoBehavior::COMPONENT_TYPE::CANVA:
			{
				if (ImGui::CollapsingHeader(("Canva##Component" + std::to_string(i)).c_str()))
				{
					ImGui::Indent();
					MonoBehavior::Canva* canva = (MonoBehavior::Canva*)p_gameObject->components[i];
					selectedObjectFields = canva->staticGetArchetype().getFieldsByPredicate([](rfk::Field const&, void*) { return true; }, canva, true, true);
					CheckFieldType(selectedObjectFields, canva);
					ImGui::Unindent();
				}
				break;
			}
			case MonoBehavior::COMPONENT_TYPE::SCRIPT:
			{
				if (ImGui::CollapsingHeader(("Component " + std::to_string(i) + ": Script").c_str()))
				{
					ImGui::Indent();
					//MonoBehavior::Script::BaseScript* script = (MonoBehavior::Script::BaseScript*)p_gameObject->components[i];
					//selectedObjectFields = script->staticGetArchetype().getFieldsByPredicate([](rfk::Field const&, void*) { return true; }, script, true, true);
					//CheckFieldType(selectedObjectFields, script);
					ImGui::Unindent();
				}
				break;
			}
			default:
				ImGui::Unindent();
				break;
			}
			
		}

	}

	void Inspector::CheckFieldType(rfk::Vector< const rfk::Field*>& p_selectedObjectFields, void * p_instance)
	{
		for (size_t i = 0; i < p_selectedObjectFields.size(); i++)
		{   
			const rfk::Archetype* tempArch = p_selectedObjectFields[i]->getType().getArchetype();
			if (p_selectedObjectFields[i]->hasSameName("text"))
			{
				std::string* tempString = (std::string*)p_selectedObjectFields[i]->getPtrUnsafe(p_instance);
				char* resourcesAvailables = (char*)tempString->c_str();
				ImGui::InputText(p_selectedObjectFields[i]->getName(), (char*)resourcesAvailables, 200 * sizeof(char*), NULL, NULL);
				p_selectedObjectFields[i]->setUnsafe(&p_instance, (std::string*)resourcesAvailables);
			}
			else if (p_selectedObjectFields[i]->hasSameName("alignment"))
			{
				MonoBehavior::Physics::CapsuleCollider* col = static_cast<MonoBehavior::Physics::CapsuleCollider*>(p_instance);
				int aligment = static_cast<int>(col->GetAlignment());
				if (ImGui::Combo("Axis alignmenent", &aligment, "X\0Y\0Z\0\0"))
				{
					col->SetAlignment(aligment);
				}
			}
			else if (tempArch->hasSameName("bool"))
			{
				bool* tempBool = (bool*)p_selectedObjectFields[i]->getPtrUnsafe(p_instance);
				if (p_selectedObjectFields[i]->hasSameName("isStatic"))
				{
					MonoBehavior::Physics::Collider* col = static_cast<MonoBehavior::Physics::Collider*>(p_instance);
					if (col->componentType != MonoBehavior::PLANE_COLLIDER && ImGui::Checkbox(p_selectedObjectFields[i]->getName(), tempBool))
					{
							col->ToggleStatic();
					}
					continue;
				}
				if (p_selectedObjectFields[i]->hasSameName("isTrigger"))
				{
					MonoBehavior::Physics::Collider* col = static_cast<MonoBehavior::Physics::Collider*>(p_instance);
					if (col->componentType != MonoBehavior::PLANE_COLLIDER && ImGui::Checkbox(p_selectedObjectFields[i]->getName(), tempBool))
					{
						col->ToggleTrigger();
					}
					continue;
				}
				if (p_selectedObjectFields[i]->hasSameName("queryable"))
				{
					if (ImGui::Checkbox(p_selectedObjectFields[i]->getName(), tempBool))
					{
						MonoBehavior::Physics::Collider* col = static_cast<MonoBehavior::Physics::Collider*>(p_instance);
						col->ToggleQueryable();
					}
					continue;
				}
				if (p_selectedObjectFields[i]->hasSameName("lockPosX") || p_selectedObjectFields[i]->hasSameName("lockPosY") || p_selectedObjectFields[i]->hasSameName("lockPosZ") || p_selectedObjectFields[i]->hasSameName("lockRotX") || p_selectedObjectFields[i]->hasSameName("lockRotY") || p_selectedObjectFields[i]->hasSameName("lockRotZ"))
				{
					MonoBehavior::Physics::Collider* col = static_cast<MonoBehavior::Physics::Collider*>(p_instance);
					if (col->IsStatic())
					{
						continue;
					}
				}
				ImGui::Checkbox(p_selectedObjectFields[i]->getName(), tempBool);
				p_selectedObjectFields[i]->setUnsafe(&p_instance, tempBool);
			}
			else if (tempArch->hasSameName("Vector4"))
			{
				Math::Vector4* tempVec4 = (Math::Vector4*)p_selectedObjectFields[i]->getPtrUnsafe(p_instance);
				if (ImGui::ColorEdit4(p_selectedObjectFields[i]->getName(), &tempVec4->x, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel))
				{
					p_selectedObjectFields[i]->setUnsafe(&p_instance, tempVec4);
				}
			}
			else if (tempArch->hasSameName("float"))
			{
				float* tempFloat = (float*)p_selectedObjectFields[i]->getPtrUnsafe(p_instance);
				
				if(p_selectedObjectFields[i]->hasSameName("halfHeight"))
				{
					if (ImGui::SliderFloat(p_selectedObjectFields[i]->getName(), tempFloat, 0.f, 10.f, "%.3f"))
					{
						MonoBehavior::Physics::CapsuleCollider* col = static_cast<MonoBehavior::Physics::CapsuleCollider*>(p_instance);
						col->SetHalfHeight();
					}
					continue;
				}
				if (p_selectedObjectFields[i]->hasSameName("radius"))
				{
					if (ImGui::SliderFloat(p_selectedObjectFields[i]->getName(), tempFloat, 0.1f, 10.f, "%.3f"))
					{
						MonoBehavior::Physics::Collider* col = static_cast<MonoBehavior::Physics::Collider*>(p_instance);
						if (col->componentType == MonoBehavior::COMPONENT_TYPE::SPHERE_COLLIDER)
						{
							MonoBehavior::Physics::SphereCollider* sCol = static_cast<MonoBehavior::Physics::SphereCollider*>(p_instance);
							sCol->SetRadius();

						}
						else if (col->componentType == MonoBehavior::COMPONENT_TYPE::CAPSULE_COLLIDER)
						{
							MonoBehavior::Physics::CapsuleCollider* cCol = static_cast<MonoBehavior::Physics::CapsuleCollider*>(p_instance);
							cCol->SetRadius();
						}
					}
					continue;
				}
				ImGui::InputFloat(p_selectedObjectFields[i]->getName(), tempFloat, -1.f, 90.f, "%.3f");
				p_selectedObjectFields[i]->setUnsafe(&p_instance, tempFloat);
			}
			else if (tempArch->hasSameName("int"))
			{
				int* tempInt = (int*)p_selectedObjectFields[i]->getPtrUnsafe(p_instance);
				if (ImGui::SliderInt(p_selectedObjectFields[i]->getName(), tempInt, -10, 10))
				{
					p_selectedObjectFields[i]->setUnsafe(&p_instance, tempInt);
				}
			}
			else if (tempArch->hasSameName("Vector2"))
			{
				Math::Vector2* tempVec2 = (Math::Vector2*)p_selectedObjectFields[i]->getPtrUnsafe(p_instance);
				if (ImGui::InputFloat2(p_selectedObjectFields[i]->getName(), &tempVec2->x, "%.3f"))
				{
					p_selectedObjectFields[i]->setUnsafe(&p_instance, tempVec2);
				}
			}
			else if (tempArch->hasSameName("Vector3"))
			{
				Math::Vector3* tempVec3 = (Math::Vector3*)p_selectedObjectFields[i]->getPtrUnsafe(p_instance);
				if (p_selectedObjectFields[i]->hasSameName("offset"))
				{
					MonoBehavior::Physics::Collider* col = static_cast<MonoBehavior::Physics::Collider*>(p_instance);
					if (col->componentType == MonoBehavior::PLANE_COLLIDER)
					{
						continue;
					}
					ImGui::SliderFloat3(p_selectedObjectFields[i]->getName(), &tempVec3->x, -10.f, 10.f, "%.3f");
					continue;
				}
				if (p_selectedObjectFields[i]->hasSameName("scale"))
				{
					MonoBehavior::Physics::BoxCollider* col = static_cast<MonoBehavior::Physics::BoxCollider*>(p_instance);
					if (ImGui::SliderFloat3(p_selectedObjectFields[i]->getName(), &tempVec3->x, 0.1f, 10.f, "%.3f"))
					{
						col->SetScale();
					}
					continue;
				}
				if (ImGui::SliderFloat3(p_selectedObjectFields[i]->getName(), &tempVec3->x, -1.f, 1.f, "%.3f"))
				{
					p_selectedObjectFields[i]->setUnsafe(&p_instance, tempVec3);
				}
			}
			else if (tempArch->hasSameName("string"))
			{
				std::string* tempString = (std::string*)p_selectedObjectFields[i]->getPtrUnsafe(p_instance);
				ImGui::InputText(p_selectedObjectFields[i]->getName(), (char*)tempString, IM_ARRAYSIZE(tempString));
				p_selectedObjectFields[i]->setUnsafe(&p_instance, tempString);
			}
			else if (tempArch->getKind() == rfk::EEntityKind::Class)
			{
				if (tempArch->hasSameName("Texture") && p_selectedObjectFields[i]->getPtrUnsafe(p_instance) != nullptr)
				{
					if (ImGui::CollapsingHeader(("Texture " + std::to_string(i)).c_str()))
					{
						std::string* resourcesAvailables = GetResources("Resources/Textures");
						Resource::Texture** texture1 = (Resource::Texture**)p_selectedObjectFields[i]->getPtrUnsafe(p_instance);
						Resource::Texture* texture = *texture1;
						if (texture == nullptr)
						{
							ImGui::Text("No texture (FBX)");
							break;
						}
						subSelectedObjectField = texture->staticGetArchetype().getFieldsByPredicate([](rfk::Field const&, void*) { return true; }, texture, true, true);
						GetResourcesInfo(resourcesAvailables, texture);
						if (ValueChanged)
						{
							size_t index_of_slash = ValueChanged->find_last_of("/\\");
							std::string file_name = ValueChanged->substr(index_of_slash + 1);
							size_t index_of_period = file_name.find_last_of('.');
							std::string file_without_extension = file_name.substr(0, index_of_period);
							texture = Core::ResourceManager::Get()->UseTexture("Resources/Textures/" + file_name);
							*texture1 = texture;
							p_selectedObjectFields[i]->setUnsafe(&p_instance, texture1);
							ValueChanged = nullptr;
						}
					}
				}
				else if (tempArch->hasSameName("Shader") && p_selectedObjectFields[i]->getPtrUnsafe(p_instance) != nullptr)
				{
					if (ImGui::CollapsingHeader(("Shader " + std::to_string(i)).c_str()))
					{
						std::string* resourcesAvailables = GetResources("Resources/Shaders");
						Resource::Shader** shader1 = (Resource::Shader**)p_selectedObjectFields[i]->getPtrUnsafe(p_instance);
						Resource::Shader* shader = *shader1;
						subSelectedObjectField = shader->staticGetArchetype().getFieldsByPredicate([](rfk::Field const&, void*) { return true; }, shader, true, true);

						 GetResourcesInfo(resourcesAvailables, shader);

						 if (ValueChanged)
						 {
							 size_t index_of_slash = ValueChanged->find_last_of("/\\");
							 std::string file_name = ValueChanged->substr(index_of_slash + 1);
							 size_t index_of_period = file_name.find_last_of('.');
							 std::string file_without_extension = file_name.substr(0, index_of_period);
							 shader = Core::ResourceManager::Get()->UseShader("Resources/Shaders/" + file_without_extension + ".vert", "Resources/Shaders/" + file_without_extension + ".frag");
							 *shader1 = shader;
							 p_selectedObjectFields[i]->setUnsafe(&p_instance, shader1);
							 ValueChanged = nullptr;
						 }
						
					}
				}
				else if (tempArch->hasSameName("Mesh") && p_selectedObjectFields[i]->getPtrUnsafe(p_instance) != nullptr)
				{
					if (ImGui::CollapsingHeader(("Mesh " + std::to_string(i)).c_str()))
					{
						std::string* resourcesAvailables = GetResources("Resources/Mesh");
						Resource::Mesh** mesh1 = (Resource::Mesh**)p_selectedObjectFields[i]->getPtrUnsafe(p_instance);
						Resource::Mesh* mesh = *mesh1;
	
						subSelectedObjectField = mesh->staticGetArchetype().getFieldsByPredicate([](rfk::Field const&, void*) { return true; }, mesh, true, true);
						GetResourcesInfo(resourcesAvailables, mesh);
						if (ValueChanged)
						{
							size_t index_of_slash = ValueChanged->find_last_of("/\\");
							std::string file_name = ValueChanged->substr(index_of_slash + 1);
							size_t index_of_period = file_name.find_last_of('.');
							std::string file_without_extension = file_name.substr(0, index_of_period);
							mesh = Core::ResourceManager::Get()->UseMesh("Resources/Mesh/" + file_name);
							*mesh1 = mesh;
							p_selectedObjectFields[i]->setUnsafe(&p_instance, mesh1);
							ValueChanged = nullptr;
						}
					}
				}
				else if (tempArch->hasSameName("Animation") && p_selectedObjectFields[i]->getPtrUnsafe(p_instance) != nullptr)
				{
					if (ImGui::CollapsingHeader(("Animation " + std::to_string(i)).c_str()))
					{		
						DataStructure::Animation::Animation** animation1 = (DataStructure::Animation::Animation**)p_selectedObjectFields[i]->getPtrUnsafe(p_instance);
						DataStructure::Animation::Animation* animation = *animation1;
						subSelectedObjectField = animation->staticGetArchetype().getFieldsByPredicate([](rfk::Field const&, void*) { return true; }, animation, true, true);

						for (size_t i = 0; i < subSelectedObjectField.size(); i++)
						{
							if (subSelectedObjectField[i]->hasSameName("path"))
							{
								std::string* tempString = (std::string*)subSelectedObjectField[i]->getPtrUnsafe(animation);
								ImGui::Text(tempString->c_str());
							}
						}
					}

				}
				else if (tempArch->hasSameName("Sound") && p_selectedObjectFields[i]->getPtrUnsafe(p_instance) != nullptr)
				{
					if (ImGui::CollapsingHeader(("Sound " + std::to_string(i)).c_str()))
					{
						std::string* resourcesAvailables = GetResources("Resources/Sounds");
						Resource::Sound** sound1 = (Resource::Sound**)p_selectedObjectFields[i]->getPtrUnsafe(p_instance);
						Resource::Sound* sound = *sound1;
						subSelectedObjectField = sound->staticGetArchetype().getFieldsByPredicate([](rfk::Field const&, void*) { return true; }, sound, true, true);

						GetResourcesInfo(resourcesAvailables, sound);
						if (ValueChanged)
						{
							size_t index_of_slash = ValueChanged->find_last_of("/\\");
							std::string file_name = ValueChanged->substr(index_of_slash + 1);
							size_t index_of_period = file_name.find_last_of('.');
							std::string file_without_extension = file_name.substr(0, index_of_period);
							sound = Core::ResourceManager::Get()->UseSound("Resources/Sounds/" + file_name);
							*sound1 = sound;
							p_selectedObjectFields[i]->setUnsafe(&p_instance, sound1);
							ValueChanged = nullptr;
						}
					}
				}
			}
		}
	}

	void Inspector::DrawName(DataStructure::GameObject* p_gameObjectSelected)
	{
		static char newName[64];
		memset(newName, 0, sizeof(newName));
		size_t lenghtName = std::strlen((p_gameObjectSelected->GetName()).c_str());
		std::copy_n(p_gameObjectSelected->GetName().c_str(), lenghtName, newName);
		ImGui::InputText("Name", newName, IM_ARRAYSIZE(newName));
		
		if (std::strlen(newName) != 0) // Check if name is not equal to ""
		{
			p_gameObjectSelected->SetName(newName);
		}
	}

	void Inspector::DrawTransform(DataStructure::GameObject* p_gameObjectSelected, MonoBehavior::Physics::Collider* p_colliderSelected)
	{
		if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(1.f, 0.f, 0.f, 0.25f));  
			ImGui::InputFloat3("Position", &UIposition.x);
			ImGui::PopStyleColor(1);

			if (ImGui::IsItemActive())
			{
				p_gameObjectSelected->transform.SetPosition(UIposition, true);
				if (p_colliderSelected)
				{
					p_colliderSelected->SetModified();
				}
			}
			else
			{
				UIposition = p_gameObjectSelected->transform.GetLocalPosition();
			}

			ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.f, 0.f, 1.f, 0.25f));  
			ImGui::InputFloat3("Rotation", &UIrotation.x);
			ImGui::PopStyleColor(1);

			if (ImGui::IsItemActive())
			{
				p_gameObjectSelected->transform.SetRotation(Math::Quaternion::QuatFromEuler(UIrotation));
				if (p_colliderSelected)
				{
					p_colliderSelected->SetModified();
				}
			}
			else
			{
				UIrotation = p_gameObjectSelected->transform.GetLocalRotation().QuatToEuler();
			}
			ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.f, 1.f, 0.f, 0.25f)); 
			ImGui::InputFloat3("Scale", &UIscale.x);
			ImGui::PopStyleColor(1);

			if (ImGui::IsItemActive())
			{
				p_gameObjectSelected->transform.SetScale(UIscale);
			}
			else
			{
				UIscale = p_gameObjectSelected->transform.GetLocalScale();
			}

		}
	}

	void Inspector::AddComponentButton(DataStructure::GameObject* p_gameObjectSelected, Core::Scene* p_scene)
	{
		if (ImGui::Button("Add Component"))
		{
			ImGui::OpenPopup("Component");
		}
		if (ImGui::BeginPopup("Component"))
		{
			const char* items[] = 
			{
				"Point light", "Spot Light", "Directional Light", 
				"Capsule Collider", "Sphere Collider", "Box Collider", "Plane Collider", "AudioSource", 
				"Animator", "Canva","Model", "Script"
			};

			if (ImGui::ListBox("Component Type", &item_current, items, IM_ARRAYSIZE(items), 3))
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

			ImGui::Text("Selected type");
			ImGui::TextWrapped(items[item_current]);

			if (ImGui::Button("Add Component"))
			{		
				switch (item_current)
				{
				case 0:
				{
					MonoBehavior::Renderer::PointLight* tempPoint = dynamic_cast<MonoBehavior::Renderer::PointLight *>(p_gameObjectSelected->CreateComponent(item_current));
					tempPoint->Start(&p_scene->GetGameState());
					p_scene->AddLight(p_gameObjectSelected, tempPoint);
					ImGui::CloseCurrentPopup();
					break;
				}
				case 1:
				{
					MonoBehavior::Renderer::SpotLight* tempSpot = dynamic_cast<MonoBehavior::Renderer::SpotLight*>(p_gameObjectSelected->CreateComponent(item_current));
					tempSpot->Start(&p_scene->GetGameState());
					p_scene->AddLight(p_gameObjectSelected, tempSpot);
					ImGui::CloseCurrentPopup();
					break;
				}
				case 2:
				{
					MonoBehavior::Renderer::DirectionalLight* tempDir = dynamic_cast<MonoBehavior::Renderer::DirectionalLight*>(p_gameObjectSelected->CreateComponent(item_current));
					tempDir->Start(&p_scene->GetGameState());
					p_scene->AddLight(p_gameObjectSelected, tempDir);
					ImGui::CloseCurrentPopup();
					break;
				}
				case 3:
				{
					MonoBehavior::Physics::CapsuleCollider* tempCaps = dynamic_cast<MonoBehavior::Physics::CapsuleCollider*>(p_gameObjectSelected->CreateComponent(item_current));
					tempCaps->Start(&p_scene->GetGameState());
					p_gameObjectSelected->AddComponent(tempCaps);
					ImGui::CloseCurrentPopup();
					break;
				}
				case 4:
				{
					MonoBehavior::Physics::SphereCollider* tempSphere = dynamic_cast<MonoBehavior::Physics::SphereCollider*>(p_gameObjectSelected->CreateComponent(item_current));
					tempSphere->Start(&p_scene->GetGameState());
					p_gameObjectSelected->AddComponent(tempSphere);
					ImGui::CloseCurrentPopup();
					break;
				}
				case 5:
				{
					MonoBehavior::Physics::BoxCollider* tempBox = dynamic_cast<MonoBehavior::Physics::BoxCollider*>(p_gameObjectSelected->CreateComponent(item_current));
					tempBox->Start(&p_scene->GetGameState());
					p_gameObjectSelected->AddComponent(tempBox);
					ImGui::CloseCurrentPopup();
					break;
				}
				case 6:
				{
					MonoBehavior::Physics::PlaneCollider* tempPlane = dynamic_cast<MonoBehavior::Physics::PlaneCollider*>(p_gameObjectSelected->CreateComponent(item_current));
					tempPlane->Start(&p_scene->GetGameState());
					p_gameObjectSelected->AddComponent(tempPlane);
					ImGui::CloseCurrentPopup();
					break;
				}
				case 7:
				{
					MonoBehavior::AudioSource* tempAudio = dynamic_cast<MonoBehavior::AudioSource*>(p_gameObjectSelected->CreateComponent(item_current));
					tempAudio->Start(&p_scene->GetGameState());
					p_gameObjectSelected->AddComponent(tempAudio);
					ImGui::CloseCurrentPopup();
					break;
				}
				case 8:
				{
					MonoBehavior::Animator* tempAnim = dynamic_cast<MonoBehavior::Animator*>(p_gameObjectSelected->CreateComponent(item_current));
					tempAnim->Start(&p_scene->GetGameState());
					p_gameObjectSelected->AddComponent(tempAnim);
					ImGui::CloseCurrentPopup();
					break;
				}
				case 9:
				{
					MonoBehavior::Canva* tempCanva = dynamic_cast<MonoBehavior::Canva*>(p_gameObjectSelected->CreateComponent(item_current));
					tempCanva->Start(&p_scene->GetGameState());
					p_gameObjectSelected->AddComponent(tempCanva);
					ImGui::CloseCurrentPopup();
					break;
				}
				case 10:
				{
					MonoBehavior::Renderer::Model* temModel = dynamic_cast<MonoBehavior::Renderer::Model*>(p_gameObjectSelected->CreateComponent(item_current));
					temModel->Start(&p_scene->GetGameState());
					p_gameObjectSelected->AddComponent(temModel);
					ImGui::CloseCurrentPopup();
					break;
				}
				case 11:
				{
					//TODO Script
					ImGui::CloseCurrentPopup();
					break;
				}
				default:
					break;
				}
			}

			if (ImGui::Button("Cancel"))
			{
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
	}

	void Inspector::DrawResources(std::string* p_resources,int p_index)
	{
		if (ImGui::Button(("Change " + std::to_string(p_index)).c_str()))
		{
			ImGui::OpenPopup("Resources"+ p_index);
		}
		if (ImGui::BeginPopup("Resources" + p_index))
		{
			static int item_current_idx = 0;
			if (ImGui::BeginListBox("Resources" + p_index))
			{
				for (int n = 0; n < sizeof(p_resources); n++)
				{
					const bool is_selected = (item_current_idx == n);
					if (ImGui::Selectable(p_resources[n].c_str(), is_selected))
					{
						item_current_idx = n;
					}

					// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
					if (is_selected)
					{
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndListBox();
			}

			ImGui::Text("Selected resources");
			ImGui::TextWrapped(p_resources[item_current_idx].c_str());

			if (ImGui::Button("Cancel"))
			{
				ImGui::CloseCurrentPopup();
			}

			ImGui::SameLine();

			if (ImGui::Button("Valid Change"))
			{
				ValueChanged =  &p_resources[item_current_idx];
				ImGui::CloseCurrentPopup();
			}
			
			ImGui::EndPopup();

		}
	}

	std::string* Inspector::GetResources(const char* p_name)
	{
		std::filesystem::path tempResources;
		std::filesystem::path finalPath = p_name;

		const size_t tempSize = std::distance(std::filesystem::directory_iterator(finalPath), std::filesystem::directory_iterator{});
		std::string* resourcesAvailables = new std::string[tempSize];;

		int indexResources = 0;
		for (const auto& entry : std::filesystem::directory_iterator(finalPath))
		{
			tempResources += entry.path();
			resourcesAvailables[indexResources] = entry.path().string();
			indexResources++;
		}

		return resourcesAvailables;
	}

	void Inspector::GetResourcesInfo(std::string* p_resourcesAvailables, void* p_class)
	{
		for (size_t i = 0; i < subSelectedObjectField.size(); i++)
		{
			std::string* tempString = (std::string*)subSelectedObjectField[i]->getPtrUnsafe(p_class);
			if (subSelectedObjectField[i])
			{
				ImGui::Text(tempString->c_str());
				ImGui::SameLine();
				DrawResources(p_resourcesAvailables, (int)i);
			}

		}
	}

}
