#pragma once

#include "../../../../../Headers/DataStructure/Animation/Animation.hpp"

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
 static rfk::NamespaceFragment const& getNamespaceFragment_2539190819096088051u_6997835210246224622() noexcept {
static rfk::NamespaceFragment fragment("Animation", 2539190819096088051u);
static bool initialized = false;
if (!initialized) {
initialized = true;
fragment.setNestedEntitiesCapacity(1u);
fragment.addNestedEntity(*rfk::getArchetype<DataStructure::Animation::Animation>());
}
return fragment; }
 static rfk::NamespaceFragment const& getNamespaceFragment_18329427133192430447u_6997835210246224622() noexcept {
static rfk::NamespaceFragment fragment("DataStructure", 18329427133192430447u);
static bool initialized = false;
if (!initialized) {
initialized = true;
fragment.setNestedEntitiesCapacity(1u);
fragment.addNestedEntity(rfk::generated::getNamespaceFragment_2539190819096088051u_6997835210246224622());
}
return fragment; }
static rfk::NamespaceFragmentRegisterer const namespaceFragmentRegisterer_18329427133192430447u_6997835210246224622(rfk::generated::getNamespaceFragment_18329427133192430447u_6997835210246224622());
 }
rfk::Class const& DataStructure::Animation::Animation::staticGetArchetype() noexcept {
static bool initialized = false;
static rfk::Class type("Animation", 120390009212975656u, sizeof(Animation), 1);
if (!initialized) {
initialized = true;
Animation::_rfk_registerChildClass<Animation>(type);
static rfk::StaticMethod defaultSharedInstantiator("", 0u, rfk::getType<rfk::SharedPtr<Animation>>(),new rfk::NonMemberFunction<rfk::SharedPtr<Animation>()>(&rfk::internal::CodeGenerationHelpers::defaultSharedInstantiator<Animation>),rfk::EMethodFlags::Default, nullptr);
type.addSharedInstantiator(defaultSharedInstantiator);
static rfk::StaticMethod defaultUniqueInstantiator("", 0u, rfk::getType<rfk::UniquePtr<Animation>>(),new rfk::NonMemberFunction<rfk::UniquePtr<Animation>()>(&rfk::internal::CodeGenerationHelpers::defaultUniqueInstantiator<Animation>),rfk::EMethodFlags::Default, nullptr);
type.addUniqueInstantiator(defaultUniqueInstantiator);
type.setMethodsCapacity(0u); type.setStaticMethodsCapacity(0u); 
}
return type; }

template <> rfk::Archetype const* rfk::getArchetype<DataStructure::Animation::Animation>() noexcept { return &DataStructure::Animation::Animation::staticGetArchetype(); }


