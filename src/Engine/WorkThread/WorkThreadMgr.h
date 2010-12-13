#pragma once

namespace Engine
{
	class WorkProducer;
	class WorkProduction;
	class WorkDoneData;
	class Worker;
	class WorkData;

	class CoreMgr;
	class WorkThreadMgr
	{
	public:
		WorkThreadMgr(CoreMgr *coreMgr);
		~WorkThreadMgr();

		bool isWorkGroupCompletedFor(WorkProducer *producer);
		WorkDoneData *getWorkGroupDoneData(WorkProducer *producer);

		void addWorkGroup(WorkProducer *producer, std::vector<WorkData*> work_group, WorkDoneData *doneData);
		
		void assignWork();
		void finishedWork(WorkProducer *producer, unsigned int index);

		void update(float dt);

	private:
		std::map<WorkProducer*, WorkProduction*> produce;

		unsigned int num_threads;
		std::vector<Worker*> workers;
		std::vector<CL_Event> work_for_worker;

		CoreMgr *coreMgr;
	};
}
