#pragma once

#include "../../../../../Headers/Resource/Shader.hpp"

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
 static rfk::NamespaceFragment const& getNamespaceFragment_12715226823617554478u_15556463456369713701() noexcept {
static rfk::NamespaceFragment fragment("Resource", 12715226823617554478u);
static bool initialized = false;
if (!initialized) {
initialized = true;
fragment.setNestedEntitiesCapacity(1u);
fragment.addNestedEntity(*rfk::getArchetype<Resource::Shader>());
}
return fragment; }
static rfk::NamespaceFragmentRegisterer const namespaceFragmentRegisterer_12715226823617554478u_15556463456369713701(rfk::generated::getNamespaceFragment_12715226823617554478u_15556463456369713701());
 }
rfk::Class const& Resource::Shader::staticGetArchetype() noexcept {
static bool initialized = false;
static rfk::Class type("Shader", 10409466086373000788u, sizeof(Shader), 1);
if (!initialized) {
initialized = true;
type.setDirectParentsCapacity(1);
type.addDirectParent(rfk::getArchetype<Resource::IResource>(), static_cast<rfk::EAccessSpecifier>(1));
Shader::_rfk_registerChildClass<Shader>(type);
static rfk::StaticMethod defaultSharedInstantiator("", 0u, rfk::getType<rfk::SharedPtr<Shader>>(),new rfk::NonMemberFunction<rfk::SharedPtr<Shader>()>(&rfk::internal::CodeGenerationHelpers::defaultSharedInstantiator<Shader>),rfk::EMethodFlags::Default, nullptr);
type.addSharedInstantiator(defaultSharedInstantiator);
static rfk::StaticMethod defaultUniqueInstantiator("", 0u, rfk::getType<rfk::UniquePtr<Shader>>(),new rfk::NonMemberFunction<rfk::UniquePtr<Shader>()>(&rfk::internal::CodeGenerationHelpers::defaultUniqueInstantiator<Shader>),rfk::EMethodFlags::Default, nullptr);
type.addUniqueInstantiator(defaultUniqueInstantiator);
type.setMethodsCapacity(0u); type.setStaticMethodsCapacity(0u); 
}
return type; }

template <> rfk::Archetype const* rfk::getArchetype<Resource::Shader>() noexcept { return &Resource::Shader::staticGetArchetype(); }


