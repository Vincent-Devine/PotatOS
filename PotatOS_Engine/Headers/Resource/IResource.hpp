#pragma once

#include <DLLInclude.hpp>
#include <string>

#include <Refureku/Refureku.h>
#include <Refureku/Generated/IResource.rfkh.h>

namespace Resource RFKNamespace()
{
	class RFKClass() POTATOS_ENGINE_API IResource
	{
	// Attributes
	protected:
		RFKField()
		std::string path = "";

		std::string name = "";
		int id = -1;
		bool isFinishToInit = false;
		unsigned int usedBy = 0;

	// Methods
	public:
		virtual ~IResource() {};

		virtual const bool Init() { CreateName(); return true; };
		virtual const bool InitRHI() { return true; };

		virtual void Unload() {};

		virtual void StartUsing() { usedBy++; };
		virtual void StopUsing() { usedBy--; };

		virtual const std::string& GetPath() const { return path; };
		virtual const std::string& GetName() const { return name; };
		virtual const bool GetIsFinishToInit() const { return isFinishToInit; };
		virtual const unsigned int GetUsedBy() const { return usedBy; };

	protected:
		virtual void CreateName();

		Resource_IResource_GENERATED
	};
}
File_IResource_GENERATED
