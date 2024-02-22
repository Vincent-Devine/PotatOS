#pragma once

#include "../../../../../Headers/Resource/Sound.hpp"

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
 static rfk::NamespaceFragment const& getNamespaceFragment_12715226823617554478u_15002669913124533623() noexcept {
static rfk::NamespaceFragment fragment("Resource", 12715226823617554478u);
static bool initialized = false;
if (!initialized) {
initialized = true;
fragment.setNestedEntitiesCapacity(1u);
fragment.addNestedEntity(*rfk::getArchetype<Resource::Sound>());
}
return fragment; }
static rfk::NamespaceFragmentRegisterer const namespaceFragmentRegisterer_12715226823617554478u_15002669913124533623(rfk::generated::getNamespaceFragment_12715226823617554478u_15002669913124533623());
 }
rfk::Class const& Resource::Sound::staticGetArchetype() noexcept {
static bool initialized = false;
static rfk::Class type("Sound", 8875790124069754840u, sizeof(Sound), 1);
if (!initialized) {
initialized = true;
type.setDirectParentsCapacity(1);
type.addDirectParent(rfk::getArchetype<Resource::IResource>(), static_cast<rfk::EAccessSpecifier>(1));
Sound::_rfk_registerChildClass<Sound>(type);
static rfk::StaticMethod defaultSharedInstantiator("", 0u, rfk::getType<rfk::SharedPtr<Sound>>(),new rfk::NonMemberFunction<rfk::SharedPtr<Sound>()>(&rfk::internal::CodeGenerationHelpers::defaultSharedInstantiator<Sound>),rfk::EMethodFlags::Default, nullptr);
type.addSharedInstantiator(defaultSharedInstantiator);
static rfk::StaticMethod defaultUniqueInstantiator("", 0u, rfk::getType<rfk::UniquePtr<Sound>>(),new rfk::NonMemberFunction<rfk::UniquePtr<Sound>()>(&rfk::internal::CodeGenerationHelpers::defaultUniqueInstantiator<Sound>),rfk::EMethodFlags::Default, nullptr);
type.addUniqueInstantiator(defaultUniqueInstantiator);
type.setMethodsCapacity(0u); type.setStaticMethodsCapacity(0u); 
}
return type; }

template <> rfk::Archetype const* rfk::getArchetype<Resource::Sound>() noexcept { return &Resource::Sound::staticGetArchetype(); }


