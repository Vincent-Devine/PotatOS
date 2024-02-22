#pragma once

#include "../../../../../Headers/MonoBehavior/Physics/CapsuleCollider.hpp"

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
 static rfk::NamespaceFragment const& getNamespaceFragment_1154610240384852604u_1677380214228819384() noexcept {
static rfk::NamespaceFragment fragment("Physics", 1154610240384852604u);
static bool initialized = false;
if (!initialized) {
initialized = true;
fragment.setNestedEntitiesCapacity(2u);
fragment.addNestedEntity(*rfk::getArchetype<MonoBehavior::Physics::CapsuleCollider>());
fragment.addNestedEntity(*rfk::getEnum<MonoBehavior::Physics::AXIS_ALIGNMENT>());
}
return fragment; }
 static rfk::NamespaceFragment const& getNamespaceFragment_17331560784760942515u_1677380214228819384() noexcept {
static rfk::NamespaceFragment fragment("MonoBehavior", 17331560784760942515u);
static bool initialized = false;
if (!initialized) {
initialized = true;
fragment.setNestedEntitiesCapacity(1u);
fragment.addNestedEntity(rfk::generated::getNamespaceFragment_1154610240384852604u_1677380214228819384());
}
return fragment; }
static rfk::NamespaceFragmentRegisterer const namespaceFragmentRegisterer_17331560784760942515u_1677380214228819384(rfk::generated::getNamespaceFragment_17331560784760942515u_1677380214228819384());
 }
rfk::Class const& MonoBehavior::Physics::CapsuleCollider::staticGetArchetype() noexcept {
static bool initialized = false;
static rfk::Class type("CapsuleCollider", 8263437082351771530u, sizeof(CapsuleCollider), 1);
if (!initialized) {
initialized = true;
type.setDirectParentsCapacity(1);
type.addDirectParent(rfk::getArchetype<MonoBehavior::Physics::Collider>(), static_cast<rfk::EAccessSpecifier>(1));
CapsuleCollider::_rfk_registerChildClass<CapsuleCollider>(type);
static rfk::StaticMethod defaultSharedInstantiator("", 0u, rfk::getType<rfk::SharedPtr<CapsuleCollider>>(),new rfk::NonMemberFunction<rfk::SharedPtr<CapsuleCollider>()>(&rfk::internal::CodeGenerationHelpers::defaultSharedInstantiator<CapsuleCollider>),rfk::EMethodFlags::Default, nullptr);
type.addSharedInstantiator(defaultSharedInstantiator);
static rfk::StaticMethod defaultUniqueInstantiator("", 0u, rfk::getType<rfk::UniquePtr<CapsuleCollider>>(),new rfk::NonMemberFunction<rfk::UniquePtr<CapsuleCollider>()>(&rfk::internal::CodeGenerationHelpers::defaultUniqueInstantiator<CapsuleCollider>),rfk::EMethodFlags::Default, nullptr);
type.addUniqueInstantiator(defaultUniqueInstantiator);
type.setMethodsCapacity(0u); type.setStaticMethodsCapacity(0u); 
}
return type; }

template <> rfk::Archetype const* rfk::getArchetype<MonoBehavior::Physics::CapsuleCollider>() noexcept { return &MonoBehavior::Physics::CapsuleCollider::staticGetArchetype(); }

template <> rfk::Enum const* rfk::getEnum<MonoBehavior::Physics::AXIS_ALIGNMENT>() noexcept
{
static bool initialized = false;
static rfk::Enum type("AXIS_ALIGNMENT", 5201566320764205918u, rfk::getArchetype<int>());
if (!initialized) {
initialized = true;
rfk::EnumValue* enumValue = nullptr;
type.setEnumValuesCapacity(3);
enumValue = type.addEnumValue("X", 1078739732451654726u, 0);
enumValue = type.addEnumValue("Y", 1078740831963282937u, 1);
enumValue = type.addEnumValue("Z", 1078737533428398304u, 2);
}
return &type; }

