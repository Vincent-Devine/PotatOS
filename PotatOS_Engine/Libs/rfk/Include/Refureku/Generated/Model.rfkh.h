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


#define MonoBehavior_Renderer_Model_GENERATED	\
RFK_UNPACK_IF_NOT_PARSING(friend rfk::internal::CodeGenerationHelpers;\
friend rfk::internal::implements_template1__rfk_registerChildClass<Model, void, void(rfk::Struct&)>; \
\
private: template <typename ChildClass> static void _rfk_registerChildClass(rfk::Struct& childClass) noexcept {\
rfk::Struct const& thisClass = staticGetArchetype();\
if constexpr (!std::is_same_v<ChildClass, Model>)const_cast<rfk::Struct&>(thisClass).addSubclass(childClass, rfk::internal::CodeGenerationHelpers::computeClassPointerOffset<ChildClass, Model>());\
else\
{\
childClass.setFieldsCapacity(3u + rfk::internal::CodeGenerationHelpers::getReflectedFieldsCount< MonoBehavior::IComponent>()); childClass.setStaticFieldsCapacity(0u + rfk::internal::CodeGenerationHelpers::getReflectedStaticFieldsCount< MonoBehavior::IComponent>()); \
}\
[[maybe_unused]] rfk::Field* field = nullptr; [[maybe_unused]] rfk::StaticField* staticField = nullptr;\
)\
__RFK_DISABLE_WARNING_PUSH \
__RFK_DISABLE_WARNING_OFFSETOF \
RFK_UNPACK_IF_NOT_PARSING(field = childClass.addField("shader", std::hash<std::string>()(std::string("c:@N@MonoBehavior@N@Renderer@S@Model@FI@shader") + rfk::internal::getTypename<ChildClass>()), rfk::getType<Resource::Shader *>(), static_cast<rfk::EFieldFlags>(4), offsetof(ChildClass, shader), &thisClass);\
field = childClass.addField("texture", std::hash<std::string>()(std::string("c:@N@MonoBehavior@N@Renderer@S@Model@FI@texture") + rfk::internal::getTypename<ChildClass>()), rfk::getType<Resource::Texture *>(), static_cast<rfk::EFieldFlags>(4), offsetof(ChildClass, texture), &thisClass);\
field = childClass.addField("mesh", std::hash<std::string>()(std::string("c:@N@MonoBehavior@N@Renderer@S@Model@FI@mesh") + rfk::internal::getTypename<ChildClass>()), rfk::getType<Resource::Mesh *>(), static_cast<rfk::EFieldFlags>(4), offsetof(ChildClass, mesh), &thisClass);\
)\
__RFK_DISABLE_WARNING_POP \
RFK_UNPACK_IF_NOT_PARSING(rfk::internal::CodeGenerationHelpers::registerChildClass<MonoBehavior::IComponent, ChildClass>(childClass);\
}\
\
public:  static rfk::Class const& staticGetArchetype() noexcept;\
\
)\


#define File_Model_GENERATED	\
template <>  rfk::Archetype const* rfk::getArchetype<MonoBehavior::Renderer::Model>() noexcept;\


