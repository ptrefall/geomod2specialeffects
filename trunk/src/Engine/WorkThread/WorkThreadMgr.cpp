#include "precomp.h"
#include "WorkThreadMgr.h"
#include "WorkProduction.h"

using namespace Engine;

WorkThreadMgr::WorkThreadMgr()
{
}

WorkThreadMgr::~WorkThreadMgr()
{
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
}
