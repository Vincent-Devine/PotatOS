#pragma once

#include "../../../../../Headers/MonoBehavior/TransitionScript.hpp"

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
 static rfk::NamespaceFragment const& getNamespaceFragment_2539190819096088051u_11555481613567460443() noexcept {
static rfk::NamespaceFragment fragment("Animation", 2539190819096088051u);
static bool initialized = false;
if (!initialized) {
initialized = true;
fragment.setNestedEntitiesCapacity(1u);
fragment.addNestedEntity(*rfk::getArchetype<DataStructure::Animation::Animation>());
}
return fragment; }
 static rfk::NamespaceFragment const& getNamespaceFragment_18329427133192430447u_11555481613567460443() noexcept {
static rfk::NamespaceFragment fragment("DataStructure", 18329427133192430447u);
static bool initialized = false;
if (!initialized) {
initialized = true;
fragment.setNestedEntitiesCapacity(1u);
fragment.addNestedEntity(rfk::generated::getNamespaceFragment_2539190819096088051u_11555481613567460443());
}
return fragment; }
static rfk::NamespaceFragmentRegisterer const namespaceFragmentRegisterer_18329427133192430447u_11555481613567460443(rfk::generated::getNamespaceFragment_18329427133192430447u_11555481613567460443());
 }
namespace rfk::generated { 
 static rfk::NamespaceFragment const& getNamespaceFragment_17331560784760942515u_11555481613567460443() noexcept {
static rfk::NamespaceFragment fragment("MonoBehavior", 17331560784760942515u);
static bool initialized = false;
if (!initialized) {
initialized = true;
}
return fragment; }
static rfk::NamespaceFragmentRegisterer const namespaceFragmentRegisterer_17331560784760942515u_11555481613567460443(rfk::generated::getNamespaceFragment_17331560784760942515u_11555481613567460443());
 }

