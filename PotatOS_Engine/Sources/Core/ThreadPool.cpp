#include "pch.h"

#include <Core/ThreadPool.hpp>

namespace Core
{
	ThreadPool* ThreadPool::singleton = nullptr;

	ThreadPool* ThreadPool::Get()
	{
		if (singleton == nullptr)
		{
			singleton = new ThreadPool;
		}
		return singleton;
	}

	void ThreadPool::Init(unsigned int p_nbThread)
	{
		loadItem = 0;
		threads.resize(p_nbThread);
		for (unsigned int i = 0; i < p_nbThread; i++)
		{
			threads[i] = std::thread();
		}
	}

	void ThreadPool::Update()
	{
		if (resourcesToInit.size() != 0)
		{
			for (unsigned int i = 0; i < threads.size(); i++)
			{
				if (!threads.at(i).joinable())
				{
					threads.at(i) = std::thread(&ThreadPool::InitResource, singleton);
					threads.at(i).detach();
				}
			}
		}

		while (resourcesToInitRHI.size() != 0)
		{
			if (mutexResourcesToInitRHI.try_lock())
			{
				if (resourcesToInitRHI.empty())
				{
					continue;
				}
				resourcesToInitRHI.front()->InitRHI();
				resourcesToInitRHI.pop();
				mutexResourcesToInitRHI.unlock();
				loadItem--;
			}
		}
	}

	void ThreadPool::Delete()
	{
		for (unsigned int i = 0; i < threads.size(); i++)
		{
			if (threads.at(i).joinable())
			{
				threads.at(i).join();
			}
		}
	}

	bool ThreadPool::FinishLoad()
	{
		if (resourcesToInitRHI.empty() && resourcesToInit.empty() && loadItem == 0)
		{
			return true;
		}
		return false;
	}

	void ThreadPool::AddResourceToInit(Resource::IResource* p_resource)
	{
		singleton->resourcesToInit.push(p_resource);
	}

	void ThreadPool::InitResource()
	{
		while (resourcesToInit.size() != 0)
		{
			if (mutexResourcesToInit.try_lock())
			{
				if (resourcesToInit.empty())
				{
					continue;
				}
				Resource::IResource* resource = resourcesToInit.front();
				loadItem++;
				resourcesToInit.pop();
				mutexResourcesToInit.unlock();

				resource->Init();

				bool addedToInitRHIQueue = false;
				while (!addedToInitRHIQueue)
				{
					if (mutexResourcesToInitRHI.try_lock())
					{
						resourcesToInitRHI.push(resource);
						mutexResourcesToInitRHI.unlock();
						addedToInitRHIQueue = true;
					}
				}
			}
		}
	}
}
