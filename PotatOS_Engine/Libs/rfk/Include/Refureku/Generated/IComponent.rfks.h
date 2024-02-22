#pragma once

#include "../../../../../Headers/MonoBehavior/IComponent.hpp"

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
 static rfk::NamespaceFragment const& getNamespaceFragment_18329427133192430447u_3445175413531323718() noexcept {
static rfk::NamespaceFragment fragment("DataStructure", 18329427133192430447u);
static bool initialized = false;
if (!initialized) {
initialized = true;
}
return fragment; }
static rfk::NamespaceFragmentRegisterer const namespaceFragmentRegisterer_18329427133192430447u_3445175413531323718(rfk::generated::getNamespaceFragment_18329427133192430447u_3445175413531323718());
 }
namespace rfk::generated { 
 static rfk::NamespaceFragment const& getNamespaceFragment_14648874301494198576u_3445175413531323718() noexcept {
static rfk::NamespaceFragment fragment("Renderer", 14648874301494198576u);
static bool initialized = false;
if (!initialized) {
initialized = true;
}
return fragment; }
 static rfk::NamespaceFragment const& getNamespaceFragment_17331560784760942515u_3445175413531323718() noexcept {
static rfk::NamespaceFragment fragment("MonoBehavior", 17331560784760942515u);
static bool initialized = false;
if (!initialized) {
initialized = true;
fragment.setNestedEntitiesCapacity(2u);
fragment.addNestedEntity(rfk::generated::getNamespaceFragment_14648874301494198576u_3445175413531323718());
fragment.addNestedEntity(*rfk::getArchetype<MonoBehavior::IComponent>());
}
return fragment; }
static rfk::NamespaceFragmentRegisterer const namespaceFragmentRegisterer_17331560784760942515u_3445175413531323718(rfk::generated::getNamespaceFragment_17331560784760942515u_3445175413531323718());
 }
rfk::Class const& MonoBehavior::IComponent::staticGetArchetype() noexcept {
static bool initialized = false;
static rfk::Class type("IComponent", 4650650107024705332u, sizeof(IComponent), 1);
if (!initialized) {
initialized = true;
IComponent::_rfk_registerChildClass<IComponent>(type);
static rfk::StaticMethod defaultSharedInstantiator("", 0u, rfk::getType<rfk::SharedPtr<IComponent>>(),new rfk::NonMemberFunction<rfk::SharedPtr<IComponent>()>(&rfk::internal::CodeGenerationHelpers::defaultSharedInstantiator<IComponent>),rfk::EMethodFlags::Default, nullptr);
type.addSharedInstantiator(defaultSharedInstantiator);
static rfk::StaticMethod defaultUniqueInstantiator("", 0u, rfk::getType<rfk::UniquePtr<IComponent>>(),new rfk::NonMemberFunction<rfk::UniquePtr<IComponent>()>(&rfk::internal::CodeGenerationHelpers::defaultUniqueInstantiator<IComponent>),rfk::EMethodFlags::Default, nullptr);
type.addUniqueInstantiator(defaultUniqueInstantiator);
type.setMethodsCapacity(0u); type.setStaticMethodsCapacity(0u); 
}
return type; }

template <> rfk::Archetype const* rfk::getArchetype<MonoBehavior::IComponent>() noexcept { return &MonoBehavior::IComponent::staticGetArchetype(); }


