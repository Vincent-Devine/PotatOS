#include "pch.h"
#include <DataStructure/Animation/Bone.hpp>
#include <DebugSystem/Assertion.hpp>

namespace DataStructure::Animation
{
	Bone::Bone(const std::string& p_name, int p_ID, const BoneData& p_boneData)
		: name(p_name)
		, ID(p_ID)
		, localTransform(Math::Mat4::Identity())
	{
        numPositions = p_boneData.numPositions;
        numRotations = p_boneData.numRotations;
        numScalings = p_boneData.numScalings;
        positions = p_boneData.positions;
        rotations = p_boneData.rotations;
        scales = p_boneData.scales;
	}

    void Bone::Update(const float p_animationTime)
    {
        Math::Mat4 translation = Math::Mat4::CreateTranslationMatrix(InterpolatePosition(p_animationTime));
        Math::Mat4 rotation = Math::Quaternion::QuatToMatrix(InterpolateRotation(p_animationTime));
        Math::Mat4 scale = Math::Mat4::CreateScaleMatrix(InterpolateScaling(p_animationTime));
        localTransform = translation * rotation * scale;
    }

    const int Bone::GetPositionIndex(float p_animationTime) const
    {
        for (int i = 0; i < numPositions - 1; ++i)
        {
            if (p_animationTime < positions[i + 1].timeStamp)
            {
                return i;
            }
        }
        Assertion(0, "Invalid animation time")
    }

    const int Bone::GetRotationIndex(float p_animationTime) const
    {
        for (int i = 0; i < numRotations - 1; ++i)
        {
            if (p_animationTime < rotations[i + 1].timeStamp)
            {
                return i;
            }
        }
        Assertion(0, "Invalid animation time")
    }

    const int Bone::GetScalIndex(float p_animationTime) const
    {
        for (int i = 0; i < numScalings - 1; ++i)
        {
            if (p_animationTime < scales[i + 1].timeStamp)
            {
                return i;
            }
        }
        Assertion(0, "Invalid animation time")
    }

    Math::Vector3 Bone::InterpolatePosition(const float p_animationTime)
    {
        if (numPositions == 1)
        {
            return positions[0].position;
        }

        unsigned int p0Index = GetPositionIndex(p_animationTime);
        unsigned int p1Index = p0Index + 1;

        float scaleFactor = GetScaleFactor(
            positions[p0Index].timeStamp,
            positions[p1Index].timeStamp,
            p_animationTime
        );

        Math::Vector3 finalPosition = Math::lerp(
            positions[p0Index].position,
            positions[p1Index].position,
            scaleFactor
        );

        return finalPosition;
    }

    Math::Quaternion Bone::InterpolateRotation(const float p_animationTime)
    {
        if (numRotations == 1)
        {
            Math::Quaternion rotation = rotations[0].orientation.Normalize();
            return rotation;
        }

        unsigned int p0Index = GetRotationIndex(p_animationTime);
        unsigned int p1Index = p0Index + 1;

        float scaleFactor = GetScaleFactor(
            rotations[p0Index].timeStamp,
            rotations[p1Index].timeStamp,
            p_animationTime
        );

        Math::Quaternion finalRotation = Math::Quaternion::Slerp(
            rotations[p0Index].orientation,
            rotations[p1Index].orientation,
            scaleFactor
        );

        finalRotation = finalRotation.Normalize();
        return finalRotation;
    }

    Math::Vector3 Bone::InterpolateScaling(const float p_animationTime)
    {
        if (numScalings == 1)
        {
            return scales[0].scale;
        }

        unsigned int p0Index = GetScalIndex(p_animationTime);
        unsigned int p1Index = p0Index + 1;

        float scaleFactor = GetScaleFactor(
            scales[p0Index].timeStamp,
            scales[p1Index].timeStamp,
            p_animationTime
        );

        Math::Vector3 finalScale = Math::lerp(
            scales[p0Index].scale,
            scales[p1Index].scale,
            scaleFactor
        );

        return finalScale;
    }

    float Bone::GetScaleFactor(const float p_lastTimeStamp, const float p_nextTimeStamp, const float p_animationTime)
    {
        float scaleFactor = 0.0f;
        float midWayLenght = p_animationTime - p_lastTimeStamp;
        float framesDiff = p_nextTimeStamp - p_lastTimeStamp;
        scaleFactor = midWayLenght / framesDiff;
        return scaleFactor;
    }
}
