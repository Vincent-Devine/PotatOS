#include "pch.h"
#include <MonoBehavior/Animator.hpp>

#include <DataStructure/Animation/Animation.hpp>
#include <Wrapper/RHI.hpp>
#include <Core/AnimationManager.hpp>
#include <Core/ResourceManager.hpp>

namespace MonoBehavior
{
	Animator::Animator(DataStructure::Animation::Animation* p_animation, const unsigned int* p_shaderProgram)
		: shaderProgram(p_shaderProgram)
		, pause(false)
		, increment(0.f)
		, rate(60.f)
		, keyFrameNavigation(-1.f)
		, speed(1.f)
		, loop(true)
		, stopLoop(false)
	{
		if (p_animation)
		{
			currentAnimation = *p_animation;
		}
		hasCurrentAnimation = true;

		componentType = ANIMATOR;
		finalBoneMatrix.reserve(200);
		for (unsigned int i = 0; i < 200; i++)
		{
			finalBoneMatrix.push_back(Math::Mat4::Identity());
		}
	}

	void Animator::Update(const float p_deltaTime, const Inputs& p_inputs)
	{
		if (*gameState == GAMESTATE::PLAY && hasCurrentAnimation && pause && loop)
		{	
			if (keyFrameNavigation > 0.f)
			{
				currentAnimation.SetCurrentTime(keyFrameNavigation);
			}
			else
			{
				float inverse = 1 / rate;
				if (increment < inverse)
				{
					increment += p_deltaTime * speed;
					return;
				}
				increment = 0.f;
			}
			
			if (hasNextAnimation)
			{
				TransitionBetweenAnimation(p_deltaTime * speed);
			}
			else
			{
				bool newAnimation = currentAnimation.UpdateTime(p_deltaTime * speed);
				if (stopLoop && newAnimation)
				{
					loop = false;
				}
			}
			CalculateBoneTransform(&currentAnimation.GetRootNode(), Math::Mat4::Identity());
		}
		else
		{
			if (!stopLoop)
			{
				loop = true;
			}
		}

		pause = p_inputs.pauseAnimation;
	}

	void Animator::Draw(const MonoBehavior::Renderer::Camera* p_camera, const DataStructure::LightManager& p_lightManager, const MonoBehavior::Renderer::Light* p_light) const
	{
		if (hasCurrentAnimation)
		{
			unsigned int shader = *shaderProgram;
			if (p_light)
			{
				shader = *p_light->GetShadowShader()->GetShaderProgram();
				p_light->GetShadowShader()->Use();
			}
			else
			{
				Core::ResourceManager::Get()->UseShader("Resources/Shaders/Animation.vert", "Resources/Shaders/ShadowedBlinnPhong.frag")->Use();
			}
			for (unsigned int i = 0; i < finalBoneMatrix.size(); i++)
			{
				Wrapper::RHI::SetMat4Shader(shader, "gBones[" + std::to_string(i) + "]", finalBoneMatrix[i]);
			}
		}
	}

	void Animator::StartTransition(DataStructure::Animation::Animation* p_animation, float p_transitionTime)
	{
		nextAnimation = *p_animation;
		hasNextAnimation = true;
		transitionTime = p_transitionTime;
		transitionCountdown = 0.f;
		currentAnimation.SetCurrentTime(0.f);
		nextAnimation.SetCurrentTime(0.f);
	}

	void Animator::TransitionBetweenAnimation(const float p_deltaTime)
	{
		ratioTransition = transitionCountdown / transitionTime;
		double multiplier = static_cast<double>(nextAnimation.GetDuration()) / static_cast<double>(currentAnimation.GetDuration());

		const double timeScale = Math::lerp(multiplier, 1.0, ratioTransition);
		const double timeScale2 = Math::lerp(1.0, 1.0 / multiplier, ratioTransition);

		currentAnimation.UpdateTime(static_cast<float>(timeScale2 * p_deltaTime));
		nextAnimation.UpdateTime(static_cast<float>(timeScale * p_deltaTime));

		transitionCountdown += p_deltaTime;

		if (transitionCountdown < transitionTime)
		{
			return;
		}

		FinishTransition();
	}

	void Animator::FinishTransition()
	{
		currentAnimation = nextAnimation;
		hasNextAnimation = false;
	}

	void Animator::PlayAnimation(DataStructure::Animation::Animation* p_animation)
	{
		currentAnimation = *p_animation;
		currentAnimation.SetCurrentTime(0.f);
	}

	void Animator::CalculateBoneTransform(const DataStructure::Animation::NodeData* p_node, const Math::Mat4& p_parentTransform)
	{
		std::string nodeName = p_node->name;
		Math::Mat4 nodeTransform = p_node->transformation;

		DataStructure::Animation::Bone* Bone = currentAnimation.FindBone(nodeName);

		if (Bone)
		{
			if (!hasNextAnimation)
			{
				Bone->Update(currentAnimation.GetCurrentTimeAnimation());
				nodeTransform = Bone->GetLocalTransform();
			}
			else
			{
				Math::Vector3 posCurrentAnim, posNextAnim, scaleCurrentAnim, scaleNextAnim;
				Math::Quaternion rotCurrentAnim, rotNextAnim;

				posCurrentAnim = Bone->InterpolatePosition(currentAnimation.GetCurrentTimeAnimation());
				rotCurrentAnim = Bone->InterpolateRotation(currentAnimation.GetCurrentTimeAnimation());
				scaleCurrentAnim = Bone->InterpolateScaling(currentAnimation.GetCurrentTimeAnimation());

				DataStructure::Animation::Bone* boneNextAnim = nextAnimation.FindBone(nodeName);
				if (boneNextAnim)
				{
					posNextAnim = boneNextAnim->InterpolatePosition(nextAnimation.GetCurrentTimeAnimation());
					rotNextAnim = boneNextAnim->InterpolateRotation(nextAnimation.GetCurrentTimeAnimation());
					scaleNextAnim = boneNextAnim->InterpolateScaling(nextAnimation.GetCurrentTimeAnimation());

					Math::Vector3 finalPos = Math::lerp(posCurrentAnim, posNextAnim, ratioTransition);
					Math::Quaternion finalRot = Math::Quaternion::Slerp(rotCurrentAnim, rotNextAnim, ratioTransition);
					Math::Vector3 finalScale = Math::lerp(scaleCurrentAnim, scaleNextAnim, ratioTransition);

					nodeTransform = Math::Mat4::CreateTransformationMatrix(finalPos, finalScale, finalRot);
					//nodeTransform = Math::Mat4::CreateTranslationMatrix(finalPos) * Math::Quaternion::QuatToMatrix(finalRot) * Math::Mat4::CreateScaleMatrix(finalScale);
				}
				else
				{
					Log::Print("Next animation don't have same bone as current animation", LOG_LEVEL_TYPE::Warning);
				}
			}
		}

		Math::Mat4 globalTransformation = p_parentTransform * nodeTransform;

		const std::map<std::string, DataStructure::Animation::BoneInfo>& boneInfoMap = currentAnimation.GetBoneInfos();
		if (boneInfoMap.find(nodeName) != boneInfoMap.end())
		{
			int index = boneInfoMap.at(nodeName).id;
			Math::Mat4 offset = boneInfoMap.at(nodeName).offset;
			finalBoneMatrix[index] = globalTransformation * offset;
		}

		for (int i = 0; i < p_node->childrenCount; i++)
		{
			CalculateBoneTransform(&p_node->children[i], globalTransformation);
		}
	}
}
