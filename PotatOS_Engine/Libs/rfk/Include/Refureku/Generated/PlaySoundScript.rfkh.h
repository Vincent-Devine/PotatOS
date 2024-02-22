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


#define MonoBehavior_Script_PlaySoundScript_GENERATED	\
RFK_UNPACK_IF_NOT_PARSING(friend rfk::internal::CodeGenerationHelpers;\
friend rfk::internal::implements_template1__rfk_registerChildClass<PlaySoundScript, void, void(rfk::Struct&)>; \
\
private: template <typename ChildClass> static void _rfk_registerChildClass(rfk::Struct& childClass) noexcept {\
rfk::Struct const& thisClass = staticGetArchetype();\
if constexpr (!std::is_same_v<ChildClass, PlaySoundScript>)const_cast<rfk::Struct&>(thisClass).addSubclass(childClass, rfk::internal::CodeGenerationHelpers::computeClassPointerOffset<ChildClass, PlaySoundScript>());\
else\
{\
childClass.setFieldsCapacity(3u + rfk::internal::CodeGenerationHelpers::getReflectedFieldsCount< MonoBehavior::Script::BaseScript>()); childClass.setStaticFieldsCapacity(0u + rfk::internal::CodeGenerationHelpers::getReflectedStaticFieldsCount< MonoBehavior::Script::BaseScript>()); \
}\
[[maybe_unused]] rfk::Field* field = nullptr; [[maybe_unused]] rfk::StaticField* staticField = nullptr;\
)\
__RFK_DISABLE_WARNING_PUSH \
__RFK_DISABLE_WARNING_OFFSETOF \
RFK_UNPACK_IF_NOT_PARSING(field = childClass.addField("canva", std::hash<std::string>()(std::string("c:@N@MonoBehavior@N@Script@S@PlaySoundScript@FI@canva") + rfk::internal::getTypename<ChildClass>()), rfk::getType<MonoBehavior::Canva *>(), static_cast<rfk::EFieldFlags>(4), offsetof(ChildClass, canva), &thisClass);\
field = childClass.addField("audioSource", std::hash<std::string>()(std::string("c:@N@MonoBehavior@N@Script@S@PlaySoundScript@FI@audioSource") + rfk::internal::getTypename<ChildClass>()), rfk::getType<MonoBehavior::AudioSource *>(), static_cast<rfk::EFieldFlags>(4), offsetof(ChildClass, audioSource), &thisClass);\
field = childClass.addField("soundName", std::hash<std::string>()(std::string("c:@N@MonoBehavior@N@Script@S@PlaySoundScript@FI@soundName") + rfk::internal::getTypename<ChildClass>()), rfk::getType<std::string>(), static_cast<rfk::EFieldFlags>(4), offsetof(ChildClass, soundName), &thisClass);\
)\
__RFK_DISABLE_WARNING_POP \
RFK_UNPACK_IF_NOT_PARSING(rfk::internal::CodeGenerationHelpers::registerChildClass<MonoBehavior::Script::BaseScript, ChildClass>(childClass);\
}\
\
public:  static rfk::Class const& staticGetArchetype() noexcept;\
\
)\


#define File_PlaySoundScript_GENERATED	\
template <>  rfk::Archetype const* rfk::getArchetype<MonoBehavior::Script::PlaySoundScript>() noexcept;\


