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


#define MonoBehavior_Canva_GENERATED	\
RFK_UNPACK_IF_NOT_PARSING(friend rfk::internal::CodeGenerationHelpers;\
friend rfk::internal::implements_template1__rfk_registerChildClass<Canva, void, void(rfk::Struct&)>; \
\
private: template <typename ChildClass> static void _rfk_registerChildClass(rfk::Struct& childClass) noexcept {\
rfk::Struct const& thisClass = staticGetArchetype();\
if constexpr (!std::is_same_v<ChildClass, Canva>)const_cast<rfk::Struct&>(thisClass).addSubclass(childClass, rfk::internal::CodeGenerationHelpers::computeClassPointerOffset<ChildClass, Canva>());\
else\
{\
childClass.setFieldsCapacity(8u + rfk::internal::CodeGenerationHelpers::getReflectedFieldsCount< MonoBehavior::IComponent>()); childClass.setStaticFieldsCapacity(0u + rfk::internal::CodeGenerationHelpers::getReflectedStaticFieldsCount< MonoBehavior::IComponent>()); \
}\
[[maybe_unused]] rfk::Field* field = nullptr; [[maybe_unused]] rfk::StaticField* staticField = nullptr;\
)\
__RFK_DISABLE_WARNING_PUSH \
__RFK_DISABLE_WARNING_OFFSETOF \
RFK_UNPACK_IF_NOT_PARSING(field = childClass.addField("color", std::hash<std::string>()(std::string("c:@N@MonoBehavior@S@Canva@FI@color") + rfk::internal::getTypename<ChildClass>()), rfk::getType<Math::Vector4>(), static_cast<rfk::EFieldFlags>(4), offsetof(ChildClass, color), &thisClass);\
field = childClass.addField("scale", std::hash<std::string>()(std::string("c:@N@MonoBehavior@S@Canva@FI@scale") + rfk::internal::getTypename<ChildClass>()), rfk::getType<float>(), static_cast<rfk::EFieldFlags>(4), offsetof(ChildClass, scale), &thisClass);\
field = childClass.addField("posSet", std::hash<std::string>()(std::string("c:@N@MonoBehavior@S@Canva@FI@posSet") + rfk::internal::getTypename<ChildClass>()), rfk::getType<Math::Vector2>(), static_cast<rfk::EFieldFlags>(4), offsetof(ChildClass, posSet), &thisClass);\
field = childClass.addField("text", std::hash<std::string>()(std::string("c:@N@MonoBehavior@S@Canva@FI@text") + rfk::internal::getTypename<ChildClass>()), rfk::getType<std::string>(), static_cast<rfk::EFieldFlags>(4), offsetof(ChildClass, text), &thisClass);\
field = childClass.addField("isText", std::hash<std::string>()(std::string("c:@N@MonoBehavior@S@Canva@FI@isText") + rfk::internal::getTypename<ChildClass>()), rfk::getType<bool>(), static_cast<rfk::EFieldFlags>(4), offsetof(ChildClass, isText), &thisClass);\
field = childClass.addField("width", std::hash<std::string>()(std::string("c:@N@MonoBehavior@S@Canva@FI@width") + rfk::internal::getTypename<ChildClass>()), rfk::getType<float>(), static_cast<rfk::EFieldFlags>(4), offsetof(ChildClass, width), &thisClass);\
field = childClass.addField("height", std::hash<std::string>()(std::string("c:@N@MonoBehavior@S@Canva@FI@height") + rfk::internal::getTypename<ChildClass>()), rfk::getType<float>(), static_cast<rfk::EFieldFlags>(4), offsetof(ChildClass, height), &thisClass);\
field = childClass.addField("timer", std::hash<std::string>()(std::string("c:@N@MonoBehavior@S@Canva@FI@timer") + rfk::internal::getTypename<ChildClass>()), rfk::getType<float>(), static_cast<rfk::EFieldFlags>(4), offsetof(ChildClass, timer), &thisClass);\
)\
__RFK_DISABLE_WARNING_POP \
RFK_UNPACK_IF_NOT_PARSING(rfk::internal::CodeGenerationHelpers::registerChildClass<MonoBehavior::IComponent, ChildClass>(childClass);\
}\
\
public:  static rfk::Class const& staticGetArchetype() noexcept;\
\
)\


#define File_Canva_GENERATED	\
template <>  rfk::Archetype const* rfk::getArchetype<MonoBehavior::Canva>() noexcept;\


