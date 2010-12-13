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
		bool isUnderWork(unsigned int i) { return under_work[i]; }
		void setUnderWork(unsigned int i) { under_work[i] = true; }
		void setFinishedWork(unsigned int i) 
		{ 
			numFinished++; 
			finished_work[i] = true; 
			if(numFinished == work.size())
			{
				done = true;
			}
		}

	private:
		volatile bool done;
		std::vector<WorkData*> work;
		std::vector<bool> under_work;
		std::vector<bool> finished_work;
		unsigned int numFinished;
		WorkDoneData *doneData;
	};
}
