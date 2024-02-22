#pragma once

#include "../../../../../Headers/MonoBehavior/Physics/PlaneCollider.hpp"

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
 static rfk::NamespaceFragment const& getNamespaceFragment_1154610240384852604u_18440221682068827657() noexcept {
static rfk::NamespaceFragment fragment("Physics", 1154610240384852604u);
static bool initialized = false;
if (!initialized) {
initialized = true;
fragment.setNestedEntitiesCapacity(1u);
fragment.addNestedEntity(*rfk::getArchetype<MonoBehavior::Physics::PlaneCollider>());
}
return fragment; }
 static rfk::NamespaceFragment const& getNamespaceFragment_17331560784760942515u_18440221682068827657() noexcept {
static rfk::NamespaceFragment fragment("MonoBehavior", 17331560784760942515u);
static bool initialized = false;
if (!initialized) {
initialized = true;
fragment.setNestedEntitiesCapacity(1u);
fragment.addNestedEntity(rfk::generated::getNamespaceFragment_1154610240384852604u_18440221682068827657());
}
return fragment; }
static rfk::NamespaceFragmentRegisterer const namespaceFragmentRegisterer_17331560784760942515u_18440221682068827657(rfk::generated::getNamespaceFragment_17331560784760942515u_18440221682068827657());
 }
rfk::Class const& MonoBehavior::Physics::PlaneCollider::staticGetArchetype() noexcept {
static bool initialized = false;
static rfk::Class type("PlaneCollider", 3042372356527794411u, sizeof(PlaneCollider), 1);
if (!initialized) {
initialized = true;
type.setDirectParentsCapacity(1);
type.addDirectParent(rfk::getArchetype<MonoBehavior::Physics::Collider>(), static_cast<rfk::EAccessSpecifier>(1));
PlaneCollider::_rfk_registerChildClass<PlaneCollider>(type);
static rfk::StaticMethod defaultSharedInstantiator("", 0u, rfk::getType<rfk::SharedPtr<PlaneCollider>>(),new rfk::NonMemberFunction<rfk::SharedPtr<PlaneCollider>()>(&rfk::internal::CodeGenerationHelpers::defaultSharedInstantiator<PlaneCollider>),rfk::EMethodFlags::Default, nullptr);
type.addSharedInstantiator(defaultSharedInstantiator);
static rfk::StaticMethod defaultUniqueInstantiator("", 0u, rfk::getType<rfk::UniquePtr<PlaneCollider>>(),new rfk::NonMemberFunction<rfk::UniquePtr<PlaneCollider>()>(&rfk::internal::CodeGenerationHelpers::defaultUniqueInstantiator<PlaneCollider>),rfk::EMethodFlags::Default, nullptr);
type.addUniqueInstantiator(defaultUniqueInstantiator);
type.setMethodsCapacity(0u); type.setStaticMethodsCapacity(0u); 
}
return type; }

template <> rfk::Archetype const* rfk::getArchetype<MonoBehavior::Physics::PlaneCollider>() noexcept { return &MonoBehavior::Physics::PlaneCollider::staticGetArchetype(); }


