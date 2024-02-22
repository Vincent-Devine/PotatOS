#pragma once

#include "../../../../../Headers/MonoBehavior/Renderer/Camera.hpp"

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
 static rfk::NamespaceFragment const& getNamespaceFragment_14648874301494198576u_10173960374942287128() noexcept {
static rfk::NamespaceFragment fragment("Renderer", 14648874301494198576u);
static bool initialized = false;
if (!initialized) {
initialized = true;
fragment.setNestedEntitiesCapacity(1u);
fragment.addNestedEntity(*rfk::getArchetype<MonoBehavior::Renderer::Camera>());
}
return fragment; }
 static rfk::NamespaceFragment const& getNamespaceFragment_17331560784760942515u_10173960374942287128() noexcept {
static rfk::NamespaceFragment fragment("MonoBehavior", 17331560784760942515u);
static bool initialized = false;
if (!initialized) {
initialized = true;
fragment.setNestedEntitiesCapacity(1u);
fragment.addNestedEntity(rfk::generated::getNamespaceFragment_14648874301494198576u_10173960374942287128());
}
return fragment; }
static rfk::NamespaceFragmentRegisterer const namespaceFragmentRegisterer_17331560784760942515u_10173960374942287128(rfk::generated::getNamespaceFragment_17331560784760942515u_10173960374942287128());
 }
rfk::Class const& MonoBehavior::Renderer::Camera::staticGetArchetype() noexcept {
static bool initialized = false;
static rfk::Class type("Camera", 18039879834768985356u, sizeof(Camera), 1);
if (!initialized) {
initialized = true;
type.setDirectParentsCapacity(1);
type.addDirectParent(rfk::getArchetype<MonoBehavior::IComponent>(), static_cast<rfk::EAccessSpecifier>(1));
Camera::_rfk_registerChildClass<Camera>(type);
static rfk::StaticMethod defaultSharedInstantiator("", 0u, rfk::getType<rfk::SharedPtr<Camera>>(),new rfk::NonMemberFunction<rfk::SharedPtr<Camera>()>(&rfk::internal::CodeGenerationHelpers::defaultSharedInstantiator<Camera>),rfk::EMethodFlags::Default, nullptr);
type.addSharedInstantiator(defaultSharedInstantiator);
static rfk::StaticMethod defaultUniqueInstantiator("", 0u, rfk::getType<rfk::UniquePtr<Camera>>(),new rfk::NonMemberFunction<rfk::UniquePtr<Camera>()>(&rfk::internal::CodeGenerationHelpers::defaultUniqueInstantiator<Camera>),rfk::EMethodFlags::Default, nullptr);
type.addUniqueInstantiator(defaultUniqueInstantiator);
type.setMethodsCapacity(0u); type.setStaticMethodsCapacity(0u); 
}
return type; }

template <> rfk::Archetype const* rfk::getArchetype<MonoBehavior::Renderer::Camera>() noexcept { return &MonoBehavior::Renderer::Camera::staticGetArchetype(); }


