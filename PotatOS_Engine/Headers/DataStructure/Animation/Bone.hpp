#pragma once

#include <DLLInclude.hpp>
#include <vector>
#include <Math/Vector3.hpp>
#include <Math/Quaternion.inl>
#include <Math/Mat4.inl>

namespace DataStructure::Animation
{
    struct KeyPosition
    {
        Math::Vector3 position;
        float timeStamp = 0.f;
    };

    struct KeyRotation
    {
        Math::Quaternion orientation;
        float timeStamp = 0.f;
    };

    struct KeyScale
    {
        Math::Vector3 scale;
        float timeStamp = 0.f;
    };

    struct BoneData
    {
        std::vector<KeyPosition> positions;
        std::vector<KeyRotation> rotations;
        std::vector<KeyScale> scales;
        int numPositions = 0;
        int numRotations = 0;
        int numScalings = 0;
    };

    class POTATOS_ENGINE_API Bone
    {
        // Attributes
    private:
        std::vector<KeyPosition> positions;
        std::vector<KeyRotation> rotations;
        std::vector<KeyScale> scales;
        int numPositions;
        int numRotations;
        int numScalings;

        Math::Mat4 localTransform;
        std::string name;
        int ID;

        // Methods
    public:
        Bone(const std::string& p_name, int p_ID, const BoneData& p_boneData);

        void Update(const float p_animationTime);

        const Math::Mat4& GetLocalTransform() const { return localTransform; };
        const std::string& GetName() const { return name; };

        const int GetPositionIndex(float p_animationTime) const;
        const int GetRotationIndex(float p_animationTime) const;
        const int GetScalIndex(float p_animationTime) const;

        Math::Vector3 InterpolatePosition(const float p_animationTime);
        Math::Quaternion InterpolateRotation(const float p_animationTime);
        Math::Vector3 InterpolateScaling(const float p_animationTime);

    private:
        float GetScaleFactor(const float p_lastTimeStamp, const float p_nextTimeStamp, const float p_animationTime);
    };
}
