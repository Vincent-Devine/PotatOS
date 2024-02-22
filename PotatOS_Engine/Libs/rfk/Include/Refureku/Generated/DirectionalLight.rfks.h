#pragma once

#include "../../../../../Headers/MonoBehavior/Renderer/DirectionalLight.hpp"

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
 static rfk::NamespaceFragment const& getNamespaceFragment_14648874301494198576u_9293959666559423463() noexcept {
static rfk::NamespaceFragment fragment("Renderer", 14648874301494198576u);
static bool initialized = false;
if (!initialized) {
initialized = true;
fragment.setNestedEntitiesCapacity(1u);
fragment.addNestedEntity(*rfk::getArchetype<MonoBehavior::Renderer::DirectionalLight>());
}
return fragment; }
 static rfk::NamespaceFragment const& getNamespaceFragment_17331560784760942515u_9293959666559423463() noexcept {
static rfk::NamespaceFragment fragment("MonoBehavior", 17331560784760942515u);
static bool initialized = false;
if (!initialized) {
initialized = true;
fragment.setNestedEntitiesCapacity(1u);
fragment.addNestedEntity(rfk::generated::getNamespaceFragment_14648874301494198576u_9293959666559423463());
}
return fragment; }
static rfk::NamespaceFragmentRegisterer const namespaceFragmentRegisterer_17331560784760942515u_9293959666559423463(rfk::generated::getNamespaceFragment_17331560784760942515u_9293959666559423463());
 }
rfk::Class const& MonoBehavior::Renderer::DirectionalLight::staticGetArchetype() noexcept {
static bool initialized = false;
static rfk::Class type("DirectionalLight", 17278736663729273219u, sizeof(DirectionalLight), 1);
if (!initialized) {
initialized = true;
type.setDirectParentsCapacity(1);
type.addDirectParent(rfk::getArchetype<MonoBehavior::Renderer::Light>(), static_cast<rfk::EAccessSpecifier>(1));
DirectionalLight::_rfk_registerChildClass<DirectionalLight>(type);
static rfk::StaticMethod defaultSharedInstantiator("", 0u, rfk::getType<rfk::SharedPtr<DirectionalLight>>(),new rfk::NonMemberFunction<rfk::SharedPtr<DirectionalLight>()>(&rfk::internal::CodeGenerationHelpers::defaultSharedInstantiator<DirectionalLight>),rfk::EMethodFlags::Default, nullptr);
type.addSharedInstantiator(defaultSharedInstantiator);
static rfk::StaticMethod defaultUniqueInstantiator("", 0u, rfk::getType<rfk::UniquePtr<DirectionalLight>>(),new rfk::NonMemberFunction<rfk::UniquePtr<DirectionalLight>()>(&rfk::internal::CodeGenerationHelpers::defaultUniqueInstantiator<DirectionalLight>),rfk::EMethodFlags::Default, nullptr);
type.addUniqueInstantiator(defaultUniqueInstantiator);
type.setMethodsCapacity(0u); type.setStaticMethodsCapacity(0u); 
}
return type; }

template <> rfk::Archetype const* rfk::getArchetype<MonoBehavior::Renderer::DirectionalLight>() noexcept { return &MonoBehavior::Renderer::DirectionalLight::staticGetArchetype(); }


