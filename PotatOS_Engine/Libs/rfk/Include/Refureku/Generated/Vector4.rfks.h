#pragma once

#include "../../../../../Headers/Math/Vector4.hpp"

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
 static rfk::NamespaceFragment const& getNamespaceFragment_2309996934464676284u_13261272617846955458() noexcept {
static rfk::NamespaceFragment fragment("Math", 2309996934464676284u);
static bool initialized = false;
if (!initialized) {
initialized = true;
fragment.setNestedEntitiesCapacity(1u);
fragment.addNestedEntity(*rfk::getArchetype<Math::Vector4>());
}
return fragment; }
static rfk::NamespaceFragmentRegisterer const namespaceFragmentRegisterer_2309996934464676284u_13261272617846955458(rfk::generated::getNamespaceFragment_2309996934464676284u_13261272617846955458());
 }
rfk::Class const& Math::Vector4::staticGetArchetype() noexcept {
static bool initialized = false;
static rfk::Class type("Vector4", 15538141531843417560u, sizeof(Vector4), 1);
if (!initialized) {
initialized = true;
Vector4::_rfk_registerChildClass<Vector4>(type);
static rfk::StaticMethod defaultSharedInstantiator("", 0u, rfk::getType<rfk::SharedPtr<Vector4>>(),new rfk::NonMemberFunction<rfk::SharedPtr<Vector4>()>(&rfk::internal::CodeGenerationHelpers::defaultSharedInstantiator<Vector4>),rfk::EMethodFlags::Default, nullptr);
type.addSharedInstantiator(defaultSharedInstantiator);
static rfk::StaticMethod defaultUniqueInstantiator("", 0u, rfk::getType<rfk::UniquePtr<Vector4>>(),new rfk::NonMemberFunction<rfk::UniquePtr<Vector4>()>(&rfk::internal::CodeGenerationHelpers::defaultUniqueInstantiator<Vector4>),rfk::EMethodFlags::Default, nullptr);
type.addUniqueInstantiator(defaultUniqueInstantiator);
type.setMethodsCapacity(0u); type.setStaticMethodsCapacity(0u); 
}
return type; }

template <> rfk::Archetype const* rfk::getArchetype<Math::Vector4>() noexcept { return &Math::Vector4::staticGetArchetype(); }


