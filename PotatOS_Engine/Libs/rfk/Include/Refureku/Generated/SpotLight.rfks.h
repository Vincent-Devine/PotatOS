#pragma once

#include "../../../../../Headers/MonoBehavior/Renderer/SpotLight.hpp"

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
 static rfk::NamespaceFragment const& getNamespaceFragment_14648874301494198576u_8645760331972409483() noexcept {
static rfk::NamespaceFragment fragment("Renderer", 14648874301494198576u);
static bool initialized = false;
if (!initialized) {
initialized = true;
fragment.setNestedEntitiesCapacity(1u);
fragment.addNestedEntity(*rfk::getArchetype<MonoBehavior::Renderer::SpotLight>());
}
return fragment; }
 static rfk::NamespaceFragment const& getNamespaceFragment_17331560784760942515u_8645760331972409483() noexcept {
static rfk::NamespaceFragment fragment("MonoBehavior", 17331560784760942515u);
static bool initialized = false;
if (!initialized) {
initialized = true;
fragment.setNestedEntitiesCapacity(1u);
fragment.addNestedEntity(rfk::generated::getNamespaceFragment_14648874301494198576u_8645760331972409483());
}
return fragment; }
static rfk::NamespaceFragmentRegisterer const namespaceFragmentRegisterer_17331560784760942515u_8645760331972409483(rfk::generated::getNamespaceFragment_17331560784760942515u_8645760331972409483());
 }
rfk::Class const& MonoBehavior::Renderer::SpotLight::staticGetArchetype() noexcept {
static bool initialized = false;
static rfk::Class type("SpotLight", 17469487248570614269u, sizeof(SpotLight), 1);
if (!initialized) {
initialized = true;
type.setDirectParentsCapacity(1);
type.addDirectParent(rfk::getArchetype<MonoBehavior::Renderer::Light>(), static_cast<rfk::EAccessSpecifier>(1));
SpotLight::_rfk_registerChildClass<SpotLight>(type);
static rfk::StaticMethod defaultSharedInstantiator("", 0u, rfk::getType<rfk::SharedPtr<SpotLight>>(),new rfk::NonMemberFunction<rfk::SharedPtr<SpotLight>()>(&rfk::internal::CodeGenerationHelpers::defaultSharedInstantiator<SpotLight>),rfk::EMethodFlags::Default, nullptr);
type.addSharedInstantiator(defaultSharedInstantiator);
static rfk::StaticMethod defaultUniqueInstantiator("", 0u, rfk::getType<rfk::UniquePtr<SpotLight>>(),new rfk::NonMemberFunction<rfk::UniquePtr<SpotLight>()>(&rfk::internal::CodeGenerationHelpers::defaultUniqueInstantiator<SpotLight>),rfk::EMethodFlags::Default, nullptr);
type.addUniqueInstantiator(defaultUniqueInstantiator);
type.setMethodsCapacity(0u); type.setStaticMethodsCapacity(0u); 
}
return type; }

template <> rfk::Archetype const* rfk::getArchetype<MonoBehavior::Renderer::SpotLight>() noexcept { return &MonoBehavior::Renderer::SpotLight::staticGetArchetype(); }


