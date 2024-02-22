#include "pch.h"
#include <Wrapper/JsonLayer.hpp>

#include <fstream>
#include <nlohmann/json.hpp>
#include <DataStructure/GameObject.hpp>
#include <MonoBehavior/Renderer/Model.hpp>
#include <DataStructure/Animation/Animation.hpp>
#include <MonoBehavior/Animator.hpp>
#include <DebugSystem/Assertion.hpp>
#include <Core/ResourceManager.hpp>
#include <Core/AnimationManager.hpp>
#include <MonoBehavior/Physics/BoxCollider.hpp>
#include <MonoBehavior/Physics/CapsuleCollider.hpp>
#include <MonoBehavior/Physics/PlaneCollider.hpp>
#include <MonoBehavior/Physics/SphereCollider.hpp>
#include <MonoBehavior/AudioSource.hpp>
#include <MonoBehavior/RandomRotation.hpp>
#include <MonoBehavior/MoveCamera.hpp>
#include <MonoBehavior/Canva.hpp>
#include <MonoBehavior/BobScript.hpp>
#include <MonoBehavior/TransitionScript.hpp>
#include <MonoBehavior/PlayerAttack.hpp>
#include <MonoBehavior/Scripts/PlaySoundScript.hpp>
#include <MonoBehavior/LifeScript.hpp>
#include <MonoBehavior/ColliderPlayerAttack.hpp>
#include <MonoBehavior/Scripts/MenuScript.hpp>
#include <Wrapper/Window.hpp>
#include <MonoBehavior/Scripts/Jump.hpp>
#include <MonoBehavior/Scripts/PlayThemeScript.hpp>
#include <MonoBehavior/SoundAsset.hpp>
#include <MonoBehavior/Scripts/ZombieFollowAttack.hpp>
#include <MonoBehavior/Scripts/LifeDisplay.hpp>
#include <MonoBehavior/Scripts/PlaySoundEnemyScript.hpp>

namespace Wrapper
{
#pragma region UTILITY
	// ---------------------------------------
	//                 Save
	// ---------------------------------------
	void SaveVector2(nlohmann::json& p_file, const Math::Vector2& p_vector2, unsigned int p_index, const std::string& p_localisation, const std::string& p_type)
	{
		p_file["GameObject"][p_index][p_localisation][p_type]["x"] = p_vector2.x;
		p_file["GameObject"][p_index][p_localisation][p_type]["y"] = p_vector2.y;
	}
	
	void SaveVector3(nlohmann::json& p_file, const Math::Vector3& p_vector3, unsigned int p_index, const std::string& p_localisation, const std::string& p_type)
	{
		p_file["GameObject"][p_index][p_localisation][p_type]["x"] = p_vector3.x;
		p_file["GameObject"][p_index][p_localisation][p_type]["y"] = p_vector3.y;
		p_file["GameObject"][p_index][p_localisation][p_type]["z"] = p_vector3.z;
	}

	void SaveVector4(nlohmann::json& p_file, const Math::Vector4& p_vector4, unsigned int p_index, const std::string& p_localisation, const std::string& p_type)
	{
		p_file["GameObject"][p_index][p_localisation][p_type]["x"] = p_vector4.x;
		p_file["GameObject"][p_index][p_localisation][p_type]["y"] = p_vector4.y;
		p_file["GameObject"][p_index][p_localisation][p_type]["z"] = p_vector4.z;
		p_file["GameObject"][p_index][p_localisation][p_type]["w"] = p_vector4.w;
	}

	void SaveQuaternion(nlohmann::json& p_file, const Math::Quaternion& p_quaternion, unsigned int p_index, const std::string& p_localisation, const std::string& p_type)
	{
		p_file["GameObject"][p_index][p_localisation][p_type]["x"] = p_quaternion.x;
		p_file["GameObject"][p_index][p_localisation][p_type]["y"] = p_quaternion.y;
		p_file["GameObject"][p_index][p_localisation][p_type]["z"] = p_quaternion.z;
		p_file["GameObject"][p_index][p_localisation][p_type]["w"] = p_quaternion.w;
	}

	void SaveTransform(nlohmann::json& p_file, const DataStructure::Transform& p_transform, unsigned int p_index)
	{
		SaveVector3(p_file, p_transform.GetLocalPosition(), p_index, "Transform", "Position");
		SaveQuaternion(p_file, p_transform.GetLocalRotation(), p_index, "Transform", "Rotation");
		SaveVector3(p_file, p_transform.GetLocalScale(), p_index, "Transform", "Scale");
	}

	void SaveCamera(nlohmann::json& p_file, const MonoBehavior::Renderer::Camera* p_camera, unsigned int p_index)
	{
		SaveVector3(p_file, p_camera->GetRotation(), p_index, "Camera", "Rotation");
		p_file["GameObject"][p_index]["Camera"]["Speed"] = p_camera->GetFOV();
	}

	void SaveModel(nlohmann::json& p_file, const MonoBehavior::Renderer::Model* p_model, unsigned int p_index)
	{
		p_file["GameObject"][p_index]["Model"]["ShaderVert"] = p_model->GetShader()->GetVertexPath();
		p_file["GameObject"][p_index]["Model"]["ShaderFrag"] = p_model->GetShader()->GetFragmentPath();
		p_file["GameObject"][p_index]["Model"]["Mesh"] = p_model->GetMesh()->GetPath();
		
		if (p_model->GetTexture())
		{
			p_file["GameObject"][p_index]["Model"]["Texture"] = p_model->GetTexture()->GetPath();
		}
		else
		{
			p_file["GameObject"][p_index]["Model"]["Texture"] = nullptr;
		}
	}

	void SaveLight(nlohmann::json& p_file, const MonoBehavior::Renderer::Light* p_light, unsigned int p_index, const std::string& p_localisation)
	{
		SaveVector4(p_file, p_light->GetAmbient(), p_index, p_localisation, "Ambient");
		SaveVector4(p_file, p_light->GetDiffuse(), p_index, p_localisation, "Diffuse");
		SaveVector4(p_file, p_light->GetSpecular(), p_index, p_localisation, "Specular");
	}

	void SaveDirectionalLight(nlohmann::json& p_file, const MonoBehavior::Renderer::DirectionalLight* p_directionalLight, unsigned int p_index)
	{
		SaveVector3(p_file, p_directionalLight->GetDirection(), p_index, "DirectionalLight", "Direction");
		SaveLight(p_file, p_directionalLight, p_index, "DirectionalLight");
	}

	void SaveSpotLight(nlohmann::json& p_file, const MonoBehavior::Renderer::SpotLight* p_spotLight, unsigned int p_index)
	{
		SaveVector3(p_file, p_spotLight->GetDirection(), p_index, "SpotLight", "Direction");
		p_file["GameObject"][p_index]["SpotLight"]["CutOff"] = p_spotLight->GetCutOff();
		p_file["GameObject"][p_index]["SpotLight"]["OuterCutOff"] = p_spotLight->GetOuterCutOff();
		p_file["GameObject"][p_index]["SpotLight"]["Constant"] = p_spotLight->GetConstant();
		p_file["GameObject"][p_index]["SpotLight"]["Linear"] = p_spotLight->GetLinear();
		p_file["GameObject"][p_index]["SpotLight"]["Quadratic"] = p_spotLight->GetQuadratic();
		SaveLight(p_file, p_spotLight, p_index, "SpotLight");
	}

	void SavePointLight(nlohmann::json& p_file, const MonoBehavior::Renderer::PointLight* p_pointLight, unsigned int p_index)
	{
		p_file["GameObject"][p_index]["PointLight"]["Constant"] = p_pointLight->GetConstant();
		p_file["GameObject"][p_index]["PointLight"]["Linear"] = p_pointLight->GetLinear();
		p_file["GameObject"][p_index]["PointLight"]["Quadratic"] = p_pointLight->GetQuadratic();
		SaveLight(p_file, p_pointLight, p_index, "PointLight");
	}

	void SaveAnimator(nlohmann::json& p_file, const MonoBehavior::Animator* p_animator, unsigned int p_index)
	{
		p_file["GameObject"][p_index]["Animator"]["Animation"] = true;
	}

	void SaveBoxCollider(nlohmann::json& p_file, const MonoBehavior::Physics::BoxCollider* p_boxCollider, unsigned int p_index)
	{
		SaveVector3(p_file, p_boxCollider->GetScale(), p_index, "BoxCollider", "Scale");
		p_file["GameObject"][p_index]["BoxCollider"]["IsStatic"] = p_boxCollider->IsStatic();
		p_file["GameObject"][p_index]["BoxCollider"]["IsTrigger"] = p_boxCollider->IsTrigger();
		p_file["GameObject"][p_index]["BoxCollider"]["Queryable"] = p_boxCollider->Queryable();
		p_file["GameObject"][p_index]["BoxCollider"]["LockPosX"] = p_boxCollider->GetLockPosX();
		p_file["GameObject"][p_index]["BoxCollider"]["LockPosY"] = p_boxCollider->GetLockPosY();
		p_file["GameObject"][p_index]["BoxCollider"]["LockPosZ"] = p_boxCollider->GetLockPosZ();
		p_file["GameObject"][p_index]["BoxCollider"]["LockRotX"] = p_boxCollider->GetLockRotX();
		p_file["GameObject"][p_index]["BoxCollider"]["LockRotY"] = p_boxCollider->GetLockRotY();
		p_file["GameObject"][p_index]["BoxCollider"]["LockRotZ"] = p_boxCollider->GetLockRotZ();
		SaveVector3(p_file, p_boxCollider->GetOffset(), p_index, "BoxCollider", "Offset");
	}

	void SaveCapsuleCollider(nlohmann::json& p_file, const MonoBehavior::Physics::CapsuleCollider* p_capsuleCollider, unsigned int p_index)
	{
		p_file["GameObject"][p_index]["CapsuleCollider"]["Radius"] = p_capsuleCollider->GetRadius();
		p_file["GameObject"][p_index]["CapsuleCollider"]["Alignment"] = p_capsuleCollider->GetAlignment();
		p_file["GameObject"][p_index]["CapsuleCollider"]["HalfHeight"] = p_capsuleCollider->GetHalfHeight();
		p_file["GameObject"][p_index]["CapsuleCollider"]["IsStatic"] = p_capsuleCollider->IsStatic();
		p_file["GameObject"][p_index]["CapsuleCollider"]["IsTrigger"] = p_capsuleCollider->IsTrigger();
		p_file["GameObject"][p_index]["CapsuleCollider"]["Queryable"] = p_capsuleCollider->Queryable();
		p_file["GameObject"][p_index]["CapsuleCollider"]["LockPosX"] = p_capsuleCollider->GetLockPosX();
		p_file["GameObject"][p_index]["CapsuleCollider"]["LockPosY"] = p_capsuleCollider->GetLockPosY();
		p_file["GameObject"][p_index]["CapsuleCollider"]["LockPosZ"] = p_capsuleCollider->GetLockPosZ();
		p_file["GameObject"][p_index]["CapsuleCollider"]["LockRotX"] = p_capsuleCollider->GetLockRotX();
		p_file["GameObject"][p_index]["CapsuleCollider"]["LockRotY"] = p_capsuleCollider->GetLockRotY();
		p_file["GameObject"][p_index]["CapsuleCollider"]["LockRotZ"] = p_capsuleCollider->GetLockRotZ();

		SaveVector3(p_file, p_capsuleCollider->GetOffset(), p_index, "CapsuleCollider", "Offset");
	}

	void SaveSphereCollider(nlohmann::json& p_file, const MonoBehavior::Physics::SphereCollider* p_sphereCollider, unsigned int p_index)
	{
		p_file["GameObject"][p_index]["SphereCollider"]["Radius"] = p_sphereCollider->GetRadius();
		p_file["GameObject"][p_index]["SphereCollider"]["IsStatic"] = p_sphereCollider->IsStatic();
		p_file["GameObject"][p_index]["SphereCollider"]["IsTrigger"] = p_sphereCollider->IsTrigger();
		p_file["GameObject"][p_index]["SphereCollider"]["Queryable"] = p_sphereCollider->Queryable();
		p_file["GameObject"][p_index]["SphereCollider"]["LockPosX"] = p_sphereCollider->GetLockPosX();
		p_file["GameObject"][p_index]["SphereCollider"]["LockPosY"] = p_sphereCollider->GetLockPosY();
		p_file["GameObject"][p_index]["SphereCollider"]["LockPosZ"] = p_sphereCollider->GetLockPosZ();
		p_file["GameObject"][p_index]["SphereCollider"]["LockRotX"] = p_sphereCollider->GetLockRotX();
		p_file["GameObject"][p_index]["SphereCollider"]["LockRotY"] = p_sphereCollider->GetLockRotY();
		p_file["GameObject"][p_index]["SphereCollider"]["LockRotZ"] = p_sphereCollider->GetLockRotZ();

		SaveVector3(p_file, p_sphereCollider->GetOffset(), p_index, "SphereCollider", "Offset");
	}

	void SavePlaneCollider(nlohmann::json& p_file, const MonoBehavior::Physics::PlaneCollider* p_planeCollider, unsigned int p_index)
	{
		p_file["GameObject"][p_index]["PlaneCollider"]["Queryable"] = p_planeCollider->Queryable();
	}

	void SaveAudioSource(nlohmann::json& p_file, const MonoBehavior::AudioSource* p_audioSource, unsigned int p_index)
	{
		p_file["GameObject"][p_index]["AudioSource"]["Sound"] = p_audioSource->GetSound()->GetPath();
		p_file["GameObject"][p_index]["AudioSource"]["Channel"] = p_audioSource->GetChannel();
		p_file["GameObject"][p_index]["AudioSource"]["PlayOnLoop"] = p_audioSource->GetPlayOnLoop();
		p_file["GameObject"][p_index]["AudioSource"]["MinRange"] = p_audioSource->GetMinRange();
		p_file["GameObject"][p_index]["AudioSource"]["MaxRange"] = p_audioSource->GetMaxRange();
	}

	void SaveRandomRotation(nlohmann::json& p_file, unsigned int p_index)
	{
		p_file["GameObject"][p_index]["RandomRotation"]["IsPresent"] = true;
	}

	void SaveMoveCamera(nlohmann::json& p_file, unsigned int p_index)
	{
		p_file["GameObject"][p_index]["MoveCamera"]["IsPresent"] = true;
	}
	
	void SaveCanva(nlohmann::json& p_file, const MonoBehavior::Canva* p_canva,  unsigned int p_index)
	{
		SaveVector2(p_file, p_canva->GetPosition(), p_index, "Canva", "posSet");
		SaveVector4(p_file, p_canva->GetColor(), p_index, "Canva", "color");
		p_file["GameObject"][p_index]["Canva"]["width"] = p_canva->GetWidth();
		p_file["GameObject"][p_index]["Canva"]["height"] = p_canva->GetHeight();
		p_file["GameObject"][p_index]["Canva"]["timer"] = p_canva->GetTimer();
		p_file["GameObject"][p_index]["Canva"]["scale"] = p_canva->GetScale();
	}

	void SaveBobScript(nlohmann::json& p_file, unsigned int p_index)
	{
		p_file["GameObject"][p_index]["BobScript"]["IsPresent"] = true;
	}

	void SaveTransitionScript(nlohmann::json& p_file, unsigned int p_index)
	{
		p_file["GameObject"][p_index]["TransitionScript"]["IsPresent"] = true;
	}

	void SavePlayerAttack(nlohmann::json& p_file, unsigned int p_index)
	{
		p_file["GameObject"][p_index]["PlayerAttack"]["IsPresent"] = true;
	}

	void SavePlaySoundScript(nlohmann::json& p_file, unsigned int p_index)
	{
		p_file["GameObject"][p_index]["PlaySoundScript"]["IsPresent"] = true;
	}

	void SaveColliderPlayerAttack(nlohmann::json& p_file, unsigned int p_index)
	{
		p_file["GameObject"][p_index]["ColliderPlayerAttack"]["IsPresent"] = true;
	}

	void SaveLifeScript(nlohmann::json& p_file, unsigned int p_index)
	{
		p_file["GameObject"][p_index]["LifeScript"]["IsPresent"] = true;
	}

	void SaveMenuScript(nlohmann::json& p_file, unsigned int p_index)
	{
		p_file["GameObject"][p_index]["MenuScript"]["IsPresent"] = true;
	}

	void SaveJumpScript(nlohmann::json& p_file, unsigned int p_index)
	{
		p_file["GameObject"][p_index]["JumpScript"]["IsPresent"] = true;
	}

	void SavePlayThemeScript(nlohmann::json& p_file, unsigned int p_index)
	{
		p_file["GameObject"][p_index]["PlayThemeScript"]["IsPresent"] = true;
	}

	void SaveSoundAsset(nlohmann::json& p_file, unsigned int p_index)
	{
		p_file["GameObject"][p_index]["SoundAsset"]["IsPresent"] = true;
	}

	void SaveZombieFollowAttack(nlohmann::json& p_file, unsigned int p_index)
	{
		p_file["GameObject"][p_index]["ZombieFollowAttack"]["IsPresent"] = true;
	}

	void SaveLifeDisplay(nlohmann::json& p_file, unsigned int p_index)
	{
		p_file["GameObject"][p_index]["LifeDisplay"]["IsPresent"] = true;
	}

	void SavePlaySoundEnemy(nlohmann::json& p_file, unsigned int p_index)
	{
		p_file["GameObject"][p_index]["PlaySoundEnemy"]["IsPresent"] = true;
	}

	void SaveComponents(nlohmann::json& p_file, const std::vector<MonoBehavior::IComponent*>& p_components, unsigned int p_index)
	{
		for (MonoBehavior::IComponent* component : p_components)
		{
			if (dynamic_cast<MonoBehavior::Renderer::Camera*>(component))
			{
				SaveCamera(p_file, dynamic_cast<MonoBehavior::Renderer::Camera*>(component), p_index);
			}
			else if (dynamic_cast<MonoBehavior::Animator*>(component))
			{
				SaveAnimator(p_file, dynamic_cast<MonoBehavior::Animator*>(component), p_index);
			}
			else if(dynamic_cast<MonoBehavior::Renderer::Model*>(component))
			{
				SaveModel(p_file, dynamic_cast<MonoBehavior::Renderer::Model*>(component), p_index);
			}
			else if (dynamic_cast<MonoBehavior::Renderer::DirectionalLight*>(component))
			{
				SaveDirectionalLight(p_file, dynamic_cast<MonoBehavior::Renderer::DirectionalLight*>(component), p_index);
			}
			else if (dynamic_cast<MonoBehavior::Renderer::SpotLight*>(component))
			{
				SaveSpotLight(p_file, dynamic_cast<MonoBehavior::Renderer::SpotLight*>(component), p_index);
			}
			else if (dynamic_cast<MonoBehavior::Renderer::PointLight*>(component))
			{
				SavePointLight(p_file, dynamic_cast<MonoBehavior::Renderer::PointLight*>(component), p_index);
			}
			else if (dynamic_cast<MonoBehavior::Physics::BoxCollider*>(component))
			{
				SaveBoxCollider(p_file, dynamic_cast<MonoBehavior::Physics::BoxCollider*>(component), p_index);
			}
			else if (dynamic_cast<MonoBehavior::Physics::CapsuleCollider*>(component))
			{
				SaveCapsuleCollider(p_file, dynamic_cast<MonoBehavior::Physics::CapsuleCollider*>(component), p_index);
			}
			else if (dynamic_cast<MonoBehavior::Physics::PlaneCollider*>(component))
			{
				SavePlaneCollider(p_file, dynamic_cast<MonoBehavior::Physics::PlaneCollider*>(component), p_index);
			}
			else if (dynamic_cast<MonoBehavior::Physics::SphereCollider*>(component))
			{
				SaveSphereCollider(p_file, dynamic_cast<MonoBehavior::Physics::SphereCollider*>(component), p_index);
			}
			else if (dynamic_cast<MonoBehavior::AudioSource*>(component))
			{
				SaveAudioSource(p_file, dynamic_cast<MonoBehavior::AudioSource*>(component), p_index);
			}
			else if (dynamic_cast<MonoBehavior::RandomRotation*>(component))
			{
				SaveRandomRotation(p_file, p_index);
			}
			else if (dynamic_cast<MonoBehavior::MoveCamera*>(component))
			{
				SaveMoveCamera(p_file, p_index);
			}
			else if (dynamic_cast<MonoBehavior::Canva*>(component))
			{
				SaveCanva(p_file, dynamic_cast<MonoBehavior::Canva*>(component), p_index);
			}
			else if (dynamic_cast<MonoBehavior::BobScript*>(component))
			{
				SaveBobScript(p_file, p_index);
			}
			else if (dynamic_cast<MonoBehavior::TransitionScript*>(component))
			{
				SaveTransitionScript(p_file, p_index);
			}
			else if (dynamic_cast<MonoBehavior::PlayerAttack*>(component))
			{
				SavePlayerAttack(p_file, p_index);
			}
			else if(dynamic_cast<MonoBehavior::Script::PlaySoundScript*>(component))
			{
				SavePlaySoundScript(p_file, p_index);
			}
			else if (dynamic_cast<MonoBehavior::ColliderPlayerAttack*>(component))
			{
				SaveColliderPlayerAttack(p_file, p_index);
			}
			else if (dynamic_cast<MonoBehavior::LifeScript*>(component))
			{
				SaveLifeScript(p_file, p_index);
			}
			else if (dynamic_cast<MonoBehavior::Script::MenuScript*>(component))
			{
				SaveMenuScript(p_file, p_index);
			}
			else if (dynamic_cast<MonoBehavior::Script::JumpScript*>(component))
			{
				SaveJumpScript(p_file, p_index);
			}
			else if (dynamic_cast<MonoBehavior::Script::PlayThemeScript*>(component))
			{
				SavePlayThemeScript(p_file, p_index);
			}
			else if (dynamic_cast<MonoBehavior::SoundAsset*>(component))
			{
				SaveSoundAsset(p_file, p_index);
			}
			else if (dynamic_cast<MonoBehavior::Script::ZombieFollowAttack*>(component))
			{
				SaveZombieFollowAttack(p_file, p_index);
			}
			else if (dynamic_cast<MonoBehavior::Script::LifeDisplay*>(component))
			{
				SaveLifeDisplay(p_file, p_index);
			}
			else if (dynamic_cast<MonoBehavior::Script::PlaySoundEnemyScript*>(component))
			{
				SavePlaySoundEnemy(p_file, p_index);
			}
		}
	}

	void SaveGameObject(nlohmann::json& p_file, const DataStructure::GameObject* p_gameObject, unsigned int p_index)
	{
		if (p_gameObject->GetName() == "Camera Editor" || p_gameObject->GetName() == "Root")
		{
			return;
		}

		p_file["GameObject"][p_index]["Name"] = p_gameObject->GetName();
		if (p_gameObject->transform.parentTransform)
		{
			p_file["GameObject"][p_index]["Parent"] = p_gameObject->transform.parentTransform->gameObject->GetName();
		}
		else
		{
			p_file["GameObject"][p_index]["Parent"] = nullptr;
		}
		SaveTransform(p_file, p_gameObject->transform, p_index);
		SaveComponents(p_file, p_gameObject->components, p_index);
	}

	// ---------------------------------------
	//                 Load
	// ---------------------------------------
	Math::Vector2 LoadVector2(const nlohmann::json& p_file, const unsigned int p_index, const std::string& p_localisation, const std::string& p_type)
	{
		return Math::Vector2
		(
			p_file["GameObject"][p_index][p_localisation][p_type]["x"],
			p_file["GameObject"][p_index][p_localisation][p_type]["y"]
		);
	}

	Math::Vector3 LoadVector3(const nlohmann::json& p_file, const unsigned int p_index, const std::string& p_localisation, const std::string& p_type)
	{
		return Math::Vector3
		(
			p_file["GameObject"][p_index][p_localisation][p_type]["x"],
			p_file["GameObject"][p_index][p_localisation][p_type]["y"],
			p_file["GameObject"][p_index][p_localisation][p_type]["z"]
		);
	}

	Math::Vector4 LoadVector4(const nlohmann::json& p_file, const unsigned int p_index, const std::string& p_localisation, const std::string& p_type)
	{
		return Math::Vector4
		(
			p_file["GameObject"][p_index][p_localisation][p_type]["x"],
			p_file["GameObject"][p_index][p_localisation][p_type]["y"],
			p_file["GameObject"][p_index][p_localisation][p_type]["z"],
			p_file["GameObject"][p_index][p_localisation][p_type]["w"]
		);
	}

	Math::Quaternion LoadQuaternion(const nlohmann::json& p_file, const unsigned int p_index, const std::string& p_localisation, const std::string& p_type)
	{
		return Math::Quaternion
		(
			p_file["GameObject"][p_index][p_localisation][p_type]["x"],
			p_file["GameObject"][p_index][p_localisation][p_type]["y"],
			p_file["GameObject"][p_index][p_localisation][p_type]["z"],
			p_file["GameObject"][p_index][p_localisation][p_type]["w"]
		);
	}

	DataStructure::Transform LoadTransform(const nlohmann::json& p_file, const unsigned int p_index)
	{
		return DataStructure::Transform
		(
			LoadVector3(p_file, p_index, "Transform", "Position"),
			LoadQuaternion(p_file, p_index, "Transform", "Rotation"),
			LoadVector3(p_file, p_index, "Transform", "Scale")
		);
	}

	DataStructure::GameObject* FindGameObjectByName(Core::Scene* p_scene, const nlohmann::json& p_file, const unsigned int p_index, const std::string& p_type)
	{
		const std::string name = p_file["GameObject"][p_index][p_type];
		for (DataStructure::GameObject* gameObject : p_scene->GetGameObjects())
		{
			if (gameObject->GetName() == name)
			{
				return gameObject;
			}
		}
		return nullptr;
	}

	DataStructure::GameObject* FindParentByName(Core::Scene* p_scene, const nlohmann::json& p_file, const unsigned int p_index)
	{
		if (p_file["GameObject"][p_index]["Parent"].is_null())
		{
			return nullptr;
		}
		return FindGameObjectByName(p_scene, p_file, p_index, "Parent");
	}

	void LoadCamera(Core::Scene* p_scene, DataStructure::GameObject* p_gameObject)
	{
		p_scene->AddCamera(p_gameObject);
	}

	void LoadDirectionalLight(Core::Scene* p_scene, nlohmann::json& p_file, unsigned int p_index, DataStructure::GameObject* p_gameObject)
	{
		MonoBehavior::Renderer::InitLight initLight
		{
			LoadVector4(p_file, p_index, "DirectionalLight", "Ambient"),
			LoadVector4(p_file, p_index, "DirectionalLight", "Diffuse"),
			LoadVector4(p_file, p_index, "DirectionalLight", "Specular")
		};

		p_scene->AddLight
		(
			p_gameObject, 
			new MonoBehavior::Renderer::DirectionalLight
			(
				initLight,
				LoadVector3(p_file, p_index, "DirectionalLight", "Direction")
			)
		);
	}

	void LoadPointLight(Core::Scene* p_scene, nlohmann::json& p_file, unsigned int p_index, DataStructure::GameObject* p_gameObject)
	{
		MonoBehavior::Renderer::InitLight initLight
		{
			LoadVector4(p_file, p_index, "PointLight", "Ambient"),
			LoadVector4(p_file, p_index, "PointLight", "Diffuse"),
			LoadVector4(p_file, p_index, "PointLight", "Specular")
		};

		p_scene->AddLight
		(
			p_gameObject,
			new MonoBehavior::Renderer::PointLight
			(
				initLight,
				p_file["GameObject"][p_index]["PointLight"]["Constant"],
				p_file["GameObject"][p_index]["PointLight"]["Linear"],
				p_file["GameObject"][p_index]["PointLight"]["Quadratic"]
			)
		);
	}

	void LoadSpotLight(Core::Scene* p_scene, nlohmann::json& p_file, unsigned int p_index, DataStructure::GameObject* p_gameObject)
	{
		MonoBehavior::Renderer::InitLight initLight
		{
			LoadVector4(p_file, p_index, "SpotLight", "Ambient"),
			LoadVector4(p_file, p_index, "SpotLight", "Diffuse"),
			LoadVector4(p_file, p_index, "SpotLight", "Specular")
		};

		p_scene->AddLight
		(
			p_gameObject,
			new MonoBehavior::Renderer::SpotLight
			(
				initLight,
				LoadVector3(p_file, p_index, "SpotLight", "Direction"),
				p_file["GameObject"][p_index]["SpotLight"]["CutOff"],
				p_file["GameObject"][p_index]["SpotLight"]["OuterCutOff"],
				p_file["GameObject"][p_index]["SpotLight"]["Constant"],
				p_file["GameObject"][p_index]["SpotLight"]["Linear"],
				p_file["GameObject"][p_index]["SpotLight"]["Quadratic"]
			)
		);
	}

	void LoadModel(Core::Scene* p_scene, nlohmann::json& p_file, unsigned int p_index, DataStructure::GameObject* p_gameObject)
	{
		Core::ResourceManager* resourceManager = Core::ResourceManager::Get();
		if (p_file["GameObject"][p_index]["Model"]["Texture"].is_null())
		{
			p_gameObject->AddComponent
			(
				new MonoBehavior::Renderer::Model
				(
					resourceManager->UseMesh(p_file["GameObject"][p_index]["Model"]["Mesh"]),
					resourceManager->UseShader(p_file["GameObject"][p_index]["Model"]["ShaderVert"], p_file["GameObject"][p_index]["Model"]["ShaderFrag"]),
					nullptr
				)
			);
		}
		else
		{
			p_gameObject->AddComponent
			(
				new MonoBehavior::Renderer::Model
				(
					resourceManager->UseMesh(p_file["GameObject"][p_index]["Model"]["Mesh"]),
					resourceManager->UseShader(p_file["GameObject"][p_index]["Model"]["ShaderVert"], p_file["GameObject"][p_index]["Model"]["ShaderFrag"]),
					resourceManager->UseTexture(p_file["GameObject"][p_index]["Model"]["Texture"])
				)
			);
		}
	}

	void LoadAnimator(Core::Scene* p_scene, nlohmann::json& p_file, unsigned int p_index, DataStructure::GameObject* p_gameObject)
	{
		p_gameObject->AddComponent
		(
			new MonoBehavior::Animator
			(
				//Core::AnimationManager::Get()->UseAnimation(p_file["GameObject"][p_index]["Animator"]["Animation"], 
				//	Core::AnimationManager::Get()->UseRig(p_file["GameObject"][p_index]["Model"]["Mesh"])),
				nullptr,
				Core::ResourceManager::Get()->UseShader(p_file["GameObject"][p_index]["Model"]["ShaderVert"], p_file["GameObject"][p_index]["Model"]["ShaderFrag"])->GetShaderProgram()
			)
		);
	}

	void LoadBoxCollider(Core::Scene* p_scene, nlohmann::json& p_file, unsigned int p_index, DataStructure::GameObject* p_gameObject)
	{
		MonoBehavior::Physics::BoxCollider* box = new MonoBehavior::Physics::BoxCollider
		(
			LoadVector3(p_file, p_index, "BoxCollider", "Scale"),
			p_file["GameObject"][p_index]["BoxCollider"]["IsStatic"],
			p_file["GameObject"][p_index]["BoxCollider"]["IsTrigger"],
			p_file["GameObject"][p_index]["BoxCollider"]["Queryable"],
			LoadVector3(p_file, p_index, "BoxCollider", "Offset")
		);
		box->SetLock
		(
			p_file["GameObject"][p_index]["BoxCollider"]["LockPosX"],
			p_file["GameObject"][p_index]["BoxCollider"]["LockPosY"],
			p_file["GameObject"][p_index]["BoxCollider"]["LockPosZ"],
			p_file["GameObject"][p_index]["BoxCollider"]["LockRotX"],
			p_file["GameObject"][p_index]["BoxCollider"]["LockRotY"],
			p_file["GameObject"][p_index]["BoxCollider"]["LockRotZ"]
		);
		p_gameObject->AddComponent
		(
			box
		);
	}

	void LoadCapsuleCollider(Core::Scene* p_scene, nlohmann::json& p_file, unsigned int p_index, DataStructure::GameObject* p_gameObject)
	{
		MonoBehavior::Physics::CapsuleCollider* capsule = new MonoBehavior::Physics::CapsuleCollider
		(
			p_file["GameObject"][p_index]["CapsuleCollider"]["Radius"],
			p_file["GameObject"][p_index]["CapsuleCollider"]["Alignment"],
			p_file["GameObject"][p_index]["CapsuleCollider"]["HalfHeight"],
			p_file["GameObject"][p_index]["CapsuleCollider"]["IsStatic"],
			p_file["GameObject"][p_index]["CapsuleCollider"]["IsTrigger"],
			p_file["GameObject"][p_index]["CapsuleCollider"]["Queryable"],
			LoadVector3(p_file, p_index, "CapsuleCollider", "Offset")
		);
		capsule->SetLock
		(
			p_file["GameObject"][p_index]["CapsuleCollider"]["LockPosX"],
			p_file["GameObject"][p_index]["CapsuleCollider"]["LockPosY"],
			p_file["GameObject"][p_index]["CapsuleCollider"]["LockPosZ"],
			p_file["GameObject"][p_index]["CapsuleCollider"]["LockRotX"],
			p_file["GameObject"][p_index]["CapsuleCollider"]["LockRotY"],
			p_file["GameObject"][p_index]["CapsuleCollider"]["LockRotZ"]
		);
		p_gameObject->AddComponent
		(
			capsule
		);
	}

	void LoadPlaneCollider(Core::Scene* p_scene, nlohmann::json& p_file, unsigned int p_index, DataStructure::GameObject* p_gameObject)
	{
		p_gameObject->AddComponent
		(
			new MonoBehavior::Physics::PlaneCollider
			(
				p_file["GameObject"][p_index]["PlaneCollider"]["Queryable"]
			)
		);
	}

	void LoadSphereCollider(Core::Scene* p_scene, nlohmann::json& p_file, unsigned int p_index, DataStructure::GameObject* p_gameObject)
	{
		MonoBehavior::Physics::SphereCollider* sphere = new MonoBehavior::Physics::SphereCollider
		(
			p_file["GameObject"][p_index]["SphereCollider"]["Radius"],
			p_file["GameObject"][p_index]["SphereCollider"]["IsStatic"],
			p_file["GameObject"][p_index]["SphereCollider"]["IsTrigger"],
			p_file["GameObject"][p_index]["SphereCollider"]["Queryable"],
			LoadVector3(p_file, p_index, "SphereCollider", "Offset")
		);
		sphere->SetLock
		(
			p_file["GameObject"][p_index]["SphereCollider"]["LockPosX"],
			p_file["GameObject"][p_index]["SphereCollider"]["LockPosY"],
			p_file["GameObject"][p_index]["SphereCollider"]["LockPosZ"],
			p_file["GameObject"][p_index]["SphereCollider"]["LockRotX"],
			p_file["GameObject"][p_index]["SphereCollider"]["LockRotY"],
			p_file["GameObject"][p_index]["SphereCollider"]["LockRotZ"]
		);
		p_gameObject->AddComponent
		(
			sphere
		);
	}

	void LoadAudioSource(Core::Scene* p_scene, nlohmann::json& p_file, unsigned int p_index, DataStructure::GameObject* p_gameObject)
	{
		p_gameObject->AddComponent
		(
			new MonoBehavior::AudioSource
			(
				Core::ResourceManager::Get()->UseSound(p_file["GameObject"][p_index]["AudioSource"]["Sound"]),
				p_file["GameObject"][p_index]["AudioSource"]["Channel"],
				p_file["GameObject"][p_index]["AudioSource"]["PlayOnLoop"],
				p_file["GameObject"][p_index]["AudioSource"]["MinRange"],
				p_file["GameObject"][p_index]["AudioSource"]["MaxRange"]
			)
		);
	}  

	void LoadCanva(Core::Scene* p_scene, nlohmann::json& p_file, unsigned int p_index, DataStructure::GameObject* p_gameObject)
	{
		p_gameObject->AddComponent
		(
			new MonoBehavior::Canva
			(
				LoadVector2(p_file, p_index, "Canva", "posSet"),
				LoadVector4(p_file, p_index, "Canva", "color"),
				p_file["GameObject"][p_index]["Canva"]["width"],
				p_file["GameObject"][p_index]["Canva"]["height"],
				p_file["GameObject"][p_index]["Canva"]["timer"],
				p_file["GameObject"][p_index]["Canva"]["scale"]
			)
		);
	}

	// TODO : Update load and save system for script
	void LoadRandomRotation(Core::Scene* p_scene, nlohmann::json& p_file, unsigned int p_index, DataStructure::GameObject* p_gameObject)
	{
		p_gameObject->AddComponent(new MonoBehavior::RandomRotation);
	}

	void LoadMoveCamera(Core::Scene* p_scene, nlohmann::json& p_file, unsigned int p_index, DataStructure::GameObject* p_gameObject)
	{
		p_gameObject->AddComponent(new MonoBehavior::MoveCamera);
	}

	void LoadBobScript(Core::Scene* p_scene, nlohmann::json& p_file, unsigned int p_index, DataStructure::GameObject* p_gameObject)
	{
		p_gameObject->AddComponent(new MonoBehavior::BobScript);
	}

	void LoadTransitionScript(Core::Scene* p_scene, nlohmann::json& p_file, unsigned int p_index, DataStructure::GameObject* p_gameObject)
	{
		p_gameObject->AddComponent(new MonoBehavior::TransitionScript);
	}

	void LoadPlayerAttack(Core::Scene* p_scene, nlohmann::json& p_file, unsigned int p_index, DataStructure::GameObject* p_gameObject)
	{
		p_gameObject->AddComponent(new MonoBehavior::PlayerAttack);
	}

	void LoadPlaySoundScript(Core::Scene* p_scene, nlohmann::json& p_file, unsigned int p_index, DataStructure::GameObject* p_gameObject)
	{
		p_gameObject->AddComponent(new MonoBehavior::Script::PlaySoundScript);
	}

	void LoadColliderPlayerAttack(Core::Scene* p_scene, nlohmann::json& p_file, unsigned int p_index, DataStructure::GameObject* p_gameObject)
	{
		p_gameObject->AddComponent(new MonoBehavior::ColliderPlayerAttack);
	}

	void LoadLifeScript(Core::Scene* p_scene, nlohmann::json& p_file, unsigned int p_index, DataStructure::GameObject* p_gameObject)
	{
		p_gameObject->AddComponent(new MonoBehavior::LifeScript);
	}

	void LoadMenuScript(Core::Scene* p_scene, nlohmann::json& p_file, unsigned int p_index, DataStructure::GameObject* p_gameObject)
	{
		p_gameObject->AddComponent
		(
			new MonoBehavior::Script::MenuScript()
		);
	}

	void LoadJumpScript(Core::Scene* p_scene, nlohmann::json& p_file, unsigned int p_index, DataStructure::GameObject* p_gameObject)
	{
		p_gameObject->AddComponent
		(
			new MonoBehavior::Script::JumpScript()
		);
	}

	void LoadPlayThemeScript(Core::Scene* p_scene, nlohmann::json& p_file, unsigned int p_index, DataStructure::GameObject* p_gameObject)
	{
		p_gameObject->AddComponent
		(
			new MonoBehavior::Script::PlayThemeScript()
		);
	}

	void LoadSoundAsset(Core::Scene* p_scene, nlohmann::json& p_file, unsigned int p_index, DataStructure::GameObject* p_gameObject)
	{
		p_gameObject->AddComponent
		(
			new MonoBehavior::SoundAsset()
		);
	}

	void LoadZombieFollowAttack(Core::Scene* p_scene, nlohmann::json& p_file, unsigned int p_index, DataStructure::GameObject* p_gameObject)
	{
		p_gameObject->AddComponent
		(
			new MonoBehavior::Script::ZombieFollowAttack()
		);
	}

	void LoadLifeDisplay(Core::Scene* p_scene, nlohmann::json& p_file, unsigned int p_index, DataStructure::GameObject* p_gameObject)
	{
		p_gameObject->AddComponent
		(
			new MonoBehavior::Script::LifeDisplay()
		);
	}

	void LoadPlaySoundEnemy(Core::Scene* p_scene, nlohmann::json& p_file, unsigned int p_index, DataStructure::GameObject* p_gameObject)
	{
		p_gameObject->AddComponent
		(
			new MonoBehavior::Script::PlaySoundEnemyScript()
		);
	}

	void LoadComponents(Core::Scene* p_scene, nlohmann::json& p_file, const unsigned int p_index)
	{
		DataStructure::GameObject* gameObject = FindGameObjectByName(p_scene, p_file, p_index, "Name");
		if (p_file["GameObject"][p_index]["Camera"].get<nlohmann::json::object_t*>())
		{
			LoadCamera(p_scene, gameObject);
		}
		if (p_file["GameObject"][p_index]["DirectionalLight"].get<nlohmann::json::object_t*>())
		{
			LoadDirectionalLight(p_scene, p_file, p_index, gameObject);
		}
		if (p_file["GameObject"][p_index]["PointLight"].get<nlohmann::json::object_t*>())
		{
			LoadPointLight(p_scene, p_file, p_index, gameObject);
		}
		if (p_file["GameObject"][p_index]["SpotLight"].get<nlohmann::json::object_t*>())
		{
			LoadSpotLight(p_scene, p_file, p_index, gameObject);
		}
		if (p_file["GameObject"][p_index]["Animator"].get<nlohmann::json::object_t*>())
		{
			LoadAnimator(p_scene, p_file, p_index, gameObject);
		}
		if (p_file["GameObject"][p_index]["Model"].get<nlohmann::json::object_t*>())
		{
			LoadModel(p_scene, p_file, p_index, gameObject);
		}
		if (p_file["GameObject"][p_index]["BoxCollider"].get<nlohmann::json::object_t*>())
		{
			LoadBoxCollider(p_scene, p_file, p_index, gameObject);
		}
		if (p_file["GameObject"][p_index]["CapsuleCollider"].get<nlohmann::json::object_t*>())
		{
			LoadCapsuleCollider(p_scene, p_file, p_index, gameObject);
		}
		if (p_file["GameObject"][p_index]["PlaneCollider"].get<nlohmann::json::object_t*>())
		{
			LoadPlaneCollider(p_scene, p_file, p_index, gameObject);
		}
		if (p_file["GameObject"][p_index]["SphereCollider"].get<nlohmann::json::object_t*>())
		{
			LoadSphereCollider(p_scene, p_file, p_index, gameObject);
		}
		if (p_file["GameObject"][p_index]["AudioSource"].get<nlohmann::json::object_t*>())
		{
			LoadAudioSource(p_scene, p_file, p_index, gameObject);
		}
		if (p_file["GameObject"][p_index]["RandomRotation"].get<nlohmann::json::object_t*>())
		{
			LoadRandomRotation(p_scene, p_file, p_index, gameObject);
		}
		if (p_file["GameObject"][p_index]["MoveCamera"].get<nlohmann::json::object_t*>())
		{
			LoadMoveCamera(p_scene, p_file, p_index, gameObject);
		}
		if (p_file["GameObject"][p_index]["Canva"].get<nlohmann::json::object_t*>())
		{
			LoadCanva(p_scene, p_file, p_index, gameObject);
		}
		if (p_file["GameObject"][p_index]["BobScript"].get<nlohmann::json::object_t*>())
		{
			LoadBobScript(p_scene, p_file, p_index, gameObject);
		}
		if (p_file["GameObject"][p_index]["TransitionScript"].get<nlohmann::json::object_t*>())
		{
			LoadTransitionScript(p_scene, p_file, p_index, gameObject);
		}
		if (p_file["GameObject"][p_index]["PlayerAttack"].get<nlohmann::json::object_t*>())
		{
			LoadPlayerAttack(p_scene, p_file, p_index, gameObject);
		}
		if (p_file["GameObject"][p_index]["PlaySoundScript"].get<nlohmann::json::object_t*>())
		{
			LoadPlaySoundScript(p_scene, p_file, p_index, gameObject);
		}
		if (p_file["GameObject"][p_index]["ColliderPlayerAttack"].get<nlohmann::json::object_t*>())
		{
			LoadColliderPlayerAttack(p_scene, p_file, p_index, gameObject);
		}
		if (p_file["GameObject"][p_index]["LifeScript"].get<nlohmann::json::object_t*>())
		{
			LoadLifeScript(p_scene, p_file, p_index, gameObject);
		}
		if (p_file["GameObject"][p_index]["MenuScript"].get<nlohmann::json::object_t*>())
		{
			LoadMenuScript(p_scene, p_file, p_index, gameObject);
		}
		if (p_file["GameObject"][p_index]["JumpScript"].get<nlohmann::json::object_t*>())
		{
			LoadJumpScript(p_scene, p_file, p_index, gameObject);
		}
		if (p_file["GameObject"][p_index]["PlayThemeScript"].get<nlohmann::json::object_t*>())
		{
			LoadPlayThemeScript(p_scene, p_file, p_index, gameObject);
		}
		if (p_file["GameObject"][p_index]["SoundAsset"].get<nlohmann::json::object_t*>())
		{
			LoadSoundAsset(p_scene, p_file, p_index, gameObject);
		}
		if (p_file["GameObject"][p_index]["ZombieFollowAttack"].get<nlohmann::json::object_t*>())
		{
			LoadZombieFollowAttack(p_scene, p_file, p_index, gameObject);
		}
		if (p_file["GameObject"][p_index]["LifeDisplay"].get<nlohmann::json::object_t*>())
		{
			LoadLifeDisplay(p_scene, p_file, p_index, gameObject);
		}
		if (p_file["GameObject"][p_index]["PlaySoundEnemy"].get<nlohmann::json::object_t*>())
		{
			LoadPlaySoundEnemy(p_scene, p_file, p_index, gameObject);
		}
	}

	void LoadGameObject(Core::Scene* p_scene, nlohmann::json& p_file, const unsigned int p_index)
	{
		//Prevent crash with null from Root json
		if (p_index != 0)
		{
			p_scene->AddGameObject
			(
				p_file["GameObject"][p_index]["Name"],
				LoadTransform(p_file, p_index),
				FindParentByName(p_scene, p_file, p_index)
			);
			LoadComponents(p_scene, p_file, p_index);
		}
	}

#pragma endregion UTILITY

	// ---------------------------------------
	//               JsonLayer
	// ---------------------------------------
	void Save(Core::Scene* p_scene)
	{
		if (p_scene->GetSceneType() != Core::SceneType::Scene)
		{
			return;
		}

		nlohmann::json jsonFile;
		for (unsigned int i = 0; i < p_scene->GetGameObjects().size(); i++)
		{
			SaveGameObject(jsonFile, p_scene->GetGameObjects()[i], i);
		}

		std::ofstream file("Resources/Scenes/" + p_scene->GetName() + ".json");
		file << std::setw(4) << jsonFile;
		file.close();
		Log::Print("Scene save!", LOG_LEVEL_TYPE::Notification);
	}

	void LoadSave(Core::Scene* p_scene)
	{
		std::ifstream file("Resources/Scenes/" + p_scene->GetName() + ".json");
		nlohmann::json jsonFile = nlohmann::json::parse(file);

		for (unsigned int i = 0; i < jsonFile["GameObject"].size(); i++)
		{
			LoadGameObject(p_scene, jsonFile, i);
		}
	}

	void SaveConfig(Input::InputManager* p_inputManager)
	{
		nlohmann::json jsonFile;

		jsonFile["Input"]["forward"] = p_inputManager->forward;
		jsonFile["Input"]["backward"] = p_inputManager->backward;
		jsonFile["Input"]["left"] = p_inputManager->left;
		jsonFile["Input"]["right"] = p_inputManager->right;
		jsonFile["Input"]["down"] = p_inputManager->down;
		jsonFile["Input"]["up"] = p_inputManager->up;
		jsonFile["Input"]["sensitivity"] = p_inputManager->sensitivity;
		jsonFile["Input"]["quit"] = Wrapper::Window::closeEditor;
		jsonFile["Input"]["gameForward"] = p_inputManager->gameForward;
		jsonFile["Input"]["gameBackward"] = p_inputManager->gameBackward;
		jsonFile["Input"]["gameLeft"] = p_inputManager->gameLeft;
		jsonFile["Input"]["gameRight"] = p_inputManager->gameRight;
		jsonFile["Input"]["gameJump"] = p_inputManager->gameJump;
		jsonFile["Input"]["gameAttack"] = p_inputManager->gameAttack;
		jsonFile["Input"]["gameQuit"] = p_inputManager->gameQuit;
		jsonFile["Input"]["gameMenu"] = p_inputManager->gameMenu;

		std::ofstream file("Resources/Config.json");
		file << std::setw(4) << jsonFile;
		file.close();
		Log::Print("Config save!", LOG_LEVEL_TYPE::Notification);
	}

	void LoadConfig(Input::InputManager* p_inputManager)
	{
		std::ifstream file("Resources/Config.json");
		nlohmann::json jsonFile = nlohmann::json::parse(file);

		p_inputManager->forward = jsonFile["Input"]["forward"];
		p_inputManager->backward = jsonFile["Input"]["backward"];
		p_inputManager->left = jsonFile["Input"]["left"];
		p_inputManager->right = jsonFile["Input"]["right"];
		p_inputManager->down = jsonFile["Input"]["down"];
		p_inputManager->up = jsonFile["Input"]["up"];
		p_inputManager->sensitivity = jsonFile["Input"]["sensitivity"];
		Wrapper::Window::closeEditor = jsonFile["Input"]["quit"];
		p_inputManager->gameForward = jsonFile["Input"]["gameForward"];
		p_inputManager->gameBackward = jsonFile["Input"]["gameBackward"];
		p_inputManager->gameLeft = jsonFile["Input"]["gameLeft"];
		p_inputManager->gameRight = jsonFile["Input"]["gameRight"];
		p_inputManager->gameJump = jsonFile["Input"]["gameJump"];
		p_inputManager->gameAttack = jsonFile["Input"]["gameAttack"];
		p_inputManager->gameQuit = jsonFile["Input"]["gameQuit"];
		p_inputManager->gameMenu = jsonFile["Input"]["gameMenu"];
		file.close();
	}

}
