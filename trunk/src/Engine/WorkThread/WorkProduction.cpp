#include "precomp.h"
#include "WorkProduction.h"

using namespace Engine;

WorkProduction::WorkProduction(const std::vector<WorkData*> &work, WorkDoneData *doneData)
: done(false)
{
	this->work = work;
	this->doneData = doneData;

	for(unsigned int i = 0; i < this->work.size(); i++)
	{
		under_work.push_back(false);
	}
}

WorkProduction::~WorkProduction()
{
}
