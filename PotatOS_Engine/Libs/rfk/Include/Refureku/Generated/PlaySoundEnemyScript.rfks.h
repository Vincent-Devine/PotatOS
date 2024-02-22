#pragma once

#include "../../../../../Headers/MonoBehavior/Scripts/PlaySoundEnemyScript.hpp"

#include <type_traits>
#include <Refureku/TypeInfo/Entity/DefaultEntityRegisterer.h>
#include <Refureku/TypeInfo/Archetypes/ArchetypeRegisterer.h>
#include <Refureku/TypeInfo/Namespace/Namespace.h>
#include <Refureku/TypeInfo/Namespace/NamespaceFragment.h>
#include <Refureku/TypeInfo/Namespace/NamespaceFragmentRegisterer.h>
#include <Refureku/TypeInfo/Archetypes/Template/TypeTemplateParameter.h>
#include <Refureku/TypeInfo/Archetypes/Template/NonTypeTemplateParameter.h>
#include <Refureku/TypeInfo/Archetypes/Template/TemplateTemplateParameter.h>

namespace rfk::generated { 
 static rfk::NamespaceFragment const& getNamespaceFragment_320970643918520520u_17564612467593220999() noexcept {
static rfk::NamespaceFragment fragment("Script", 320970643918520520u);
static bool initialized = false;
if (!initialized) {
initialized = true;
fragment.setNestedEntitiesCapacity(1u);
fragment.addNestedEntity(*rfk::getArchetype<MonoBehavior::Script::PlaySoundEnemyScript>());
}
return fragment; }
 static rfk::NamespaceFragment const& getNamespaceFragment_17331560784760942515u_17564612467593220999() noexcept {
static rfk::NamespaceFragment fragment("MonoBehavior", 17331560784760942515u);
static bool initialized = false;
if (!initialized) {
initialized = true;
fragment.setNestedEntitiesCapacity(1u);
fragment.addNestedEntity(rfk::generated::getNamespaceFragment_320970643918520520u_17564612467593220999());
}
return fragment; }
static rfk::NamespaceFragmentRegisterer const namespaceFragmentRegisterer_17331560784760942515u_17564612467593220999(rfk::generated::getNamespaceFragment_17331560784760942515u_17564612467593220999());
 }
rfk::Class const& MonoBehavior::Script::PlaySoundEnemyScript::staticGetArchetype() noexcept {
static bool initialized = false;
static rfk::Class type("PlaySoundEnemyScript", 8377046185607629127u, sizeof(PlaySoundEnemyScript), 1);
if (!initialized) {
initialized = true;
type.setDirectParentsCapacity(1);
type.addDirectParent(rfk::getArchetype<MonoBehavior::Script::BaseScript>(), static_cast<rfk::EAccessSpecifier>(1));
PlaySoundEnemyScript::_rfk_registerChildClass<PlaySoundEnemyScript>(type);
static rfk::StaticMethod defaultSharedInstantiator("", 0u, rfk::getType<rfk::SharedPtr<PlaySoundEnemyScript>>(),new rfk::NonMemberFunction<rfk::SharedPtr<PlaySoundEnemyScript>()>(&rfk::internal::CodeGenerationHelpers::defaultSharedInstantiator<PlaySoundEnemyScript>),rfk::EMethodFlags::Default, nullptr);
type.addSharedInstantiator(defaultSharedInstantiator);
static rfk::StaticMethod defaultUniqueInstantiator("", 0u, rfk::getType<rfk::UniquePtr<PlaySoundEnemyScript>>(),new rfk::NonMemberFunction<rfk::UniquePtr<PlaySoundEnemyScript>()>(&rfk::internal::CodeGenerationHelpers::defaultUniqueInstantiator<PlaySoundEnemyScript>),rfk::EMethodFlags::Default, nullptr);
type.addUniqueInstantiator(defaultUniqueInstantiator);
type.setMethodsCapacity(0u); type.setStaticMethodsCapacity(0u); 
}
return type; }

template <> rfk::Archetype const* rfk::getArchetype<MonoBehavior::Script::PlaySoundEnemyScript>() noexcept { return &MonoBehavior::Script::PlaySoundEnemyScript::staticGetArchetype(); }


