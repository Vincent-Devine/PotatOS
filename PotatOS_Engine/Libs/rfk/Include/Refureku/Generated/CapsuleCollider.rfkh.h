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


#define MonoBehavior_Physics_CapsuleCollider_GENERATED	\
RFK_UNPACK_IF_NOT_PARSING(friend rfk::internal::CodeGenerationHelpers;\
friend rfk::internal::implements_template1__rfk_registerChildClass<CapsuleCollider, void, void(rfk::Struct&)>; \
\
private: template <typename ChildClass> static void _rfk_registerChildClass(rfk::Struct& childClass) noexcept {\
rfk::Struct const& thisClass = staticGetArchetype();\
if constexpr (!std::is_same_v<ChildClass, CapsuleCollider>)const_cast<rfk::Struct&>(thisClass).addSubclass(childClass, rfk::internal::CodeGenerationHelpers::computeClassPointerOffset<ChildClass, CapsuleCollider>());\
else\
{\
childClass.setFieldsCapacity(3u + rfk::internal::CodeGenerationHelpers::getReflectedFieldsCount< MonoBehavior::Physics::Collider>()); childClass.setStaticFieldsCapacity(0u + rfk::internal::CodeGenerationHelpers::getReflectedStaticFieldsCount< MonoBehavior::Physics::Collider>()); \
}\
[[maybe_unused]] rfk::Field* field = nullptr; [[maybe_unused]] rfk::StaticField* staticField = nullptr;\
)\
__RFK_DISABLE_WARNING_PUSH \
__RFK_DISABLE_WARNING_OFFSETOF \
RFK_UNPACK_IF_NOT_PARSING(field = childClass.addField("radius", std::hash<std::string>()(std::string("c:@N@MonoBehavior@N@Physics@S@CapsuleCollider@FI@radius") + rfk::internal::getTypename<ChildClass>()), rfk::getType<float>(), static_cast<rfk::EFieldFlags>(4), offsetof(ChildClass, radius), &thisClass);\
field = childClass.addField("alignment", std::hash<std::string>()(std::string("c:@N@MonoBehavior@N@Physics@S@CapsuleCollider@FI@alignment") + rfk::internal::getTypename<ChildClass>()), rfk::getType<MonoBehavior::Physics::AXIS_ALIGNMENT>(), static_cast<rfk::EFieldFlags>(4), offsetof(ChildClass, alignment), &thisClass);\
field = childClass.addField("halfHeight", std::hash<std::string>()(std::string("c:@N@MonoBehavior@N@Physics@S@CapsuleCollider@FI@halfHeight") + rfk::internal::getTypename<ChildClass>()), rfk::getType<float>(), static_cast<rfk::EFieldFlags>(4), offsetof(ChildClass, halfHeight), &thisClass);\
)\
__RFK_DISABLE_WARNING_POP \
RFK_UNPACK_IF_NOT_PARSING(rfk::internal::CodeGenerationHelpers::registerChildClass<MonoBehavior::Physics::Collider, ChildClass>(childClass);\
}\
\
public:  static rfk::Class const& staticGetArchetype() noexcept;\
\
)\


#define File_CapsuleCollider_GENERATED	\
template <>  rfk::Archetype const* rfk::getArchetype<MonoBehavior::Physics::CapsuleCollider>() noexcept;\
template <>  rfk::Enum const* rfk::getEnum<MonoBehavior::Physics::AXIS_ALIGNMENT>() noexcept;\


