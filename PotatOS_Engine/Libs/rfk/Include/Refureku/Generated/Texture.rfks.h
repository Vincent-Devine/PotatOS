#pragma once

#include "../../../../../Headers/Resource/Texture.hpp"

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
 static rfk::NamespaceFragment const& getNamespaceFragment_12715226823617554478u_12467684447619658779() noexcept {
static rfk::NamespaceFragment fragment("Resource", 12715226823617554478u);
static bool initialized = false;
if (!initialized) {
initialized = true;
fragment.setNestedEntitiesCapacity(1u);
fragment.addNestedEntity(*rfk::getArchetype<Resource::Texture>());
}
return fragment; }
static rfk::NamespaceFragmentRegisterer const namespaceFragmentRegisterer_12715226823617554478u_12467684447619658779(rfk::generated::getNamespaceFragment_12715226823617554478u_12467684447619658779());
 }
rfk::Class const& Resource::Texture::staticGetArchetype() noexcept {
static bool initialized = false;
static rfk::Class type("Texture", 6019260955415814640u, sizeof(Texture), 1);
if (!initialized) {
initialized = true;
type.setDirectParentsCapacity(1);
type.addDirectParent(rfk::getArchetype<Resource::IResource>(), static_cast<rfk::EAccessSpecifier>(1));
Texture::_rfk_registerChildClass<Texture>(type);
static rfk::StaticMethod defaultSharedInstantiator("", 0u, rfk::getType<rfk::SharedPtr<Texture>>(),new rfk::NonMemberFunction<rfk::SharedPtr<Texture>()>(&rfk::internal::CodeGenerationHelpers::defaultSharedInstantiator<Texture>),rfk::EMethodFlags::Default, nullptr);
type.addSharedInstantiator(defaultSharedInstantiator);
static rfk::StaticMethod defaultUniqueInstantiator("", 0u, rfk::getType<rfk::UniquePtr<Texture>>(),new rfk::NonMemberFunction<rfk::UniquePtr<Texture>()>(&rfk::internal::CodeGenerationHelpers::defaultUniqueInstantiator<Texture>),rfk::EMethodFlags::Default, nullptr);
type.addUniqueInstantiator(defaultUniqueInstantiator);
type.setMethodsCapacity(0u); type.setStaticMethodsCapacity(0u); 
}
return type; }

template <> rfk::Archetype const* rfk::getArchetype<Resource::Texture>() noexcept { return &Resource::Texture::staticGetArchetype(); }


