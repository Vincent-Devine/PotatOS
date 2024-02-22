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


#define MonoBehavior_Renderer_SpotLight_GENERATED	\
RFK_UNPACK_IF_NOT_PARSING(friend rfk::internal::CodeGenerationHelpers;\
friend rfk::internal::implements_template1__rfk_registerChildClass<SpotLight, void, void(rfk::Struct&)>; \
\
private: template <typename ChildClass> static void _rfk_registerChildClass(rfk::Struct& childClass) noexcept {\
rfk::Struct const& thisClass = staticGetArchetype();\
if constexpr (!std::is_same_v<ChildClass, SpotLight>)const_cast<rfk::Struct&>(thisClass).addSubclass(childClass, rfk::internal::CodeGenerationHelpers::computeClassPointerOffset<ChildClass, SpotLight>());\
else\
{\
childClass.setFieldsCapacity(6u + rfk::internal::CodeGenerationHelpers::getReflectedFieldsCount< MonoBehavior::Renderer::Light>()); childClass.setStaticFieldsCapacity(0u + rfk::internal::CodeGenerationHelpers::getReflectedStaticFieldsCount< MonoBehavior::Renderer::Light>()); \
}\
[[maybe_unused]] rfk::Field* field = nullptr; [[maybe_unused]] rfk::StaticField* staticField = nullptr;\
)\
__RFK_DISABLE_WARNING_PUSH \
__RFK_DISABLE_WARNING_OFFSETOF \
RFK_UNPACK_IF_NOT_PARSING(field = childClass.addField("direction", std::hash<std::string>()(std::string("c:@N@MonoBehavior@N@Renderer@S@SpotLight@FI@direction") + rfk::internal::getTypename<ChildClass>()), rfk::getType<Math::Vector3>(), static_cast<rfk::EFieldFlags>(4), offsetof(ChildClass, direction), &thisClass);\
field = childClass.addField("cutOff", std::hash<std::string>()(std::string("c:@N@MonoBehavior@N@Renderer@S@SpotLight@FI@cutOff") + rfk::internal::getTypename<ChildClass>()), rfk::getType<float>(), static_cast<rfk::EFieldFlags>(4), offsetof(ChildClass, cutOff), &thisClass);\
field = childClass.addField("outerCutOff", std::hash<std::string>()(std::string("c:@N@MonoBehavior@N@Renderer@S@SpotLight@FI@outerCutOff") + rfk::internal::getTypename<ChildClass>()), rfk::getType<float>(), static_cast<rfk::EFieldFlags>(4), offsetof(ChildClass, outerCutOff), &thisClass);\
field = childClass.addField("constant", std::hash<std::string>()(std::string("c:@N@MonoBehavior@N@Renderer@S@SpotLight@FI@constant") + rfk::internal::getTypename<ChildClass>()), rfk::getType<float>(), static_cast<rfk::EFieldFlags>(4), offsetof(ChildClass, constant), &thisClass);\
field = childClass.addField("linear", std::hash<std::string>()(std::string("c:@N@MonoBehavior@N@Renderer@S@SpotLight@FI@linear") + rfk::internal::getTypename<ChildClass>()), rfk::getType<float>(), static_cast<rfk::EFieldFlags>(4), offsetof(ChildClass, linear), &thisClass);\
field = childClass.addField("quadratic", std::hash<std::string>()(std::string("c:@N@MonoBehavior@N@Renderer@S@SpotLight@FI@quadratic") + rfk::internal::getTypename<ChildClass>()), rfk::getType<float>(), static_cast<rfk::EFieldFlags>(4), offsetof(ChildClass, quadratic), &thisClass);\
)\
__RFK_DISABLE_WARNING_POP \
RFK_UNPACK_IF_NOT_PARSING(rfk::internal::CodeGenerationHelpers::registerChildClass<MonoBehavior::Renderer::Light, ChildClass>(childClass);\
}\
\
public:  static rfk::Class const& staticGetArchetype() noexcept;\
\
)\


#define File_SpotLight_GENERATED	\
template <>  rfk::Archetype const* rfk::getArchetype<MonoBehavior::Renderer::SpotLight>() noexcept;\


