#pragma once

namespace Engine
{
	class WorkProducer;
	class WorkProduction;
	class WorkDoneData;
	class WorkData;

	class WorkThreadMgr
	{
	public:
		WorkThreadMgr();
		~WorkThreadMgr();

		bool isWorkGroupCompletedFor(WorkProducer *producer);
		WorkDoneData *getWorkGroupDoneData(WorkProducer *producer);

		void addWorkGroup(WorkProducer *producer, std::vector<WorkData*> work_group, WorkDoneData *doneData);

	private:
		std::map<WorkProducer*, WorkProduction*> produce;
	};
}
