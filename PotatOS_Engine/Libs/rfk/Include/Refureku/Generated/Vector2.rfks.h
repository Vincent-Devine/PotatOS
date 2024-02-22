#pragma once

#include "../../../../../Headers/Math/Vector2.hpp"

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
 static rfk::NamespaceFragment const& getNamespaceFragment_2309996934464676284u_12383869962632669176() noexcept {
static rfk::NamespaceFragment fragment("Math", 2309996934464676284u);
static bool initialized = false;
if (!initialized) {
initialized = true;
fragment.setNestedEntitiesCapacity(1u);
fragment.addNestedEntity(*rfk::getArchetype<Math::Vector2>());
}
return fragment; }
static rfk::NamespaceFragmentRegisterer const namespaceFragmentRegisterer_2309996934464676284u_12383869962632669176(rfk::generated::getNamespaceFragment_2309996934464676284u_12383869962632669176());
 }
rfk::Class const& Math::Vector2::staticGetArchetype() noexcept {
static bool initialized = false;
static rfk::Class type("Vector2", 15538148128913186826u, sizeof(Vector2), 1);
if (!initialized) {
initialized = true;
Vector2::_rfk_registerChildClass<Vector2>(type);
static rfk::StaticMethod defaultSharedInstantiator("", 0u, rfk::getType<rfk::SharedPtr<Vector2>>(),new rfk::NonMemberFunction<rfk::SharedPtr<Vector2>()>(&rfk::internal::CodeGenerationHelpers::defaultSharedInstantiator<Vector2>),rfk::EMethodFlags::Default, nullptr);
type.addSharedInstantiator(defaultSharedInstantiator);
static rfk::StaticMethod defaultUniqueInstantiator("", 0u, rfk::getType<rfk::UniquePtr<Vector2>>(),new rfk::NonMemberFunction<rfk::UniquePtr<Vector2>()>(&rfk::internal::CodeGenerationHelpers::defaultUniqueInstantiator<Vector2>),rfk::EMethodFlags::Default, nullptr);
type.addUniqueInstantiator(defaultUniqueInstantiator);
type.setMethodsCapacity(0u); type.setStaticMethodsCapacity(0u); 
}
return type; }

template <> rfk::Archetype const* rfk::getArchetype<Math::Vector2>() noexcept { return &Math::Vector2::staticGetArchetype(); }


