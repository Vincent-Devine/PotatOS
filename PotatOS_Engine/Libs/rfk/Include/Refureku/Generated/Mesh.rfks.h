#pragma once

#include "../../../../../Headers/Resource/Mesh.hpp"

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
 static rfk::NamespaceFragment const& getNamespaceFragment_12715226823617554478u_663141591883837158() noexcept {
static rfk::NamespaceFragment fragment("Resource", 12715226823617554478u);
static bool initialized = false;
if (!initialized) {
initialized = true;
fragment.setNestedEntitiesCapacity(1u);
fragment.addNestedEntity(*rfk::getArchetype<Resource::Mesh>());
}
return fragment; }
static rfk::NamespaceFragmentRegisterer const namespaceFragmentRegisterer_12715226823617554478u_663141591883837158(rfk::generated::getNamespaceFragment_12715226823617554478u_663141591883837158());
 }
rfk::Class const& Resource::Mesh::staticGetArchetype() noexcept {
static bool initialized = false;
static rfk::Class type("Mesh", 11781669490123998296u, sizeof(Mesh), 1);
if (!initialized) {
initialized = true;
type.setDirectParentsCapacity(1);
type.addDirectParent(rfk::getArchetype<Resource::IResource>(), static_cast<rfk::EAccessSpecifier>(1));
Mesh::_rfk_registerChildClass<Mesh>(type);
static rfk::StaticMethod defaultSharedInstantiator("", 0u, rfk::getType<rfk::SharedPtr<Mesh>>(),new rfk::NonMemberFunction<rfk::SharedPtr<Mesh>()>(&rfk::internal::CodeGenerationHelpers::defaultSharedInstantiator<Mesh>),rfk::EMethodFlags::Default, nullptr);
type.addSharedInstantiator(defaultSharedInstantiator);
static rfk::StaticMethod defaultUniqueInstantiator("", 0u, rfk::getType<rfk::UniquePtr<Mesh>>(),new rfk::NonMemberFunction<rfk::UniquePtr<Mesh>()>(&rfk::internal::CodeGenerationHelpers::defaultUniqueInstantiator<Mesh>),rfk::EMethodFlags::Default, nullptr);
type.addUniqueInstantiator(defaultUniqueInstantiator);
type.setMethodsCapacity(0u); type.setStaticMethodsCapacity(0u); 
}
return type; }

template <> rfk::Archetype const* rfk::getArchetype<Resource::Mesh>() noexcept { return &Resource::Mesh::staticGetArchetype(); }


