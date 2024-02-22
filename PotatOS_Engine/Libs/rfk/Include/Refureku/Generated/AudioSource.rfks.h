#pragma once

#include "../../../../../Headers/MonoBehavior/AudioSource.hpp"

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
 static rfk::NamespaceFragment const& getNamespaceFragment_17331560784760942515u_16475306244504566470() noexcept {
static rfk::NamespaceFragment fragment("MonoBehavior", 17331560784760942515u);
static bool initialized = false;
if (!initialized) {
initialized = true;
fragment.setNestedEntitiesCapacity(1u);
fragment.addNestedEntity(*rfk::getArchetype<MonoBehavior::AudioSource>());
}
return fragment; }
static rfk::NamespaceFragmentRegisterer const namespaceFragmentRegisterer_17331560784760942515u_16475306244504566470(rfk::generated::getNamespaceFragment_17331560784760942515u_16475306244504566470());
 }
rfk::Class const& MonoBehavior::AudioSource::staticGetArchetype() noexcept {
static bool initialized = false;
static rfk::Class type("AudioSource", 13217370318003563649u, sizeof(AudioSource), 1);
if (!initialized) {
initialized = true;
type.setDirectParentsCapacity(1);
type.addDirectParent(rfk::getArchetype<MonoBehavior::IComponent>(), static_cast<rfk::EAccessSpecifier>(1));
AudioSource::_rfk_registerChildClass<AudioSource>(type);
static rfk::StaticMethod defaultSharedInstantiator("", 0u, rfk::getType<rfk::SharedPtr<AudioSource>>(),new rfk::NonMemberFunction<rfk::SharedPtr<AudioSource>()>(&rfk::internal::CodeGenerationHelpers::defaultSharedInstantiator<AudioSource>),rfk::EMethodFlags::Default, nullptr);
type.addSharedInstantiator(defaultSharedInstantiator);
static rfk::StaticMethod defaultUniqueInstantiator("", 0u, rfk::getType<rfk::UniquePtr<AudioSource>>(),new rfk::NonMemberFunction<rfk::UniquePtr<AudioSource>()>(&rfk::internal::CodeGenerationHelpers::defaultUniqueInstantiator<AudioSource>),rfk::EMethodFlags::Default, nullptr);
type.addUniqueInstantiator(defaultUniqueInstantiator);
type.setMethodsCapacity(0u); type.setStaticMethodsCapacity(0u); 
}
return type; }

template <> rfk::Archetype const* rfk::getArchetype<MonoBehavior::AudioSource>() noexcept { return &MonoBehavior::AudioSource::staticGetArchetype(); }


