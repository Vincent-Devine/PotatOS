#pragma once

#include "../../../../../Headers/MonoBehavior/Animator.hpp"

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
 static rfk::NamespaceFragment const& getNamespaceFragment_17331560784760942515u_10962006533017881486() noexcept {
static rfk::NamespaceFragment fragment("MonoBehavior", 17331560784760942515u);
static bool initialized = false;
if (!initialized) {
initialized = true;
fragment.setNestedEntitiesCapacity(1u);
fragment.addNestedEntity(*rfk::getArchetype<MonoBehavior::Animator>());
}
return fragment; }
static rfk::NamespaceFragmentRegisterer const namespaceFragmentRegisterer_17331560784760942515u_10962006533017881486(rfk::generated::getNamespaceFragment_17331560784760942515u_10962006533017881486());
 }
rfk::Class const& MonoBehavior::Animator::staticGetArchetype() noexcept {
static bool initialized = false;
static rfk::Class type("Animator", 13925889447382351963u, sizeof(Animator), 1);
if (!initialized) {
initialized = true;
type.setDirectParentsCapacity(1);
type.addDirectParent(rfk::getArchetype<MonoBehavior::IComponent>(), static_cast<rfk::EAccessSpecifier>(1));
Animator::_rfk_registerChildClass<Animator>(type);
static rfk::StaticMethod defaultSharedInstantiator("", 0u, rfk::getType<rfk::SharedPtr<Animator>>(),new rfk::NonMemberFunction<rfk::SharedPtr<Animator>()>(&rfk::internal::CodeGenerationHelpers::defaultSharedInstantiator<Animator>),rfk::EMethodFlags::Default, nullptr);
type.addSharedInstantiator(defaultSharedInstantiator);
static rfk::StaticMethod defaultUniqueInstantiator("", 0u, rfk::getType<rfk::UniquePtr<Animator>>(),new rfk::NonMemberFunction<rfk::UniquePtr<Animator>()>(&rfk::internal::CodeGenerationHelpers::defaultUniqueInstantiator<Animator>),rfk::EMethodFlags::Default, nullptr);
type.addUniqueInstantiator(defaultUniqueInstantiator);
type.setMethodsCapacity(0u); type.setStaticMethodsCapacity(0u); 
}
return type; }

template <> rfk::Archetype const* rfk::getArchetype<MonoBehavior::Animator>() noexcept { return &MonoBehavior::Animator::staticGetArchetype(); }


