#include "precomp.h"
#include "Worker.h"
#include "WorkThreadMgr.h"
#include "WorkProducer.h"
#include <Core/CoreMgr.h>

using namespace Engine;

Worker::Worker(CoreMgr *coreMgr, int core, const CL_Event &work_event)
: coreMgr(coreMgr), core_id(core), work_event(work_event), is_working(false), producer(NULL), data(NULL), index(0)
{
	thread.set_thread_name(cl_format("Worker%1", core).c_str());
	thread.start<Worker, int>(this, &Worker::worker_main, core);
}

Worker::~Worker()
{
}

void Worker::worker_main(int core)
{
	while(true)
	{
		//work_event.reset();
		int wakeup_reason = CL_Event::wait(work_event, event_stop);
		if (wakeup_reason == 0)
			DoSomeWork(core);
		else
			break;
	}
}

void Worker::DoSomeWork(int core)
{
	work_event.reset();
	producer->handle(data);
	is_working = false;
	coreMgr->getWorkThreadMgr()->finishedWork(producer, (unsigned int)index);
}
