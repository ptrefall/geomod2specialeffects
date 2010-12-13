#include "precomp.h"
#include "WorkThreadMgr.h"
#include "WorkProduction.h"
#include "Worker.h"
#include "WorkProducer.h"

using namespace Engine;

WorkThreadMgr::WorkThreadMgr(CoreMgr *coreMgr)
: coreMgr(coreMgr)
{
	for(unsigned int core = 0; core < (unsigned int)CL_System::get_num_cores(); core++)
	{
		work_for_worker.push_back(CL_Event());
		workers.push_back(new Worker(coreMgr, core, work_for_worker[core]));
	}
}

WorkThreadMgr::~WorkThreadMgr()
{
}

void WorkThreadMgr::update(float dt)
{
	assignWork();
}

bool WorkThreadMgr::isWorkGroupCompletedFor(WorkProducer *producer)
{
	std::map<WorkProducer*, WorkProduction*>::iterator it = produce.find(producer);
	if(it == produce.end())
		return false;

	if(it->second->isDone())
		return true;
	else
		return false;
}

WorkDoneData *WorkThreadMgr::getWorkGroupDoneData(WorkProducer *producer)
{
	std::map<WorkProducer*, WorkProduction*>::iterator it = produce.find(producer);
	if(it == produce.end())
		return NULL;

	return it->second->getDoneData();
}

void WorkThreadMgr::addWorkGroup(WorkProducer *producer, std::vector<WorkData*> work_group, WorkDoneData *doneData)
{
	std::map<WorkProducer*, WorkProduction*>::iterator it = produce.find(producer);
	if(it != produce.end())
		return;

	produce[producer] = new WorkProduction(work_group, doneData);

	assignWork();
}

void WorkThreadMgr::assignWork()
{
	std::map<WorkProducer*, WorkProduction*>::iterator it = produce.begin();
	for(; it != produce.end(); ++it)
	{
		if(it->second->isDone())
		{
			it->first->finished(it->second->getDoneData());
			produce.erase(it);
			
			if(produce.empty())
				return;

			it = produce.begin();
			continue;
		}

		for(unsigned int i = 0; i < it->second->getWorkDataSize(); i++)
		{
			if(it->second->isUnderWork(i) == false)
			{
				int foundWorker = -1;
				for(unsigned int core = 0; core < workers.size(); core++)
				{
					if(workers[core]->isAtWork() == false)
					{
						foundWorker = core;
						break;
					}
				}

				if(foundWorker > -1)
				{
					it->second->setUnderWork(i);
					workers[foundWorker]->setToWork(it->first, it->second->getWorkData(i), i);
					work_for_worker[foundWorker].set();
					continue;
				}
			}
		}
	}
}

void WorkThreadMgr::finishedWork(WorkProducer *producer, unsigned int index)
{
	std::map<WorkProducer*, WorkProduction*>::iterator it = produce.find(producer);
	if(it == produce.end())
		throw CL_Exception("Couldn't find producer of finished work!");

	it->second->setFinishedWork(index);
}
