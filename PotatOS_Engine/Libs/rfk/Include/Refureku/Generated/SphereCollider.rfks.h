#pragma once

#include "../../../../../Headers/MonoBehavior/Physics/SphereCollider.hpp"

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
 static rfk::NamespaceFragment const& getNamespaceFragment_1154610240384852604u_10785458924935788390() noexcept {
static rfk::NamespaceFragment fragment("Physics", 1154610240384852604u);
static bool initialized = false;
if (!initialized) {
initialized = true;
fragment.setNestedEntitiesCapacity(1u);
fragment.addNestedEntity(*rfk::getArchetype<MonoBehavior::Physics::SphereCollider>());
}
return fragment; }
 static rfk::NamespaceFragment const& getNamespaceFragment_17331560784760942515u_10785458924935788390() noexcept {
static rfk::NamespaceFragment fragment("MonoBehavior", 17331560784760942515u);
static bool initialized = false;
if (!initialized) {
initialized = true;
fragment.setNestedEntitiesCapacity(1u);
fragment.addNestedEntity(rfk::generated::getNamespaceFragment_1154610240384852604u_10785458924935788390());
}
return fragment; }
static rfk::NamespaceFragmentRegisterer const namespaceFragmentRegisterer_17331560784760942515u_10785458924935788390(rfk::generated::getNamespaceFragment_17331560784760942515u_10785458924935788390());
 }
rfk::Class const& MonoBehavior::Physics::SphereCollider::staticGetArchetype() noexcept {
static bool initialized = false;
static rfk::Class type("SphereCollider", 1505637440603155074u, sizeof(SphereCollider), 1);
if (!initialized) {
initialized = true;
type.setDirectParentsCapacity(1);
type.addDirectParent(rfk::getArchetype<MonoBehavior::Physics::Collider>(), static_cast<rfk::EAccessSpecifier>(1));
SphereCollider::_rfk_registerChildClass<SphereCollider>(type);
static rfk::StaticMethod defaultSharedInstantiator("", 0u, rfk::getType<rfk::SharedPtr<SphereCollider>>(),new rfk::NonMemberFunction<rfk::SharedPtr<SphereCollider>()>(&rfk::internal::CodeGenerationHelpers::defaultSharedInstantiator<SphereCollider>),rfk::EMethodFlags::Default, nullptr);
type.addSharedInstantiator(defaultSharedInstantiator);
static rfk::StaticMethod defaultUniqueInstantiator("", 0u, rfk::getType<rfk::UniquePtr<SphereCollider>>(),new rfk::NonMemberFunction<rfk::UniquePtr<SphereCollider>()>(&rfk::internal::CodeGenerationHelpers::defaultUniqueInstantiator<SphereCollider>),rfk::EMethodFlags::Default, nullptr);
type.addUniqueInstantiator(defaultUniqueInstantiator);
type.setMethodsCapacity(0u); type.setStaticMethodsCapacity(0u); 
}
return type; }

template <> rfk::Archetype const* rfk::getArchetype<MonoBehavior::Physics::SphereCollider>() noexcept { return &MonoBehavior::Physics::SphereCollider::staticGetArchetype(); }


