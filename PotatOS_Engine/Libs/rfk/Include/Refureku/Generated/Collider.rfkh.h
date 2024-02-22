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


#define MonoBehavior_Physics_Collider_GENERATED	\
RFK_UNPACK_IF_NOT_PARSING(friend rfk::internal::CodeGenerationHelpers;\
friend rfk::internal::implements_template1__rfk_registerChildClass<Collider, void, void(rfk::Struct&)>; \
\
private: template <typename ChildClass> static void _rfk_registerChildClass(rfk::Struct& childClass) noexcept {\
rfk::Struct const& thisClass = staticGetArchetype();\
if constexpr (!std::is_same_v<ChildClass, Collider>)const_cast<rfk::Struct&>(thisClass).addSubclass(childClass, rfk::internal::CodeGenerationHelpers::computeClassPointerOffset<ChildClass, Collider>());\
else\
{\
childClass.setFieldsCapacity(10u + rfk::internal::CodeGenerationHelpers::getReflectedFieldsCount< MonoBehavior::IComponent>()); childClass.setStaticFieldsCapacity(0u + rfk::internal::CodeGenerationHelpers::getReflectedStaticFieldsCount< MonoBehavior::IComponent>()); \
}\
[[maybe_unused]] rfk::Field* field = nullptr; [[maybe_unused]] rfk::StaticField* staticField = nullptr;\
)\
__RFK_DISABLE_WARNING_PUSH \
__RFK_DISABLE_WARNING_OFFSETOF \
RFK_UNPACK_IF_NOT_PARSING(field = childClass.addField("lockPosX", std::hash<std::string>()(std::string("c:@N@MonoBehavior@N@Physics@S@Collider@FI@lockPosX") + rfk::internal::getTypename<ChildClass>()), rfk::getType<bool>(), static_cast<rfk::EFieldFlags>(2), offsetof(ChildClass, lockPosX), &thisClass);\
field = childClass.addField("lockPosY", std::hash<std::string>()(std::string("c:@N@MonoBehavior@N@Physics@S@Collider@FI@lockPosY") + rfk::internal::getTypename<ChildClass>()), rfk::getType<bool>(), static_cast<rfk::EFieldFlags>(2), offsetof(ChildClass, lockPosY), &thisClass);\
field = childClass.addField("lockPosZ", std::hash<std::string>()(std::string("c:@N@MonoBehavior@N@Physics@S@Collider@FI@lockPosZ") + rfk::internal::getTypename<ChildClass>()), rfk::getType<bool>(), static_cast<rfk::EFieldFlags>(2), offsetof(ChildClass, lockPosZ), &thisClass);\
field = childClass.addField("lockRotX", std::hash<std::string>()(std::string("c:@N@MonoBehavior@N@Physics@S@Collider@FI@lockRotX") + rfk::internal::getTypename<ChildClass>()), rfk::getType<bool>(), static_cast<rfk::EFieldFlags>(2), offsetof(ChildClass, lockRotX), &thisClass);\
field = childClass.addField("lockRotY", std::hash<std::string>()(std::string("c:@N@MonoBehavior@N@Physics@S@Collider@FI@lockRotY") + rfk::internal::getTypename<ChildClass>()), rfk::getType<bool>(), static_cast<rfk::EFieldFlags>(2), offsetof(ChildClass, lockRotY), &thisClass);\
field = childClass.addField("lockRotZ", std::hash<std::string>()(std::string("c:@N@MonoBehavior@N@Physics@S@Collider@FI@lockRotZ") + rfk::internal::getTypename<ChildClass>()), rfk::getType<bool>(), static_cast<rfk::EFieldFlags>(2), offsetof(ChildClass, lockRotZ), &thisClass);\
field = childClass.addField("isStatic", std::hash<std::string>()(std::string("c:@N@MonoBehavior@N@Physics@S@Collider@FI@isStatic") + rfk::internal::getTypename<ChildClass>()), rfk::getType<bool>(), static_cast<rfk::EFieldFlags>(2), offsetof(ChildClass, isStatic), &thisClass);\
field = childClass.addField("isTrigger", std::hash<std::string>()(std::string("c:@N@MonoBehavior@N@Physics@S@Collider@FI@isTrigger") + rfk::internal::getTypename<ChildClass>()), rfk::getType<bool>(), static_cast<rfk::EFieldFlags>(2), offsetof(ChildClass, isTrigger), &thisClass);\
field = childClass.addField("queryable", std::hash<std::string>()(std::string("c:@N@MonoBehavior@N@Physics@S@Collider@FI@queryable") + rfk::internal::getTypename<ChildClass>()), rfk::getType<bool>(), static_cast<rfk::EFieldFlags>(2), offsetof(ChildClass, queryable), &thisClass);\
field = childClass.addField("offset", std::hash<std::string>()(std::string("c:@N@MonoBehavior@N@Physics@S@Collider@FI@offset") + rfk::internal::getTypename<ChildClass>()), rfk::getType<Math::Vector3>(), static_cast<rfk::EFieldFlags>(2), offsetof(ChildClass, offset), &thisClass);\
)\
__RFK_DISABLE_WARNING_POP \
RFK_UNPACK_IF_NOT_PARSING(rfk::internal::CodeGenerationHelpers::registerChildClass<MonoBehavior::IComponent, ChildClass>(childClass);\
}\
\
public:  static rfk::Class const& staticGetArchetype() noexcept;\
\
)\


#define File_Collider_GENERATED	\
template <>  rfk::Archetype const* rfk::getArchetype<MonoBehavior::Physics::Collider>() noexcept;\


