#pragma once

#include "../../../../../Headers/MonoBehavior/Renderer/PointLight.hpp"

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
 static rfk::NamespaceFragment const& getNamespaceFragment_14648874301494198576u_8505541759213666349() noexcept {
static rfk::NamespaceFragment fragment("Renderer", 14648874301494198576u);
static bool initialized = false;
if (!initialized) {
initialized = true;
fragment.setNestedEntitiesCapacity(1u);
fragment.addNestedEntity(*rfk::getArchetype<MonoBehavior::Renderer::PointLight>());
}
return fragment; }
 static rfk::NamespaceFragment const& getNamespaceFragment_17331560784760942515u_8505541759213666349() noexcept {
static rfk::NamespaceFragment fragment("MonoBehavior", 17331560784760942515u);
static bool initialized = false;
if (!initialized) {
initialized = true;
fragment.setNestedEntitiesCapacity(1u);
fragment.addNestedEntity(rfk::generated::getNamespaceFragment_14648874301494198576u_8505541759213666349());
}
return fragment; }
static rfk::NamespaceFragmentRegisterer const namespaceFragmentRegisterer_17331560784760942515u_8505541759213666349(rfk::generated::getNamespaceFragment_17331560784760942515u_8505541759213666349());
 }
rfk::Class const& MonoBehavior::Renderer::PointLight::staticGetArchetype() noexcept {
static bool initialized = false;
static rfk::Class type("PointLight", 10841590645452892205u, sizeof(PointLight), 1);
if (!initialized) {
initialized = true;
type.setDirectParentsCapacity(1);
type.addDirectParent(rfk::getArchetype<MonoBehavior::Renderer::Light>(), static_cast<rfk::EAccessSpecifier>(1));
PointLight::_rfk_registerChildClass<PointLight>(type);
static rfk::StaticMethod defaultSharedInstantiator("", 0u, rfk::getType<rfk::SharedPtr<PointLight>>(),new rfk::NonMemberFunction<rfk::SharedPtr<PointLight>()>(&rfk::internal::CodeGenerationHelpers::defaultSharedInstantiator<PointLight>),rfk::EMethodFlags::Default, nullptr);
type.addSharedInstantiator(defaultSharedInstantiator);
static rfk::StaticMethod defaultUniqueInstantiator("", 0u, rfk::getType<rfk::UniquePtr<PointLight>>(),new rfk::NonMemberFunction<rfk::UniquePtr<PointLight>()>(&rfk::internal::CodeGenerationHelpers::defaultUniqueInstantiator<PointLight>),rfk::EMethodFlags::Default, nullptr);
type.addUniqueInstantiator(defaultUniqueInstantiator);
type.setMethodsCapacity(0u); type.setStaticMethodsCapacity(0u); 
}
return type; }

template <> rfk::Archetype const* rfk::getArchetype<MonoBehavior::Renderer::PointLight>() noexcept { return &MonoBehavior::Renderer::PointLight::staticGetArchetype(); }


