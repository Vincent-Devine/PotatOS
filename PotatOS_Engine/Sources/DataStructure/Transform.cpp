#include "pch.h"

#include <DataStructure/Transform.hpp>
#include <DataStructure/GameObject.hpp>

namespace DataStructure
{
	Transform::Transform(const Math::Vector3& p_position, const Math::Quaternion& p_rotation, const Math::Vector3& p_scale)
		: parentTransform(nullptr)
	{
		position = localPosition = p_position;
		rotation = localRotation = p_rotation.Normalize();
		scale = localScale = p_scale;
	}

	Transform::Transform(const Transform& p_transform)
		: parentTransform(p_transform.parentTransform)
		, gameObject(p_transform.gameObject)
	{
		SetPosition(p_transform.GetLocalPosition());
		SetRotation(p_transform.GetLocalRotation());
		SetScale(p_transform.GetLocalScale());
	}

	void Transform::Update()
	{
		position = localPosition;
		scale = localScale;
		rotation = localRotation;

		worldMatrix = Math::Mat4::Identity();

		if (parentTransform)
		{
			scale *= parentTransform->GetScale();
			rotation = parentTransform->GetRotation() * rotation;

			if (!fromEditor)
			{
				worldMatrix = Math::Mat4::CreateTranslationMatrix(parentTransform->GetPosition()) * Math::Quaternion::QuatToMatrix(parentTransform->GetRotation());
			}
			else
			{
				position += parentTransform->GetPosition();
			}
		}

		if (!fromEditor)
		{
			worldMatrix *= Math::Mat4::CreateTranslationMatrix(localPosition) * Math::Quaternion::QuatToMatrix(localRotation) * Math::Mat4::CreateScaleMatrix(scale);

			position = Math::Vector3(worldMatrix.data[0][3], worldMatrix.data[1][3], worldMatrix.data[2][3]);
		}
		else
		{
			worldMatrix = Math::Mat4::CreateTranslationMatrix(position) * Math::Quaternion::QuatToMatrix(rotation) * Math::Mat4::CreateScaleMatrix(scale);
		}

		fromEditor = false;
		isDirty = false;
	}

	void Transform::SetPosition(const Math::Vector3& p_position, const bool p_fromEditor, const bool p_dirty)
	{
		fromEditor = p_fromEditor;
		isDirty = p_dirty;
		localPosition = p_position;
	}

	void Transform::SetRotation(const Math::Quaternion& p_quat, const bool p_dirty)
	{
		isDirty = p_dirty;
		localRotation = p_quat;
	}

	void Transform::SetScale(const Math::Vector3& p_scale, const bool p_dirty)
	{
		isDirty = p_dirty;
		localScale = p_scale;
	}

	Math::Vector3 Transform::Forward()
	{
		return (Math::Quaternion::QuatToMatrix(rotation) * Math::Vector4(0.f, 0.f, 1.f, 0.f)).ToVector3();
	}

	Math::Vector3 Transform::Up()
	{
		return (Math::Quaternion::QuatToMatrix(rotation) * Math::Vector4(0.f, 1.f, 0.f, 0.f)).ToVector3();
	}

	Math::Vector3 Transform::Right()
	{
		return (Math::Quaternion::QuatToMatrix(rotation) * Math::Vector4(1.f, 0.f, 0.f, 0.f)).ToVector3();
	}
}
