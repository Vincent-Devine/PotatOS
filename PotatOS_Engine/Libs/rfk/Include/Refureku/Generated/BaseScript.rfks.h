#pragma once

#include "../../../../../Headers/MonoBehavior/Scripts/BaseScript.hpp"

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
 static rfk::NamespaceFragment const& getNamespaceFragment_320970643918520520u_7716049823157310638() noexcept {
static rfk::NamespaceFragment fragment("Script", 320970643918520520u);
static bool initialized = false;
if (!initialized) {
initialized = true;
fragment.setNestedEntitiesCapacity(1u);
fragment.addNestedEntity(*rfk::getArchetype<MonoBehavior::Script::BaseScript>());
}
return fragment; }
 static rfk::NamespaceFragment const& getNamespaceFragment_17331560784760942515u_7716049823157310638() noexcept {
static rfk::NamespaceFragment fragment("MonoBehavior", 17331560784760942515u);
static bool initialized = false;
if (!initialized) {
initialized = true;
fragment.setNestedEntitiesCapacity(1u);
fragment.addNestedEntity(rfk::generated::getNamespaceFragment_320970643918520520u_7716049823157310638());
}
return fragment; }
static rfk::NamespaceFragmentRegisterer const namespaceFragmentRegisterer_17331560784760942515u_7716049823157310638(rfk::generated::getNamespaceFragment_17331560784760942515u_7716049823157310638());
 }
rfk::Class const& MonoBehavior::Script::BaseScript::staticGetArchetype() noexcept {
static bool initialized = false;
static rfk::Class type("BaseScript", 9138446099993396445u, sizeof(BaseScript), 1);
if (!initialized) {
initialized = true;
type.setDirectParentsCapacity(1);
type.addDirectParent(rfk::getArchetype<MonoBehavior::IComponent>(), static_cast<rfk::EAccessSpecifier>(1));
BaseScript::_rfk_registerChildClass<BaseScript>(type);
static rfk::StaticMethod defaultSharedInstantiator("", 0u, rfk::getType<rfk::SharedPtr<BaseScript>>(),new rfk::NonMemberFunction<rfk::SharedPtr<BaseScript>()>(&rfk::internal::CodeGenerationHelpers::defaultSharedInstantiator<BaseScript>),rfk::EMethodFlags::Default, nullptr);
type.addSharedInstantiator(defaultSharedInstantiator);
static rfk::StaticMethod defaultUniqueInstantiator("", 0u, rfk::getType<rfk::UniquePtr<BaseScript>>(),new rfk::NonMemberFunction<rfk::UniquePtr<BaseScript>()>(&rfk::internal::CodeGenerationHelpers::defaultUniqueInstantiator<BaseScript>),rfk::EMethodFlags::Default, nullptr);
type.addUniqueInstantiator(defaultUniqueInstantiator);
type.setMethodsCapacity(0u); type.setStaticMethodsCapacity(0u); 
}
return type; }

template <> rfk::Archetype const* rfk::getArchetype<MonoBehavior::Script::BaseScript>() noexcept { return &MonoBehavior::Script::BaseScript::staticGetArchetype(); }


