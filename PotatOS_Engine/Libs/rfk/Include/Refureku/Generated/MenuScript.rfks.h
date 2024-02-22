#pragma once

#include "../../../../../Headers/MonoBehavior/Scripts/MenuScript.hpp"

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
 static rfk::NamespaceFragment const& getNamespaceFragment_320970643918520520u_1149601286309217707() noexcept {
static rfk::NamespaceFragment fragment("Script", 320970643918520520u);
static bool initialized = false;
if (!initialized) {
initialized = true;
fragment.setNestedEntitiesCapacity(1u);
fragment.addNestedEntity(*rfk::getArchetype<MonoBehavior::Script::MenuScript>());
}
return fragment; }
 static rfk::NamespaceFragment const& getNamespaceFragment_17331560784760942515u_1149601286309217707() noexcept {
static rfk::NamespaceFragment fragment("MonoBehavior", 17331560784760942515u);
static bool initialized = false;
if (!initialized) {
initialized = true;
fragment.setNestedEntitiesCapacity(1u);
fragment.addNestedEntity(rfk::generated::getNamespaceFragment_320970643918520520u_1149601286309217707());
}
return fragment; }
static rfk::NamespaceFragmentRegisterer const namespaceFragmentRegisterer_17331560784760942515u_1149601286309217707(rfk::generated::getNamespaceFragment_17331560784760942515u_1149601286309217707());
 }
rfk::Class const& MonoBehavior::Script::MenuScript::staticGetArchetype() noexcept {
static bool initialized = false;
static rfk::Class type("MenuScript", 9089891155077521391u, sizeof(MenuScript), 1);
if (!initialized) {
initialized = true;
type.setDirectParentsCapacity(1);
type.addDirectParent(rfk::getArchetype<MonoBehavior::Script::BaseScript>(), static_cast<rfk::EAccessSpecifier>(1));
MenuScript::_rfk_registerChildClass<MenuScript>(type);
static rfk::StaticMethod defaultSharedInstantiator("", 0u, rfk::getType<rfk::SharedPtr<MenuScript>>(),new rfk::NonMemberFunction<rfk::SharedPtr<MenuScript>()>(&rfk::internal::CodeGenerationHelpers::defaultSharedInstantiator<MenuScript>),rfk::EMethodFlags::Default, nullptr);
type.addSharedInstantiator(defaultSharedInstantiator);
static rfk::StaticMethod defaultUniqueInstantiator("", 0u, rfk::getType<rfk::UniquePtr<MenuScript>>(),new rfk::NonMemberFunction<rfk::UniquePtr<MenuScript>()>(&rfk::internal::CodeGenerationHelpers::defaultUniqueInstantiator<MenuScript>),rfk::EMethodFlags::Default, nullptr);
type.addUniqueInstantiator(defaultUniqueInstantiator);
type.setMethodsCapacity(0u); type.setStaticMethodsCapacity(0u); 
}
return type; }

template <> rfk::Archetype const* rfk::getArchetype<MonoBehavior::Script::MenuScript>() noexcept { return &MonoBehavior::Script::MenuScript::staticGetArchetype(); }


