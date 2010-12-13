#pragma once

namespace Engine
{
	class WorkData;
	class WorkDoneData;
	class WorkProduction
	{
	public:
		WorkProduction(const std::vector<WorkData*> &work, WorkDoneData *doneData);
		virtual ~WorkProduction();

		bool isDone() const { return done; }
		WorkDoneData * getDoneData() const { return doneData; }
		WorkData *getWorkData(unsigned int i) { return work[i]; }
		unsigned int getWorkDataSize() const { return work.size(); }

	private:
		volatile bool done;
		std::vector<WorkData*> work;
		std::vector<bool> under_work;
		WorkDoneData *doneData;
	};
}
