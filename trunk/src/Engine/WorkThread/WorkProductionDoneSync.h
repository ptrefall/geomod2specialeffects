#pragma once

#include "WorkData.h"

namespace Engine
{
	class WorkProductionDoneSync : public WorkData
	{
	public:
		WorkProductionDoneSync(unsigned int num_jobs);
		virtual ~WorkProductionDoneSync();
		
		void worker_done()
		{
			//if (done_jobs.increment() == num_jobs)
			done_event.set();
		}

		bool is_done() const
		{
			return done_jobs.get() == num_jobs;
		}

		CL_Event done_event;

		virtual void handle() { worker_done(); handled = true; }
		virtual bool isHandled() { return handled; }
	private:
		int num_jobs;
		CL_InterlockedVariable done_jobs;
		volatile bool handled;
	};
}
