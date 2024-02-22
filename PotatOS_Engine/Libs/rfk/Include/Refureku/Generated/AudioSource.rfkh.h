#pragma once

#include "EntityMacros.h"

#include <Refureku/TypeInfo/Entity/EEntityKind.h>
#include <string>
#include <Refureku/Misc/CodeGenerationHelpers.h>
#include <Refureku/Misc/DisableWarningMacros.h>
#include <Refureku/TypeInfo/Functions/Method.h>
#include <Refureku/TypeInfo/Functions/StaticMethod.h>
#include <Refureku/TypeInfo/Variables/Field.h>
#include <Refureku/TypeInfo/Variables/StaticField.h>
#include <Refureku/TypeInfo/Archetypes/Enum.h>
#include <Refureku/TypeInfo/Archetypes/EnumValue.h>
#include <Refureku/TypeInfo/Variables/Variable.h>
#include <Refureku/TypeInfo/Functions/Function.h>
#include <Refureku/TypeInfo/Archetypes/Template/ClassTemplate.h>
#include <Refureku/TypeInfo/Archetypes/Template/ClassTemplateInstantiation.h>
#include <Refureku/TypeInfo/Archetypes/Template/ClassTemplateInstantiationRegisterer.h>
#include <Refureku/TypeInfo/Archetypes/Template/TypeTemplateArgument.h>
#include <Refureku/TypeInfo/Archetypes/Template/NonTypeTemplateArgument.h>
#include <Refureku/TypeInfo/Archetypes/Template/TemplateTemplateArgument.h>


#define MonoBehavior_AudioSource_GENERATED	\
RFK_UNPACK_IF_NOT_PARSING(friend rfk::internal::CodeGenerationHelpers;\
friend rfk::internal::implements_template1__rfk_registerChildClass<AudioSource, void, void(rfk::Struct&)>; \
\
private: template <typename ChildClass> static void _rfk_registerChildClass(rfk::Struct& childClass) noexcept {\
rfk::Struct const& thisClass = staticGetArchetype();\
if constexpr (!std::is_same_v<ChildClass, AudioSource>)const_cast<rfk::Struct&>(thisClass).addSubclass(childClass, rfk::internal::CodeGenerationHelpers::computeClassPointerOffset<ChildClass, AudioSource>());\
else\
{\
childClass.setFieldsCapacity(6u + rfk::internal::CodeGenerationHelpers::getReflectedFieldsCount< MonoBehavior::IComponent>()); childClass.setStaticFieldsCapacity(0u + rfk::internal::CodeGenerationHelpers::getReflectedStaticFieldsCount< MonoBehavior::IComponent>()); \
}\
[[maybe_unused]] rfk::Field* field = nullptr; [[maybe_unused]] rfk::StaticField* staticField = nullptr;\
)\
__RFK_DISABLE_WARNING_PUSH \
__RFK_DISABLE_WARNING_OFFSETOF \
RFK_UNPACK_IF_NOT_PARSING(field = childClass.addField("channel", std::hash<std::string>()(std::string("c:@N@MonoBehavior@S@AudioSource@FI@channel") + rfk::internal::getTypename<ChildClass>()), rfk::getType<int>(), static_cast<rfk::EFieldFlags>(4), offsetof(ChildClass, channel), &thisClass);\
field = childClass.addField("playOnLoop", std::hash<std::string>()(std::string("c:@N@MonoBehavior@S@AudioSource@FI@playOnLoop") + rfk::internal::getTypename<ChildClass>()), rfk::getType<bool>(), static_cast<rfk::EFieldFlags>(4), offsetof(ChildClass, playOnLoop), &thisClass);\
field = childClass.addField("play", std::hash<std::string>()(std::string("c:@N@MonoBehavior@S@AudioSource@FI@play") + rfk::internal::getTypename<ChildClass>()), rfk::getType<bool>(), static_cast<rfk::EFieldFlags>(4), offsetof(ChildClass, play), &thisClass);\
field = childClass.addField("sound", std::hash<std::string>()(std::string("c:@N@MonoBehavior@S@AudioSource@FI@sound") + rfk::internal::getTypename<ChildClass>()), rfk::getType<Resource::Sound *>(), static_cast<rfk::EFieldFlags>(4), offsetof(ChildClass, sound), &thisClass);\
field = childClass.addField("minRange", std::hash<std::string>()(std::string("c:@N@MonoBehavior@S@AudioSource@FI@minRange") + rfk::internal::getTypename<ChildClass>()), rfk::getType<float>(), static_cast<rfk::EFieldFlags>(4), offsetof(ChildClass, minRange), &thisClass);\
field = childClass.addField("maxRange", std::hash<std::string>()(std::string("c:@N@MonoBehavior@S@AudioSource@FI@maxRange") + rfk::internal::getTypename<ChildClass>()), rfk::getType<float>(), static_cast<rfk::EFieldFlags>(4), offsetof(ChildClass, maxRange), &thisClass);\
)\
__RFK_DISABLE_WARNING_POP \
RFK_UNPACK_IF_NOT_PARSING(rfk::internal::CodeGenerationHelpers::registerChildClass<MonoBehavior::IComponent, ChildClass>(childClass);\
}\
\
public:  static rfk::Class const& staticGetArchetype() noexcept;\
\
)\


#define File_AudioSource_GENERATED	\
template <>  rfk::Archetype const* rfk::getArchetype<MonoBehavior::AudioSource>() noexcept;\


