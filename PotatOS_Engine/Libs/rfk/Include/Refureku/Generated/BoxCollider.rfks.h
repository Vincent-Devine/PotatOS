#pragma once

#include "../../../../../Headers/MonoBehavior/Physics/BoxCollider.hpp"

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
 static rfk::NamespaceFragment const& getNamespaceFragment_1154610240384852604u_14663151894562612072() noexcept {
static rfk::NamespaceFragment fragment("Physics", 1154610240384852604u);
static bool initialized = false;
if (!initialized) {
initialized = true;
fragment.setNestedEntitiesCapacity(1u);
fragment.addNestedEntity(*rfk::getArchetype<MonoBehavior::Physics::BoxCollider>());
}
return fragment; }
 static rfk::NamespaceFragment const& getNamespaceFragment_17331560784760942515u_14663151894562612072() noexcept {
static rfk::NamespaceFragment fragment("MonoBehavior", 17331560784760942515u);
static bool initialized = false;
if (!initialized) {
initialized = true;
fragment.setNestedEntitiesCapacity(1u);
fragment.addNestedEntity(rfk::generated::getNamespaceFragment_1154610240384852604u_14663151894562612072());
}
return fragment; }
static rfk::NamespaceFragmentRegisterer const namespaceFragmentRegisterer_17331560784760942515u_14663151894562612072(rfk::generated::getNamespaceFragment_17331560784760942515u_14663151894562612072());
 }
rfk::Class const& MonoBehavior::Physics::BoxCollider::staticGetArchetype() noexcept {
static bool initialized = false;
static rfk::Class type("BoxCollider", 7302182850149838452u, sizeof(BoxCollider), 1);
if (!initialized) {
initialized = true;
type.setDirectParentsCapacity(1);
type.addDirectParent(rfk::getArchetype<MonoBehavior::Physics::Collider>(), static_cast<rfk::EAccessSpecifier>(1));
BoxCollider::_rfk_registerChildClass<BoxCollider>(type);
static rfk::StaticMethod defaultSharedInstantiator("", 0u, rfk::getType<rfk::SharedPtr<BoxCollider>>(),new rfk::NonMemberFunction<rfk::SharedPtr<BoxCollider>()>(&rfk::internal::CodeGenerationHelpers::defaultSharedInstantiator<BoxCollider>),rfk::EMethodFlags::Default, nullptr);
type.addSharedInstantiator(defaultSharedInstantiator);
static rfk::StaticMethod defaultUniqueInstantiator("", 0u, rfk::getType<rfk::UniquePtr<BoxCollider>>(),new rfk::NonMemberFunction<rfk::UniquePtr<BoxCollider>()>(&rfk::internal::CodeGenerationHelpers::defaultUniqueInstantiator<BoxCollider>),rfk::EMethodFlags::Default, nullptr);
type.addUniqueInstantiator(defaultUniqueInstantiator);
type.setMethodsCapacity(0u); type.setStaticMethodsCapacity(0u); 
}
return type; }

template <> rfk::Archetype const* rfk::getArchetype<MonoBehavior::Physics::BoxCollider>() noexcept { return &MonoBehavior::Physics::BoxCollider::staticGetArchetype(); }


