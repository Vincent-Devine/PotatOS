#pragma once

#include <DLLInclude.hpp>

#include <vector>
#include <map>

#include <MonoBehavior/IComponent.hpp>
#include <Math/Mat4.inl>
#include <DataStructure/Animation/AnimData.hpp>
#include <DLLInclude.hpp>
#include <Refureku/Refureku.h>
#include <Refureku/Generated/Animator.rfkh.h>
#include <DataStructure/Animation/Animation.hpp>
//namespace DataStructure RFKNamespace()
//{
//	namespace Animation RFKNamespace()
//	{
//		class Animation;
//	}
//}

namespace MonoBehavior RFKNamespace()
{
	class RFKClass() POTATOS_ENGINE_API Animator : public IComponent
	{
		// Attributes
	private:
		std::vector<Math::Mat4> finalBoneMatrix;

		RFKField()
		DataStructure::Animation::Animation currentAnimation;
		bool hasCurrentAnimation;

		// Next animation
		DataStructure::Animation::Animation nextAnimation;
		bool hasNextAnimation;
		float transitionTime;
		float transitionCountdown;
		float ratioTransition;

		const unsigned int* shaderProgram;
		
		RFKField()
		bool pause;
		float increment;
		float rate;
		float keyFrameNavigation; // Don't use => keyFrameNavigation = -1
		float speed;
		bool loop;
		bool stopLoop;

		// Methods
	public:
		Animator(DataStructure::Animation::Animation* p_animation, const unsigned int* p_shaderProgram);

		void Update(const float p_deltaTime, const Inputs& p_inputs) override;
		void Draw(const MonoBehavior::Renderer::Camera* p_camera, const DataStructure::LightManager& p_lightManager, const MonoBehavior::Renderer::Light * p_light = nullptr) const override;
	
		void StartTransition(DataStructure::Animation::Animation * p_animation, float p_transitionTime);
		void TransitionBetweenAnimation(const float p_deltaTime);
		void FinishTransition();

		const DataStructure::Animation::Animation* GetCurrentAnimation() const { return &currentAnimation; };

		void PlayAnimation(DataStructure::Animation::Animation* p_animation);


		DataStructure::Animation::Animation* GetCurrentAnimation() { return &currentAnimation; };
		void SetSpeed(const float p_speed) { speed = p_speed; };
		void SetLoop(const bool p_loop) { stopLoop = p_loop; };

	private:
		void CalculateBoneTransform(const DataStructure::Animation::NodeData* p_node, const Math::Mat4& p_parentTransform);
	
		MonoBehavior_Animator_GENERATED
	};
}

File_Animator_GENERATED