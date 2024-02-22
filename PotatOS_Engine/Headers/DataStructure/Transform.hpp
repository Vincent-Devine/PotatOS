#pragma once

#include <DLLInclude.hpp>
#include <Math/Vector3.hpp>
#include <Math/Quaternion.inl>
#include <Math/Mat4.inl>
#include <vector>

namespace DataStructure
{
	class GameObject;

	class POTATOS_ENGINE_API Transform
	{
	// Attributes
	public:
		GameObject* gameObject;
		Transform* parentTransform;
		std::vector<Transform*> children;

	private:
		Math::Vector3 position;
		Math::Quaternion rotation;
		Math::Vector3 scale;
		Math::Vector3 localPosition;
		Math::Quaternion localRotation;
		Math::Vector3 localScale;
		Math::Mat4 worldMatrix = Math::Mat4::Identity();
		bool isDirty = true;
		bool fromEditor = false;

	// Methods
	public:
		Transform(
			const Math::Vector3& p_position = Math::Vector3(),
			const Math::Quaternion& p_rotation = Math::Quaternion(),
			const Math::Vector3& p_scale = Math::Vector3(1.f, 1.f, 1.f)
		);

		Transform(const Transform& p_transform);

		void Update();

		Math::Mat4 GetWorldMatrix() const			{ return worldMatrix; };
		Math::Vector3 GetPosition()	const			{ return position; };
		Math::Quaternion GetRotation() const		{ return rotation; };
		Math::Vector3 GetScale() const				{ return scale; };
		Math::Vector3 GetLocalPosition() const		{ return localPosition; };
		Math::Quaternion GetLocalRotation() const	{ return localRotation; };
		Math::Vector3 GetLocalScale() const			{ return localScale; };
		bool IsDirty() const						{ return isDirty; }
		void SetDirty()								{ isDirty = true; };
		void SetWorldMatrix(const Math::Mat4& p_worldMat) { worldMatrix = p_worldMat; };
		void SetPosition(const Math::Vector3& p_position, const bool p_fromEditor = false, const bool p_dirty = true);
		void SetRotation(const Math::Quaternion& p_quat, const bool p_dirty = true);
		void SetScale(const Math::Vector3& p_scale, const bool p_dirty = true);
		Math::Vector3 Forward();
		Math::Vector3 Up();
		Math::Vector3 Right();
	};
}
