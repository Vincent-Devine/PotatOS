#pragma once

#include <ImGUI/Include/imgui.h>
#include <DataStructure/GraphScene.hpp>
#include <Core/Scene.hpp>
#include <Math/Vector3.hpp>

namespace MonoBehavior
{
	namespace Physics
	{
		class Collider;
	}
}

namespace UI
{
	class Inspector
	{
		// Attributes
	private:
		rfk::Database const& database = rfk::getDatabase();

		Math::Vector3 UIposition;
		Math::Vector3 UIscale;
		Math::Vector3 UIrotation;

		float selectedFloat;
		rfk::Vector< const rfk::Field *> selectedObjectFields;
		rfk::Vector< const rfk::Field*> subSelectedObjectField;
		rfk::Vector<const rfk::Struct*> componentSubClasses;
		std::vector<std::string*> fieldsNames;
		std::ptrdiff_t temp;

		int item_current = 0;
		MonoBehavior::IComponent tempComp;

		std::filesystem::path pathDir;

		std::string* ValueChanged;
		// Methods
	public:
		void Draw(DataStructure::GraphScene& p_scenegraph, DataStructure::GameObject* p_gameObjectSelected, 
			MonoBehavior::Physics::Collider* p_colliderSelected, Core::Scene* p_scene, std::filesystem::path p_pathDir);

	private:
		void ShowIComponentFields(DataStructure::GameObject* p_gameObject);
		void CheckFieldType(rfk::Vector< const rfk::Field*>& p_selectedObjectFields, void* p_instance);

		void CheckFieldSubType(rfk::Vector<const rfk::Field*>& p_selectedObjectFields, void* p_instance);

		void DrawName(DataStructure::GameObject* p_gameObjectSelected);
		void DrawTransform(DataStructure::GameObject* p_gameObjectSelected, MonoBehavior::Physics::Collider* p_colliderSelected);
		void AddComponentButton(DataStructure::GameObject* p_gameObjectSelected, Core::Scene* p_scene);
		void DrawResources(std::string* p_resources,int p_index);
		std::string* GetResources(const char* p_name);
		void GetResourcesInfo(std::string* p_resourcesAvailables, void* p_class);
	};
}
