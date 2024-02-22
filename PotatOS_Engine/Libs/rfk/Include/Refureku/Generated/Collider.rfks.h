#pragma once

#include "../../../../../Headers/MonoBehavior/Physics/Collider.hpp"

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
 static rfk::NamespaceFragment const& getNamespaceFragment_1154610240384852604u_15828889196514489680() noexcept {
static rfk::NamespaceFragment fragment("Physics", 1154610240384852604u);
static bool initialized = false;
if (!initialized) {
initialized = true;
fragment.setNestedEntitiesCapacity(1u);
fragment.addNestedEntity(*rfk::getArchetype<MonoBehavior::Physics::Collider>());
}
return fragment; }
 static rfk::NamespaceFragment const& getNamespaceFragment_17331560784760942515u_15828889196514489680() noexcept {
static rfk::NamespaceFragment fragment("MonoBehavior", 17331560784760942515u);
static bool initialized = false;
if (!initialized) {
initialized = true;
fragment.setNestedEntitiesCapacity(1u);
fragment.addNestedEntity(rfk::generated::getNamespaceFragment_1154610240384852604u_15828889196514489680());
}
return fragment; }
static rfk::NamespaceFragmentRegisterer const namespaceFragmentRegisterer_17331560784760942515u_15828889196514489680(rfk::generated::getNamespaceFragment_17331560784760942515u_15828889196514489680());
 }
rfk::Class const& MonoBehavior::Physics::Collider::staticGetArchetype() noexcept {
static bool initialized = false;
static rfk::Class type("Collider", 11571723746220747843u, sizeof(Collider), 1);
if (!initialized) {
initialized = true;
type.setDirectParentsCapacity(1);
type.addDirectParent(rfk::getArchetype<MonoBehavior::IComponent>(), static_cast<rfk::EAccessSpecifier>(1));
Collider::_rfk_registerChildClass<Collider>(type);
static rfk::StaticMethod defaultSharedInstantiator("", 0u, rfk::getType<rfk::SharedPtr<Collider>>(),new rfk::NonMemberFunction<rfk::SharedPtr<Collider>()>(&rfk::internal::CodeGenerationHelpers::defaultSharedInstantiator<Collider>),rfk::EMethodFlags::Default, nullptr);
type.addSharedInstantiator(defaultSharedInstantiator);
static rfk::StaticMethod defaultUniqueInstantiator("", 0u, rfk::getType<rfk::UniquePtr<Collider>>(),new rfk::NonMemberFunction<rfk::UniquePtr<Collider>()>(&rfk::internal::CodeGenerationHelpers::defaultUniqueInstantiator<Collider>),rfk::EMethodFlags::Default, nullptr);
type.addUniqueInstantiator(defaultUniqueInstantiator);
type.setMethodsCapacity(0u); type.setStaticMethodsCapacity(0u); 
}
return type; }

template <> rfk::Archetype const* rfk::getArchetype<MonoBehavior::Physics::Collider>() noexcept { return &MonoBehavior::Physics::Collider::staticGetArchetype(); }


