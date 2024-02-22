#pragma once

#include "../../../../../Headers/Resource/IResource.hpp"

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
 static rfk::NamespaceFragment const& getNamespaceFragment_12715226823617554478u_9180296918561925874() noexcept {
static rfk::NamespaceFragment fragment("Resource", 12715226823617554478u);
static bool initialized = false;
if (!initialized) {
initialized = true;
fragment.setNestedEntitiesCapacity(1u);
fragment.addNestedEntity(*rfk::getArchetype<Resource::IResource>());
}
return fragment; }
static rfk::NamespaceFragmentRegisterer const namespaceFragmentRegisterer_12715226823617554478u_9180296918561925874(rfk::generated::getNamespaceFragment_12715226823617554478u_9180296918561925874());
 }
rfk::Class const& Resource::IResource::staticGetArchetype() noexcept {
static bool initialized = false;
static rfk::Class type("IResource", 18070731500118512892u, sizeof(IResource), 1);
if (!initialized) {
initialized = true;
IResource::_rfk_registerChildClass<IResource>(type);
static rfk::StaticMethod defaultSharedInstantiator("", 0u, rfk::getType<rfk::SharedPtr<IResource>>(),new rfk::NonMemberFunction<rfk::SharedPtr<IResource>()>(&rfk::internal::CodeGenerationHelpers::defaultSharedInstantiator<IResource>),rfk::EMethodFlags::Default, nullptr);
type.addSharedInstantiator(defaultSharedInstantiator);
static rfk::StaticMethod defaultUniqueInstantiator("", 0u, rfk::getType<rfk::UniquePtr<IResource>>(),new rfk::NonMemberFunction<rfk::UniquePtr<IResource>()>(&rfk::internal::CodeGenerationHelpers::defaultUniqueInstantiator<IResource>),rfk::EMethodFlags::Default, nullptr);
type.addUniqueInstantiator(defaultUniqueInstantiator);
type.setMethodsCapacity(0u); type.setStaticMethodsCapacity(0u); 
}
return type; }

template <> rfk::Archetype const* rfk::getArchetype<Resource::IResource>() noexcept { return &Resource::IResource::staticGetArchetype(); }


