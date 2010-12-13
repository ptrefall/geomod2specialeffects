#pragma once

namespace Engine
{
	class WorkData;
	class WorkProducer;

	class CoreMgr;
	class Worker
	{
	public:
		Worker(CoreMgr *coreMgr, int core, const CL_Event &work_event);
		virtual ~Worker();

		void worker_main(int core_id);
		bool isAtWork() const { return is_working; }
		void setToWork(WorkProducer *producer, WorkData *data, unsigned int index) { is_working = true; this->producer = producer; this->data = data; this->index = index; }
	private:
		void DoSomeWork(int core);
		CoreMgr *coreMgr;
		CL_Thread thread;
		CL_Mutex mutex;
		CL_Event event_stop;
		CL_Event work_event;

		volatile bool is_working;
		int core_id;

		WorkProducer *producer;
		WorkData *data;
		unsigned int index;
	};
}
