#pragma once

#include <atomic>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>

#include <DebugSystem/Assertion.hpp>
#include <Resource/IResource.hpp>

namespace Core
{
	class ThreadPool
	{
	// Attributes
	private:
		static ThreadPool* singleton;

		std::queue<Resource::IResource*> resourcesToInit;
		std::queue<Resource::IResource*> resourcesToInitRHI;
		std::vector<std::thread> threads;

		std::mutex mutexResourcesToInit;
		std::mutex mutexResourcesToInitRHI;

		int loadItem;

	// Methods
	public:
		static ThreadPool* Get();

		void Init(unsigned int p_nbThread = std::thread::hardware_concurrency());
		void Update();
		void Delete();

		bool FinishLoad();

		static void AddResourceToInit(Resource::IResource* p_resource);

	private:
		void InitResource();
	};
}
