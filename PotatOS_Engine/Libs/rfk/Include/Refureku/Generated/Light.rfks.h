#pragma once

#include "../../../../../Headers/MonoBehavior/Renderer/Light.hpp"

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
 static rfk::NamespaceFragment const& getNamespaceFragment_14648874301494198576u_6356927904727275936() noexcept {
static rfk::NamespaceFragment fragment("Renderer", 14648874301494198576u);
static bool initialized = false;
if (!initialized) {
initialized = true;
fragment.setNestedEntitiesCapacity(1u);
fragment.addNestedEntity(*rfk::getArchetype<MonoBehavior::Renderer::Light>());
}
return fragment; }
 static rfk::NamespaceFragment const& getNamespaceFragment_17331560784760942515u_6356927904727275936() noexcept {
static rfk::NamespaceFragment fragment("MonoBehavior", 17331560784760942515u);
static bool initialized = false;
if (!initialized) {
initialized = true;
fragment.setNestedEntitiesCapacity(1u);
fragment.addNestedEntity(rfk::generated::getNamespaceFragment_14648874301494198576u_6356927904727275936());
}
return fragment; }
static rfk::NamespaceFragmentRegisterer const namespaceFragmentRegisterer_17331560784760942515u_6356927904727275936(rfk::generated::getNamespaceFragment_17331560784760942515u_6356927904727275936());
 }
rfk::Class const& MonoBehavior::Renderer::Light::staticGetArchetype() noexcept {
static bool initialized = false;
static rfk::Class type("Light", 5247195702222134117u, sizeof(Light), 1);
if (!initialized) {
initialized = true;
type.setDirectParentsCapacity(1);
type.addDirectParent(rfk::getArchetype<MonoBehavior::IComponent>(), static_cast<rfk::EAccessSpecifier>(1));
Light::_rfk_registerChildClass<Light>(type);
static rfk::StaticMethod defaultSharedInstantiator("", 0u, rfk::getType<rfk::SharedPtr<Light>>(),new rfk::NonMemberFunction<rfk::SharedPtr<Light>()>(&rfk::internal::CodeGenerationHelpers::defaultSharedInstantiator<Light>),rfk::EMethodFlags::Default, nullptr);
type.addSharedInstantiator(defaultSharedInstantiator);
static rfk::StaticMethod defaultUniqueInstantiator("", 0u, rfk::getType<rfk::UniquePtr<Light>>(),new rfk::NonMemberFunction<rfk::UniquePtr<Light>()>(&rfk::internal::CodeGenerationHelpers::defaultUniqueInstantiator<Light>),rfk::EMethodFlags::Default, nullptr);
type.addUniqueInstantiator(defaultUniqueInstantiator);
type.setMethodsCapacity(0u); type.setStaticMethodsCapacity(0u); 
}
return type; }

template <> rfk::Archetype const* rfk::getArchetype<MonoBehavior::Renderer::Light>() noexcept { return &MonoBehavior::Renderer::Light::staticGetArchetype(); }


